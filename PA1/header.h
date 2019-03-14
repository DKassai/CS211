
#ifndef header_h/* Include guard */
#define header_h

void printMatrix(double ** matrix, int rows, int coloums);
void printMatrixY(double * matrix, int rows);
void divideMatrixRow(double ** matrix, int coloums, int rowToChange,double Num);
void subtractMatrixRow(double ** matrix, int coloums, int firstRow, int secondRow );
void TransposeMatrix(double ** matrix, double **Tmatrix, int rows, int coloums);
void mutipleMatrix(double ** outcome, double ** firstMatrx, double ** secondMatrix, int firstRow, int firstColoum, int secondRow, int secondColoum);
void subtractMutipleMatrix(double ** matrix,int coloums, int firstRow, int secondRow,int muiltnum);
void clearBottomPivit(double ** matrix,int coloums,int row,int totalColoums,int totalRows,double ** augmatrix);

void clearTopPivit(double ** matrix,int coloums,int row,int totalColoums,int totalRows,double ** augmatrix);
void mutipleMatrixSingleLine(double * outcome, double ** firstMatrx, double * secondMatrix, int firstRow, int firstColoum, int secondRow);

void printMatrixYD(double * matrix, int rows);

#endif 
