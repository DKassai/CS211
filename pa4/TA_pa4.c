#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

unsigned long long int memory_size = 0, cache_size = 0, associativity = 0, block_size = 0, num_writes = 0;
unsigned long long int cache_hit[2];
unsigned long long int cache_miss[2];
unsigned long long int num_reads[2];
char* cache_policy = "fifo";
int memory_address_size = 48, offset_bits = 0, set_bits = 0, tag_bits = 0, number_of_sets = 0, num_blocks_per_set = 0;
 
typedef struct nodes{
	unsigned long long int tag, set;
	struct nodes* next;
} Node;
Node** cache[2];

unsigned long long int create_mask(int start, int end){ //node struct
	unsigned long long int mask = 1;
	for(int counter = 1; counter < start; counter++, mask++)
		mask <<= 1;
	return mask <<= end;
}

Node* init_node(unsigned long long int mem){ //initialize node
	Node* temp = (Node*)malloc(sizeof(Node));
	if(associativity == -1)
		temp->set = 0;
	else
		temp->set = (mem & create_mask(set_bits, offset_bits)) >> offset_bits;
	temp->tag = (mem & create_mask(tag_bits, set_bits + offset_bits)) >> (set_bits + offset_bits);
	temp->next = NULL; 
	return temp;
}

long long int charToInt(char* input_string){ //converts a string to an int 
	long long int num = 0, pos, counter = 1;
	for(pos = strlen(input_string) - 1; pos >= 0; pos--, counter *= 10){
	  if(input_string[pos] == ':')
	    return num;
	  num += (input_string[pos] - '0') * counter;
	}
	return num;
}

void search_cache(unsigned long long int address){ //search
	Node* temp[2];
	int run, run_with_prefetch, hm;
	for(run = 0; run < 2; run ++){
		temp[0] = init_node(address);
		if(run == 1)
			temp[1] = init_node(address + block_size);
		for(run_with_prefetch = 0; run_with_prefetch <= run; run_with_prefetch++){
			hm = 0;
			if(cache[run][temp[run_with_prefetch]->set] == NULL){ //empty cache 
				cache[run][temp[run_with_prefetch]->set] = temp[run_with_prefetch];
				if(run_with_prefetch == 0)
					cache_miss[run] += 1;
				num_reads[run] += 1;
			}
			else{
				int pos = 0;
				Node* ptr = cache[run][temp[run_with_prefetch]->set];
				Node* prev = NULL; 
				while(ptr != NULL){
					if(ptr->tag == temp[run_with_prefetch]->tag){ //hit 
						if(run_with_prefetch == 0 && strcmp(cache_policy, "lru") == 0 && ptr->next != NULL){
							if(prev == NULL)
								cache[run][temp[run_with_prefetch]->set] = ptr->next; 
							else
								prev->next = ptr->next;
							Node* tempPtr = ptr->next;
							while(tempPtr->next != NULL)
								tempPtr = tempPtr->next;
							tempPtr->next = ptr;
							ptr->next = NULL; 
						}
						if(run_with_prefetch == 0){
							cache_hit[run] += 1;
							run_with_prefetch = 2;
						}
						hm = 1;
						break;
					}
					pos += 1;
					prev = ptr;
					ptr = ptr->next;
				}
				if(hm != 1){
					if(run_with_prefetch == 0)
						cache_miss[run] += 1;
					prev->next = temp[run_with_prefetch];
					num_reads[run] += 1;
					pos += 1;
					if(pos > num_blocks_per_set){
						Node* tempPtr = cache[run][temp[run_with_prefetch]->set];
						cache[run][temp[run_with_prefetch]->set] = cache[run][temp[run_with_prefetch]->set]->next;
						free(tempPtr);
					}
				}
			}
		}
	}
}

void print_results(int run){ //prints formatted 
	if(run == 0)
		printf("no-prefetch\n");
	else
		printf("with-prefetch\n");
	printf("Memory reads: %lld\nMemory writes: %lld\nCache hits: %lld\nCache misses: %lld\n", num_reads[run], num_writes, cache_hit[run], cache_miss[run]);
}

int main(int argc, char** argv){ //set up code
	memory_size = pow(2, memory_address_size);
	int temptwo = 1, counter = 0;

	cache_size = charToInt(argv[1]);	
	while(temptwo < cache_size)
		temptwo *= 2;
	if(temptwo != cache_size){
		printf("error\n");
		return 0;
	}
	
	if(strcmp(argv[2], "direct") == 0)
	  associativity = 1;
	else if(strcmp(argv[2], "assoc") == 0)
	  associativity = -1;
	else
	  associativity = charToInt(argv[2]);
	
	cache_policy = argv[3];
	
	block_size = charToInt(argv[4]);
	if(associativity == -1){
		number_of_sets = 1;
		num_blocks_per_set = cache_size / block_size;
	}
	else{
		number_of_sets = cache_size / (associativity * block_size);
		num_blocks_per_set = associativity;
	}
	
	counter = 0;
	for(temptwo = 1; temptwo < block_size; temptwo *= 2)
		counter++;
	offset_bits = counter;
	
	counter = 0;
	for(temptwo = 1; temptwo < number_of_sets; temptwo *= 2)
		counter++;
	if(associativity == -1)
		set_bits = 0;
	else
		set_bits = counter;
	tag_bits = memory_address_size - set_bits - offset_bits;
	
	for(counter = 0; counter < 2; counter++){
		cache[counter] = (Node**)malloc(number_of_sets * sizeof(Node*));
		cache_hit[counter] = 0;
		cache_miss[counter] = 0;
		num_reads[counter] = 0;
	}
	
	//run file
	FILE* fp = fopen(argv[5], "r");
	unsigned long long int trash, address;
	char command;
	while(fscanf(fp, "%llx: %c %llx", &trash, &command, &address) > 0){
		if(command == 'W')
			num_writes += 1;
		search_cache(address);
	}
	print_results(0);
	print_results(1);
	return 0;
}
