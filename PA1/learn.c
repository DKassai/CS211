#include <stdio.h>
#include <stdlib.h>


#include "header.h"


int main(int args, char** argv){


    	//open file location
    	FILE *fp;
    	fp = fopen(argv[1],"r");
    
    	// check to make sure file exists
    	if (fp == NULL || fp == 0){
        	printf("error, no file found\n");
        	return 0;
    	}
    

        // get coloums length 
	int coloums = 0;
        fscanf (fp, "%d\n", &coloums);
        coloums++;

	// get coloums length 
	int rows = 0;
	fscanf (fp, "%d\n", &rows);
	

	

    	// create an array the size of the first number inputed
    	double **arrayX = (double **)malloc(rows * sizeof(double *));
    	int x;
    	for (x=0; x<rows; x++){
         	arrayX[x] = (double *)malloc( coloums * sizeof(double));  
    	}
    	
    	// create an transpose array the size of the first number inputed
    	double **TarrayX = (double **)malloc(coloums * sizeof(double *));
    	for (x=0; x<coloums; x++){
         	TarrayX[x] = (double *)malloc( rows * sizeof(double));  
    	}

	double *arrayY = (double *)malloc(rows * sizeof(int *));

    
    	int _row = 0;
    	int _coloum = 0;
    	double data;
    	
    	//printf("rows: %d\n",rows);
    	//printf("coloums %d\n",coloums);

    	// loop through the rest of the file getting ints and storing it in 
    	while ( _coloum < coloums  && _row < rows ){  
    		if (_coloum == 0){
    			arrayX[_row][_coloum] = 1;
    			_coloum++;
    			continue;
    		}
         	fscanf (fp, "%lf,", &data);    
         	 
         	//printf("x:%d y:%d\n",_row,_coloum);
         	//printf ("%lf \n", data);
         	arrayX[_row][_coloum] = data;
        	_coloum++;
		
		if (_coloum == coloums){
		fscanf (fp, "%lf,", &data);
		arrayY[_row] = data;
		//printf("------------y: %lf\n",arrayY[_row]);
		_coloum = 0;
		_row++;
		}
    	}
    	
    	
    	
    	// print out x matrix
    	//printf("-------------orginal matrix ---------\n");
    	//printMatrix(arrayX, rows,coloums);
    	
    	//printf("\n");
    	//printf("-------------transpose matrix ---------\n");
    	TransposeMatrix( arrayX,TarrayX,rows,coloums);
    	//printMatrix(TarrayX, coloums,rows);
    	
    	
    	
    	double **mutipleX = (double **)malloc(coloums * sizeof(double *));
    	for (x=0; x<coloums; x++){
         	mutipleX[x] = (double *)malloc( coloums * sizeof(double));  
    	}
    	


    	//mutipleX = arrayX;

    	
    
    	//printf("\n");
    	mutipleMatrix(mutipleX,TarrayX, arrayX,coloums,rows,rows,coloums);
    	//printf("------------------mutiplecation matrix--------------------\n");
	//printMatrix(mutipleX, coloums,coloums);
	//printf("--------------------------------------\n");
	
	// create agumented matrix 
	double **agumentX = (double **)malloc(coloums * sizeof(double *));
    	for (x=0; x<coloums; x++){
         	agumentX[x] = (double *)malloc( coloums * sizeof(double));  
    	}
    	// set all the pivit points to 0
    	int z = 0;
    	while(z != coloums){
    		agumentX[z][z] = 1;
    		z++;
    	} 
    	
	
	// loop through getting identiy matrix
    	int currentColoum = 0;
    	while(currentColoum < coloums){
    		clearBottomPivit(mutipleX,currentColoum,currentColoum,coloums,coloums,agumentX);
    		//printf("----------piviot point: %d-------\n",currentColoum);
    		//printMatrix(mutipleX, coloums,coloums);
    		currentColoum++;
    	
    	}
    	
    	//printf("--------------agumented matrix before top triangel-----------\n");
    	//printMatrix(agumentX, coloums,coloums);
	
	currentColoum--;
	//printf("%d\n\n",currentColoum );

	while(currentColoum >=0){
		
		
    		clearTopPivit(mutipleX,currentColoum,currentColoum,coloums,coloums,agumentX);
    		//printf("----------piviot point: %d-------\n",currentColoum);
    		//printMatrix(mutipleX, coloums,coloums);
    		currentColoum--;
    	//printf("--------------agumented matrix-----------\n");
    	//printMatrix(agumentX, coloums,coloums);


    	
    	}
    	//printf("--------------final agumented matrix----------\n");
    	//printMatrix(agumentX, coloums,coloums);


	
	// mutiplly inverse by transpose  
	// 4X4  4X7  = 4X7 
	
	// create second matrix   
	double **secondX = (double **)malloc(coloums * sizeof(double *));
    	for (x=0; x<coloums; x++){
         	secondX[x] = (double *)malloc( rows * sizeof(double));  
    	}
    	mutipleMatrix(secondX, agumentX, TarrayX,coloums,coloums,coloums,rows);
    	//printf("--------------new matrix matrix-----------\n");
    	//printMatrix(secondX,coloums,rows);
    	
    	
    	
    	double *Weights = (double *)malloc(coloums * sizeof(double *));
    	
    	//4X7 * 4X1 = 4 X 1 
    	//printf("--------------Y matrix matrix-----------\n");
    	//printMatrixY(arrayY,rows);
    	// mutiple outcome by answers 
    	// print out the weights 
    	mutipleMatrixSingleLine(Weights,secondX, arrayY, coloums,rows, rows);
    	//printf("--------------Weights matrix matrix-----------\n");
    	//printMatrixY(Weights,coloums);
    	
    	
    	// got the weights mutiply the new data by the weights and see what the answer is
    	
    	
    	// total coloums is eqaul to (coloums)
    	
    	//open file location
    	fclose (fp);
    	
    	FILE *fp1;
    	fp1 = fopen(argv[2],"r");
    
    	// check to make sure file exists
    	if (fp1 == NULL || fp1 == 0){
        	printf("error, no file found\n");
        	return 0;
    	}
    

        // get coloums length 
	int testRows = 0;
        fscanf (fp1, "%d\n", &testRows);
        //printf("%d\n",testRows);
        //printf("\n%d\n",testRows);
	//printf("%d\n",testRows);
        
       
        double *testData = (double *)malloc(coloums * sizeof(double *));
        
        int q;

        for (q = 0; q <testRows;q++){
        testData[0] = 1;
		int test = 1;
		while(test < coloums){
	       		fscanf (fp1, "%lf,", &data);  
			testData[test] = data;
			test++;
		}
		//printf("--------------testdata row %d matrix matrix-----------\n",q);
	    	//printMatrixY(testData,coloums);
	    	
	    	double value = 0;
	    	
	    	int r = 0;
	    	for (r = 0; r<coloums;r++){
	    		value += Weights[r] * testData[r];
	    	}
	    	
	    	printf("%0.0f\n", value);
	    	
		
    	}

	return 0;
    	
    	
}



