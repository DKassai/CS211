#include <stdio.h>
#include <stdlib.h>




int main(int args, char** argv){

    //open file location
    FILE *fp;
    fp = fopen(argv[1],"r");
    
    // check to make sure file exists
    if (fp == NULL || fp == 0){
        printf("error, no file found\n");
        return 0;
    }

    // get length of 2d array
    int i = 0;
    fscanf (fp, "%d\n", &i);

    // create an array the size of the first number inputed
    int **array = (int **)malloc(i * sizeof(int *));
    int x;
    for (x=0; x<i; x++){
         array[x] = (int *)malloc( i * sizeof(int));  
    }




    // keep track of how dimension of matrix.
    int length = i;
         

         
    int coloum = 0;
    int row = 0;
    
    
    // loop through the rest of the file getting ints and storing it in 
    while (coloum < length && row != length ){  
         fscanf (fp, "%d\t", &i);    
         //printf ("%d ", i); 
         array[row][coloum] = i;
         //arry[amount] = i;
          
         coloum = coloum +1;
         if (coloum == length){
             coloum = 0;
             row = row + 1;
             //printf ("\n");
         }
    }

/*
    printf("matrix\n");
    int j;
    for (x = 0; x <  length; x++){
      for (j = 0; j < length; j++){
         printf("%d ", array[x][j]);
      }
      printf("\n"); 
    }
*/

   // get total of first coloum
   int total = 0;
   int q = 0;
   for (q=0;q < length; q++){
       total = total + array[q][0];
   }

    int sum = 0;
    int j = 0;
    // check rows

    for (x = 0; x <  length; x++){
       for (j = 0; j < length; j++){
          sum = sum + array[x][j];
          //printf("%d ", array[x][j]);
       }
       //printf("sum: %d ",sum);
       //printf("\n");
       if (sum != total){
           printf("not-magic");
           return 0;
       
       }
       sum = 0;
    }



    // check coloums
    for (x = 0; x <  length; x++){
       for (j = 0; j < length; j++){
          sum = sum + array[j][x];
          //printf("%d ", array[j][x]);
       }
       //printf("sum: %d ",sum);
       //printf("\n");
       if (sum != total){
           printf("not-magic");
           return 0;
       
       }
       sum = 0;
    } 



   // check diganlaze to the right 
   for (x = 0; x <  length; x++){
       for (j = 0; j < length; j++){
           if (x == j){
               sum = sum + array[x][j];
               //printf("%d ", array[x][j]);
           }
       }
       
       

    } 
    
   //printf("sum: %d ",sum);
   //printf("\n");
   if (sum != total){
      printf("not-magic");
      return 0;
       
   }
   // reset sum
   sum = 0;


  // check diganlaze to the left 
  
     for (x = 0; x <  length; x++){
       for (j = 0; j < length; j++){
           if ((x + j) == (length -1)){
               sum = sum + array[x][j];
               //printf("%d ", array[x][j]);
           }
       }
    } 
   //printf("sum: %d ",sum);
   //printf("\n");
   if (sum != total){
      printf("not-magic");
      return 0;
       
   }
   // reset sum
   sum = 0;
   
    // check to make no same numbers

   for (x = 0; x <  length; x++){
       for (j = 0; j < length; j++){
           if (!check(array,array[x][j],length)){
               printf("not-magic\n");
               return 0;

           }
       }
    } 







   // if gets to here its a magic matrix
   
   printf("magic\n");
   return 0;
}

int check(int **matrix, int num, int length){
    int sum = 0;
    int x;
    int j;
     for (x = 0; x <  length; x++){
       for (j = 0; j < length; j++){
           if (matrix[x][j] == num){
               sum = sum + 1;
           }
       }
    } 

    if(sum > 1){
        return 0;

    }else{
    return 1;

   }



}



