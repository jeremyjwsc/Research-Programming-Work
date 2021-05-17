import numpy as np

import time

# generating 1000 x 1000 matrices
np.random.seed(42)

A = np.random.randint(0,256, size=(1000,1000)).astype("complex128")

B = np.random.randint(0,256, size=(1000,1000)).astype("complex128")


#computing multiplication time on CPU
tic = time.time()

C = np.matmul(A,B)

toc = time.time()

time_taken = toc - tic #time in s

print("Matrix A is:\n", A)

print("Matrix B is:\n", B)

print("Matrix multiplication of matrix A and B is:\n", C)

print("Time taken on CPU (in ms) = {}".format(time_taken*1000))