// coloums is equall to total coloums
void divideMatrixRow(double ** matrix, int coloums, int rowToChange,double Num){
	
	int y;
	for(y = 0; y < coloums; y++){
		if (matrix[rowToChange][y] == 0){
			matrix[rowToChange][y] = 0;
		}else{
			matrix[rowToChange][y] = (matrix[rowToChange][y] / Num)	;
		}
	}
}


//subtracts first row by second row and returns first row  R1 = R1-R2
void subtractMatrixRow(double ** matrix, int coloums, int firstRow, int secondRow ){
	
	int y;
	for(y = 0; y < coloums; y++){
		matrix[firstRow][y] = (matrix[firstRow][y] -matrix[secondRow][y])	;
	}
}



void printMatrix(double ** matrix, int rows, int coloums){
	int x = 0;
	int y = 0;
	for(x = 0; x < rows; x++){
		for(y = 0; y < coloums; y++){
			printf("%lf ",matrix[x][y]);
		}
		printf("\n");
	}
}
void TransposeMatrix(double ** matrix, double **Tmatrix, int rows, int coloums){
	int x = 0;
	int y = 0;
	for(x = 0; x < coloums; x++){
		for(y = 0; y < rows ; y++){
			Tmatrix[x][y] = matrix[y][x];
		}
	}
}

