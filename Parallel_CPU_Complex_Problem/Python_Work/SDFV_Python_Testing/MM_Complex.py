import numpy as np
A = np.array([[1+2j,2+4j,3+6j], [4+2j,5+4j,6+6j]])
B = np.array([[1+2j,1+4j,1+6j], [0+2j,1+4j,0+6j], [1+2j,1+4j,1+6j]])
print("Matrix A is:\n",A)
print("Matrix B is:\n",B)
C = np.matmul(A,B)
print("Matrix multiplication of matrix A and B is:\n",C)