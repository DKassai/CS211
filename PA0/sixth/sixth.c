#include <stdio.h>
#include <stdlib.h>


#define nullByte 1



char * add_two(char* list, int sum,char letter);
char * add_one(char* list,char letter);
void print_array(char* list);
int get_length(char* list);


int main(int args, char** argv){
    // check to confirm correct inputs
    if (args != 2){
        printf("error\n");
        return 1;
    }

   // check tmill,jhmgnbcv xzaswertgyhujiklop9;lokjhgbvf
   char * string = argv[1];
   //int length = sizeof(string) / sizeof(string[0]);
   //printf("%d \n",length);

   int x = 0;
   while (string[x] != '\0'){
       // check to see if there is a characterz
       
       if( string[x] >= (int)'0' && string[x] <= (int)'9' ){
           //printf("%d: \t number up to: %d  \t : %d \n", '0',string[x],'9');
           printf("error\n");
           return 0;
       
       
       }
   x++;
   }
   int length = x + 1;
   
   char * new_string = NULL;
   
   int stupid = 0;
   int sum= 1;
   char currect_c = '1';
   char next_c = '1';
   int i;
   /*
        for(i = 0; i < 2; i++){
            printf("%c",new_string[i]);
        }
        printf("\n");
   */
   
   x = 0;
   while (string[x] != '\0'){
       //printf("%d\n",x);
       if (currect_c == '1'){
           currect_c = string[x];
           x++;
       }else{
       // get currect char
           next_c = string[x];
           // check to see if the char is the same as the previos one;
           if (next_c != currect_c){
               // check what sum is 
               
               // if sum is grater then 1
               if (sum >1  ){
                   // send to increase string by 2 
                   new_string = add_two(new_string,sum,currect_c);
                   //print_array(new_string);
                   sum = 1;
                   stupid = 1;

                   currect_c = '1';
                
               }else if(sum <= 1 && stupid != 0){
               // send to increase string by 2 
                   new_string = add_two(new_string,1,currect_c);
                   //print_array(new_string);
                   sum = 1;
                   currect_c = '1';
               }else{
               // send to increase by one
                   new_string = add_one(new_string,currect_c);
                   //print_array(new_string);
                   currect_c = '1';
               }
               
           }else{
               sum = sum +1;
               x++;
           
           }
       }// end of else with null
   }// end of while loop
   
   if (!(currect_c == '1')){
                // if sum is grater then 1
               if (sum >0 ){
                   // send to increase string by 2 
                   new_string = add_two(new_string,sum,currect_c);
                   //print_array(new_string);
                   sum = 0;
                   currect_c = '1';
                
               }else if(sum < 1 && stupid !=0){
               // send to increase string by 2 
                   new_string = add_two(new_string,1,currect_c);
                   //print_array(new_string);
                   sum = 1;
                   currect_c = '1';
               }else{
               // send to increase by one
                   new_string = add_one(new_string,currect_c);
                   //print_array(new_string);
                   currect_c = '1';
               }
   } 
   
   // print the array at the end
   if (get_length(string) > get_length(new_string)){
       print_array(new_string);
   }else{
   print_array(string);
   }
   return 0;
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

char * add_two(char* list, int sum,char letter){
    
    int length = 0;
    int x = 0;
    int someInt = sum;
    char str[64];
    str[63] = '\0';
    // convert int to a string
    sprintf(str, "%d", someInt);
    // get length of int
    while (str[length] != '\0'){
         length++;
    } 
    
    if (list == NULL){ 
    
        char * list = malloc( length * sizeof(char) + sizeof(char) + nullByte);
        list[0] = letter;
        for(x =1; x < length+1; x++){
            list[x] = str[x-1];
        }
        list[length +1] = '\0';
        return list;
        /*
        int i = 0;
        for(i = 0; i < 3; i++){
            printf("%c",list[i]);
        }
        printf("\n");
        */
    }else{ 
        // get length of old string
        x = 0;
        while (list[x] != '\0'){
            x++;
        } 
         char * new_list = malloc( x *  sizeof(char) + ( length * sizeof(char)) + nullByte);
          
         int y = 0;
         for (y =0; y<x; y++){
             new_list[y] = list[y]; 
         }
        /*
        int i = 0;
        for(i = 0; i < 3; i++){
            printf("%c",new_list[i]);
        }
        printf("\n");
        */
        new_list[x] = letter;
        x = x + 1;
        for(y = x; y < x+length; y++){
            new_list[y] = str[y-x];
        }
        /*
        for(i = 0; i < 7; i++){
            printf("%c",new_list[i]);
        }
        printf("\n");
        */
        list[x +  length ] = '\0';
        return new_list; 
    }
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

int get_length(char* list){
    int length  = 0;
    while (list[length] != '\0'){
         length++;
    } 
    return length;

}