void printMatrixY(double * matrix, int rows){
	int x = 0;
	for(x = 0; x < rows; x++){
		
		printf("%lf ",matrix[x]);
		printf("\n");
	}
}



void mutipleMatrix(double ** outcome, double ** firstMatrx, double ** secondMatrix, int firstRow, int firstColoum, int secondRow, int secondColoum){
	//printf("%d\n",firstRow);
	//printf("%d\n",firstColoum);
	//printf("%d\n",secondRow);
	//printf("%d\n",secondColoum);
	int i =0;
	for(i=0; i<firstRow; i++){
		int j =0;
        	for(j=0; j<secondColoum; j++){

        		double sum = 0;
            		int k = 0;

            		for(k=0; k<firstColoum; k++){
           			sum+= firstMatrx[i][k]*secondMatrix[k][j];
       			 }	
			//printf("sum: %lf\n",sum);
			outcome[i][j] = sum;
    		}

	}
}

void mutipleMatrixSingleLine(double * outcome, double ** firstMatrx, double * secondMatrix, int firstRow, int firstColoum, int secondRow){

	int i =0;
	for(i=0; i<firstRow; i++){
        		outcome[i] = 0;
            		int j = 0;
            		for(j=0; j<firstColoum; j++){
           			outcome[i]+= firstMatrx[i][j]*secondMatrix[j];
       			 }
    		
	}
}

void subtractMutipleMatrix(double ** matrix,int coloums, int firstRow, int secondRow,int muiltnum){
	int y;
	for(y = 0; y < coloums; y++){
		matrix[firstRow][y] = (matrix[firstRow][y]  -(muiltnum *matrix[secondRow][y]));
	}
}

void clearBottomPivit(double ** matrix,int coloums,int row,int totalColoums,int totalRows,double ** augmatrix){

	// start by clearing the row 
	//agument value first so that you dont have to store info
	divideMatrixRow(augmatrix,totalColoums,row, matrix[row][coloums]);
	divideMatrixRow(matrix,totalColoums,row, matrix[row][coloums]);
	
	//printMatrix(matrix, 4,4);
	// loop through that coloum clearing out below the row you just cleared
	int r = row;
	r++;// move to next point because you already set the row you are up to, too 1
	while(r < totalRows){

		if (matrix[r][coloums] !=0){
			double cur = matrix[r][coloums];
			if (cur == (int) matrix[r][coloums]){
				subtractMatrixRow(augmatrix,totalColoums, r, row );
				subtractMatrixRow(matrix,totalColoums, r, row );
			}else{
				divideMatrixRow(augmatrix,totalColoums,r,matrix[r][coloums]);
				divideMatrixRow(matrix,totalColoums,r,matrix[r][coloums]);
				
			}		
		}else{
			r++;
		}
	}
}



void clearTopPivit(double ** matrix,int coloums,int row,int totalColoums,int totalRows,double ** augmatrix){
	// start of by making sure the piviot is 1
	
	divideMatrixRow(augmatrix,totalColoums,row, matrix[row][coloums]);
	divideMatrixRow(matrix,totalColoums,row, matrix[row][coloums]);
	
	int r  = row;
	r--;
	while(r >= 0){
		if (matrix[r][coloums] !=0){
			double cur = matrix[r][coloums];
			if (cur == (int) matrix[r][coloums]){
				subtractMatrixRow(augmatrix,totalColoums, r, row );
				subtractMatrixRow(matrix,totalColoums, r, row );	
			}else{
				divideMatrixRow(augmatrix,totalColoums,r,matrix[r][coloums]);
				divideMatrixRow(matrix,totalColoums,r,matrix[r][coloums]);
				
			}		
		}else{
			r--;
		}
	}
}









