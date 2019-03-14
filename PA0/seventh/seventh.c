#include <stdio.h>
#include <stdlib.h>

#define nullByte 1


char * add_one(char* list,char letter);
void print_array(char* list);

int main(int args, char** argv){
    char * list = NULL;
    int x = 1;
    int c = 0;
    for(x = 1; x < args; x++){
       char * pointer = argv[x];
       while (pointer[c] != '\0'){
        c++;
       }
       list = add_one(list,pointer[c-1]);
       c = 0;
     }
     print_array(list);
     return 0;

}

void print_array(char* list){
    int length  = 0;
    while (list[length] != '\0'){
         length++;
    } 
    
    int x;
    for (x = 0; x < length; x++){
        printf("%c",list[x]);
    }
    printf("\n");
    
}

char * add_one(char* list,char letter){
    int length = 0;
    if (!(list == NULL)){  
    while (list[length] != '\0'){
         length++;
    } 
    }
    
    if (list == NULL){
        char * list = malloc( sizeof(char) +nullByte);
        list[0] = letter;
        list[1] = '\0';
        return list;
    
    }else{
    char * new_list = malloc( length * sizeof(char) +sizeof(char) + nullByte);
    int y = 0;
    for (y =0; y<length; y++){
         new_list[y] = list[y]; 
    }
    new_list[length] = letter;
    new_list[length + nullByte] = '\0';
    return new_list;
    }
}
