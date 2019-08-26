This program solves Ax=b, using Gaussian elimination with partial pivoting and back substitution.
*A should be a nxn matrix, and b should be a nx1 vector. These matrices should have been written in text documents named "A.txt" and "b.txt", respectively. 
They should have the same number of lines. Each line represents a row.
Example:For "A.txt"
3.14 1.59 2.65 3.58
9.79 3.23 8.46 2.64
3.38 3.27 9.50 2.88
4.19 7.16 9.39 9.37
For “b.txt”
5.10
5.82
0.97
4.94
*They should also be in the same folder with the program.
*The solution file will be written to a file named "x.txt" in that file.
*If A is singular or nearly singular (any number which its absolute value is smaller than 1e-6 will be converted to 0),
a warning will appear in the console and no x file will be generated.
*If the matrix A is 2x2, the condition numbers will be shown in the console.


*****The Case of High Condition Numbers*****
A=[1.000 1.000
   1.000 1.001]
b1=[2.000 2.000]T
b2=[2.000 2.001]T
The condition number, using infinity norm, of the matrix A is 4003.81
The condition number, using one norm, of the matrix A is 4003.81
x1=[2 0]T
x2=[1.00012 0.999881]T

Since the condition number is too high (>>1), the solution is very sensitive to the small changes as we can see from the example above.