#include <iostream>
#include <fstream>
using namespace std;

void readingFiles(float **matrix, float *vector, int size){
	string line;
	ifstream matrixfile ("A.txt"), vectorfile("b.txt");// creates objects of ifstream class to make operations with A and b files, i.e. reading from them (input file)
	
	if(matrixfile.is_open()){
		for(int i=0; i<size; i++){
			for(int j=0; j<size; j++){
				matrixfile >> matrix[i][j];
			}
		}
	}// reads the file A and write it to the 2d A array
	else cout << "Unable to open the matrix file." << "\n"; // warns if the A file couldn't be opened.
	
	if(vectorfile.is_open()){
		for(int i=0; i<size; i++){
			vectorfile >> vector[i];
		}
		vectorfile.close();// closes the b file
	}// reads the file b and write it to the b array
	else cout << "Unable to open the vector file." << "\n"; // warns if the b file couldn't be opened.
}

int findMatrixSize(){
	int size=0; // creates and initializes a variable to keep the size of the matrix nxn
	string line;
	ifstream matrixfile ("A.txt");// creates objects of ifstream class to make operations with A and b files, i.e. reading from them (input file)
	
	if(matrixfile.is_open()){
		while(getline(matrixfile,line)){
			size++;
		}// counts how many lines in the file, which indicates the size of matrix
		matrixfile.close();// closes the file
	} 
	else cout << "Unable to open the matrix file." << "\n"; // warns if the A file couldn't be opened.
	//cout << n; to control whether it counts the lines correctly or not
	return size;
}

float findMax(float a, float b){
	
	if(a>b){
		return a;
	}
	else return b;
}// finds the maximum of two numbers

float abs(float a){
	
	if(a<0){
		return -a;
	}
	else return a;
}// finds the absolute value of a number

float findConditionNumberInfinityNorm(float **matrix){
	float det=matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0];// calculates the determinant of a 2 by 2 matrix
	float sumofrow1=abs(matrix[0][0])+abs(matrix[0][1]);// calculates the first row sum
	float sumofrow2=abs(matrix[1][0])+abs(matrix[1][1]);// calculates the second row sum
	float sumofcol1=abs(matrix[0][0])+abs(matrix[1][0]);// calculates the first row sum for the inverse matrix without scaling with the determinant
	float sumofcol2=abs(matrix[0][1])+abs(matrix[1][1]);// calculates the second row sum for the inverse matrix without scaling with the determinant
	
	return max(sumofrow1,sumofrow2)*max(sumofcol1,sumofcol2)/det;// multiply the max row sum for the matrix and its inverse and scale with its determinant, which is equal to the condition number
}// calculates the condition number of a 2 by 2 matrix

float findConditionNumberOneNorm(float **matrix){
	float det=matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0];// calculates the determinant of a 2 by 2 matrix
	float sumofcol1=abs(matrix[0][0])+abs(matrix[1][0]);// calculates the first row sum
	float sumofcol2=abs(matrix[0][1])+abs(matrix[1][1]);// calculates the second row sum
	float sumofrow1=abs(matrix[0][0])+abs(matrix[0][1]);// calculates the first row sum for the inverse matrix without scaling with the determinant
	float sumofrow2=abs(matrix[1][0])+abs(matrix[1][1]);// calculates the second row sum for the inverse matrix without scaling with the determinant
	
	return max(sumofcol1,sumofcol2)*max(sumofrow1,sumofrow2)/det;// multiply the max row sum for the matrix and its inverse and scale with its determinant, which is equal to the condition number
}// calculates the condition number of a 2 by 2 matrix

void partialPivoting(float **matrix, float *vector, int size){
	float max;// creates a variable to keep the maximum element of the every column for partial pivoting
	int maxindice;// creates a variable to keep the indice of the maximum element of the every column for partial pivoting
	
	for(int j=0; j<size-1; j++){// loop in columns except the last one which doesn't require pivoting
		max=abs(matrix[j][j]);// set the maximum to the diagonal of the current column
		maxindice=j;// set the maximum indice to the current row/column
		
		for(int i=j+1; i<size; i++){// loop in rows except the first one which is already kept with the max
			if(abs(matrix[i][j])>max){// compares whether the current entry is bigger than the maximum value of the column
				max=abs(matrix[i][j]);// sets maximum to the current entry if it is bigger than the current maximum value
				maxindice=i;// keeps the indice/row number of the new maximum value
			}
		}
		if(maxindice!=j){// controls whether the maximum is changed
			swap(matrix[j],matrix[maxindice]);// if changed, changes the rows of the matrix A
			swap(vector[maxindice],vector[j]);// if changed, changes the rows of the matrix b
			//maxindice=j+1;// set the maximum indice for the next column
		}
		
		float mult;// creates a variable to keep the scaling factor/multiplier for Gaussian elimination
		
		for(int i=j+1; i<size; i++){
			if(abs(matrix[j][j])<1e-6){
				break;// exits the loop whether the matrix is singular i.e. after the partial pivoting, any diagonal entry is zero
			}
			else mult=matrix[i][j]/matrix[j][j];// if not, calculates the scaling factor/multiplier for Gaussian elimination
				
			for(int k=0; k<size; k++){
				matrix[i][k]=matrix[i][k]-mult*matrix[j][k];// set A's entries to zero
			}
				
			vector[i]=vector[i]-mult*vector[j];// updates also b's entries
		}	
	}
}

int backwardSubstitution(float **matrix, float *vector, int size){
	for(int j=size-1; j>=0; j--){
		if(abs(matrix[j][j])<1e-6){
			cout << "The matrix is singular.";
			return 0;// warns if the matrix is singular and quits
		}
		vector[j]=vector[j]/matrix[j][j];
		
		for(int i=0; i<j; i++){
			vector[i]=vector[i]-matrix[i][j]*vector[j]; // updated b values with x values to save space
		}
	}
	return 1;
}

void solutionFile(float *vector, int size){
	ofstream xfile("x.txt");// creates objects of ofstream class to make operations with x files, i.e. writing to it (output file)

	if(xfile.is_open()){
		for(int i=0; i<size; i++){
			xfile << vector[i] << endl;
		}// writes the updated b entries, which constitues the solution vector, to the x file
		xfile.close();// closes the x file
	}
	else cout << "Unable to open the vector file." << "\n"; // warns if the x file couldn't be opened.
}

int main(){
	int n=findMatrixSize();
	
	float **A=new float* [n];
	for(int i=0; i<n; i++){
		A[i]=new float[n];
	} // creates dynamic allocation for the matrix A
	
	float *b;
	b= new float[n]; // creates dynamic allocation for the vector b
	
	readingFiles(A,b,n);// reads files and writes them to the matrix A and the vector b
	
	if(n==2){
		cout << "The condition number, using infinity norm, of the matrix A is " << findConditionNumberInfinityNorm(A) << endl;
		cout << "The condition number, using one norm, of the matrix A is " << findConditionNumberOneNorm(A) << endl;
	}// prints out the condition numbers of A if it is a 2 by 2 matrix
	
	partialPivoting(A,b,n);// makes partial pivoting
	
	if(backwardSubstitution(A,b,n)==0){
		return 0;
	}// makes backward substitution and quits if the matrix is singular

	solutionFile(b,n);// writes the solution vector to a file named "x.txt"
	
	for(int i=0; i<n; i++){
		delete[] A[i];
	}
	delete[] A;// deletes 2d A array
	
	delete[] b;// deletes b array
}
