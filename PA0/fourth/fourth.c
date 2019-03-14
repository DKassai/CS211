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
    
    //create array 2 for mutiplication
    int **array2 = (int **)malloc(i * sizeof(int *));
    for (x=0; x<i; x++){
         array2[x] = (int *)malloc( i * sizeof(int));  
    }
    
    //create temp 2 for mutiplication
    int **temp = (int **)malloc(i * sizeof(int *));
    for (x=0; x<i; x++){
         temp[x] = (int *)malloc( i * sizeof(int));  
    }
       
    // keep track of how dimension of matrix.
    int count = i;
         

         
    int amount = 0;
    int row = i;
    int coloum = 0;
    
    
    // loop through the rest of the file getting ints and storing it in 
    while (amount < row && coloum != row ){  
         fscanf (fp, "%d\t", &i);    
         //printf ("%d ", i); 
         array[coloum][amount] = i;
         array2[coloum][amount] = i;
         temp[coloum][amount] = 0;
         //arry[amount] = i;
          
         amount = amount +1;
         if (amount == row){
             amount = 0;
             coloum = coloum + 1;
             //printf ("\n");
         }
    }
    
    
    // get times to muliply 
    int mutiple  = 0;
    fscanf (fp, "%d\n", &mutiple);
    
    int j;
    //printf("%d ", arr[0][0]);
    /*
    printf("first matrix\n");
    int j;
    for (x = 0; x <  count; x++){
      for (j = 0; j < count; j++){
         printf("%d ", array[x][j]);
      }
      printf("\n");
    }
    
    printf("second matrix\n");
    for (x = 0; x <  count; x++){
      for (j = 0; j < count; j++){
         printf("%d ", array2[x][j]);
      }
      printf("\n");
    }
    
    printf("temp matrix\n");
    for (x = 0; x <  count; x++){
      for (j = 0; j < count; j++){
         printf("%d ", temp[x][j]);
      }
      printf("\n");
    }
    */
    // test case if mutiple is 0
    
    if (mutiple == 0){
        //printf("0 case\n");
        for (x = 0; x <  count; x++){
            for (j = 0; j < count; j++){
                if (x == j){
                    printf("1\t");
                }else{
                printf("0\t");
                }
            }
        printf("\n");
        
        }
    
    
    return 0;
    }
    
    // main part of function that deals with mutiplication
    
    while(mutiple-1 != 0){
    // mutiple matrix 
    int first , second, hand, sum = 0;
    for(first = 0; first < count; first++){
        for(second = 0; second < count; second++){
            for(hand = 0; hand < count; hand++){
                sum = sum + array[first][hand] * array2[hand][second];
            }
        temp[first][second] = sum;
        sum = 0;    
        }
    }
    /*
    printf("temp matrix\n");
    for (x = 0; x <  count; x++){
      for (j = 0; j < count; j++){
         printf("%d ", temp[x][j]);
      }
      printf("\n");
    }
    */
    for (x = 0; x <  count; x++){
      for (j = 0; j < count; j++){
          array2[x][j] = temp[x][j] ;

      }

    }

     mutiple = mutiple - 1;

    } // and of while
    
    
    //printf("final matrix\n");
    for (x = 0; x <  count; x++){
      for (j = 0; j < count; j++){
         printf("%d\t", temp[x][j]);
      }
      printf("\n");
    }

    return 0;
}
