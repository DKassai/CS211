#include <stdio.h>
#include <stdlib.h>

// create hash node
struct node {
    int data;
    struct node *next;
};


int hash(int key); 
struct node *insert(struct node *head,int cargo);
int search(struct node *head, int cargo);
int searchValue(struct node *head, int cargo);
void printArray();
void transverse(struct node *head);


// define the size of the hash table
#define HASHSIZE 10000

// create hashtable to be used
struct node *hashtable[HASHSIZE];

int main(int args, char** argv){

    // set all values to null
    int count;
    for(count = 0; count <= HASHSIZE - 1; count++){
        hashtable[count] = NULL;
    }
    
    //open file location
    FILE *fp;
    fp = fopen(argv[1],"r");
    
    // check to make sure file exists
    if (fp == NULL || fp == 0){
        printf("error\n");
        return 0;
    }
    // start reading files
    // init varables to store information
    int num = 0 ;
    char c;
    // go throught the file until no more lines to read
    while( fscanf(fp,"%c\t%d\n",&c,&num) != EOF){
        //printf("%c\t%d\n",c,num);
      
        if ('i' == c){  
            hashtable[hash(num)] = insert(hashtable[hash(num)],num);
        }else{
            searchValue(hashtable[hash(num)],num);
        }
        
    }
    //printArray();
    return 0;
}

struct node *insert(struct node *head, int cargo){
    // check to see if first entry
    if(head == NULL){
        struct node *c = malloc(sizeof(struct node));
        c->data = cargo;
        c->next = NULL;
        head = c;
        printf("inserted\n");
        return head; 
    }
    if (!search(head,cargo)){
        struct node *c = malloc(sizeof(struct node));
        c->data = cargo;
        c->next = head;
        head = c;
        printf("inserted\n");
        return head; 
    }
    printf("duplicate\n");
    return head;
    
}

int search(struct node *head, int cargo){
    struct node *current = head;
    while (current != NULL){
        if (current->data == cargo){
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int searchValue(struct node *head,int cargo){
    struct node *current = head;
    while (current != NULL){
        if (current->data == cargo){
        printf("present\n");
            return 1; 
        }
        current = current->next;
    }
    printf("absent\n");
    return 0;
}


int hash(int key){
    return abs(key) % HASHSIZE;
}

void printArray(){
    int x = 0;
    for(x =0;x <=12; x++){
        printf("row %d --->)",x);
        transverse(hashtable[x]);
        printf("\n");


    }
}
void transverse(struct node *head){
    struct node *current = head;
    while (current != NULL){
        printf("%d ---> ",current->data);
        current = current->next;
    }

}


