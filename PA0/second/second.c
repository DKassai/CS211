#include <stdio.h>
#include <stdlib.h>


int * sortArray(int arry[],int length);
void printArry(int arry[], int length);





int main(int args, char** argv){

    // check to confirm correct inputs
    if (args != 2){
        printf("error\n");
        return 0;
    }

    //open file location
    FILE *fp;
    fp = fopen(argv[1],"r");
    
    // check to make sure file exists
    if (fp == NULL || fp == 0){
        printf("error\n");
        return 0;
    }
    
    // varables used for reading information
    int i = 0;
    int amount = 0;
    
    // get how many numbers are in the file
    fscanf (fp, "%d\n", &i);
    //printf ("%d\n", i);
    
    // set amount to number pulled from file. 
    amount = 0;
    int total = i;
    //create array to store int in
    
    int arry[i];
    
    // loop through the rest of the file getting ints and storing it in 
    while (amount < total  ){  
      
         fscanf (fp, "%d", &i);    
         //printf ("%d ", i); 
         arry[amount] = i;
          
         amount = amount +1;
    }
    
    //printf("\n");
    // print array to confirm everything is in the array
    // int x=0;
    //for(x = 0; x <total; x++){
    //    printf("%d ",arry[x]);
    //}
    
    // sort array
    sortArray(arry,total);
    // print array
    printArry(arry,total);
    
    
    
    return 0;


}


void printArry(int arry[], int length){
    int x = 0;
    for(x = 0; x< length; x++){
        printf("%d\t",arry[x]);
    }
    printf("\n");
}



int * sortArray(int arry[],int length){
    int x = 0;
    int y = 0;
    int tmp;
    for(x = 0; x<length;x++){
        for(y=x;y<length;y++){
            if(arry[x] > arry[y]){
            // swap
            tmp = arry[x];
            arry[x] = arry[y];
            arry[y] = tmp;
            }
            
        }
    }
    


}






