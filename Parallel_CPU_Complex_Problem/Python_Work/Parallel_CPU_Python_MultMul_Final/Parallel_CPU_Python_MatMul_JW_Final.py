from __future__ import print_function

import dace
import time
import numpy as np
from random import randint

# For library node implementations
import dace.libraries.blas

import multiprocessing
from concurrent.futures import ThreadPoolExecutor

Dimension = 0
MatrixA = []
MatrixB = []
MatrixC = []
_real = 0
_imag = 0
MaxRndVal = 0 + 0j
Elapsed = 0
ParallelElapsed = 0

# Define symbolic sizes for arbitrary inputs
F = dace.symbol('F')
G = dace.symbol('G')
H = dace.symbol('H')

# Define data type to use
# Complex number, represented by two 64-bit floats (real and imaginary components)
dtype = dace.complex128
np_dtype = np.complex128

# tic = time.time()

# Generalized matrix-matrix multiplication (gemm method)
@dace.program
def multmul_Gemm_Final(A: dtype[F, G], B: dtype[G, H], C: dtype[F, H]):
    C[:] = A @ B

# toc = time.time()
#
# time_taken = toc - tic  # time in s

# tic1 = time.time()

# Library node version of matrix multiplication, using the numpy interface
@dace.program
def multmul_Libnode_Final(A: dtype[F, G], B: dtype[G, H]):
    return A @ B

# toc1 = time.time()
#
# time_taken1 = toc1 - tic1  # time in s

def matrixmul(ii, jj, d):
    global MatrixA
    global MatrixB
    global MatrixC

    for k in range(d):
        MatrixC[ii][jj] += MatrixA[ii][k] * MatrixB[k][jj]

def matrix_multiplication(Dimension):
    start = time.time()
    for i in range(Dimension):
        for j in range(Dimension):
            matrixmul(i, j, Dimension)
    end = time.time()
    return end - start

def matrix_parallel_multiplication(Dimension):
    start = time.time()
    cpucount = multiprocessing.cpu_count()

    with ThreadPoolExecutor(cpucount) as pool:
        pool.map(matrixmul, [(ii, jj, Dimension) for ii in range(Dimension) for jj in range(Dimension)])

    end = time.time()
    return end - start

def set_dimension(Dimension):
    return np.zeros((Dimension, Dimension), dtype=complex)

def set_random_value(Matrix, Dimension, MaxRndVal):
    for i in range(Dimension):
        for j in range(Dimension):
            if (MaxRndVal.real < 1 or MaxRndVal.imag < 1):
                Matrix[i][j] = complex(0, 0)
            else:
                _real = MaxRndVal.real
                _real = randint(0, _real)
                _imag = MaxRndVal.imag
                _imag = randint(0, _imag)
                Matrix[i][j] = complex(_real, _imag)
    return Matrix

def display_matrix(Matrix, Dimension):
    if Dimension > 30:
        print("Display is not available more than dimension 30.")
        return
    for i in range(Dimension):
        for j in range(Dimension):
            print(Matrix[i][j]),
        print("")

def main():
    print("\n ==== Program begins ====")
    global MatrixA
    global MatrixB
    global MatrixC
    global Dimension
    global _real
    global _imag
    global MaxRndVal
    global Elapsed
    global ParallelElapsed

    while True:
        Dimension = int(input("\n Enter Dimension (minimum 4): "))
        if (Dimension >= 4):
            break
        print("\n Invalid dimension. Please re-enter.")
    # set the dimensions
    MatrixA = set_dimension(Dimension)
    MatrixB = set_dimension(Dimension)
    MatrixC = set_dimension(Dimension)

    # Matrix Multiplication Dimensions
    print(f'\n Matrix Multiplication {Dimension}x{Dimension}x{Dimension}')

    while True:
        _real = int(input("\n Enter Random Maximum Real Value (minimum 10): "))
        if (_real >= 10):
            break
        print("\n Invalid random maximum value. Please re-enter.")

    while True:
        _imag = int(input("\n Enter Random Maximum Imaginary Value (minimum 10): "))
        if (_imag >= 10):
            break
        print("\n Invalid random maximum imaginary value. Please re-enter.")

    MaxRndVal = complex(_real, _imag)

    A = set_random_value(MatrixA, Dimension, MaxRndVal)
    # A.imag = np.random.rand(f, g)
    B = set_random_value(MatrixB, Dimension, MaxRndVal)
    # B.imag = np.random.rand(g, h)
    C = set_random_value(MatrixC, Dimension, 0)

    # display matrix
    print("\n Display Matrix A - DaCe:")
    print(A)
    print("\n Display Matrix B - DaCe:")
    print(B)

    # matrix multiplication - DaCe - using gemm method
    print("\n Start matrix multiplication - DaCe - using gemm method...")
    multmul_Gemm_Final(A, B, C)

    # matrix non-parallel multiplication - DaCe - using numpy interface
    print("\n Start matrix multiplication - DaCe - using numpy interface...")
    multmul_Libnode_Final(A, B, C)

    # display result matrix
    print("\nDisplay Result Matrix C - DaCe:")
    print(C)

    # # Display multiplication - DaCe elapsed time
    # print("\nGemm method - Time taken - DaCe on CPU (in ms) = {}".format(time_taken * 1000))
    #
    # # Display non-parallel multiplication - DaCe elapsed time
    # print("\nNumpy interface - Time taken - DaCe on CPU (in ms) = {}".format(time_taken1 * 1000))

    # set random value in the matrix
    MatrixA = set_random_value(MatrixA, Dimension, MaxRndVal)
    MatrixB = set_random_value(MatrixB, Dimension, MaxRndVal)
    MatrixC = set_random_value(MatrixC, Dimension, 0)  # because of result matrix must be zero

    # matrix non-parallel multiplication
    print("\nStart non-parallel multiplication...")
    Elapsed = matrix_multiplication(Dimension)

    # display matrix
    print("\nDisplay Matrix A:")
    print(MatrixA)
    print("\nDisplay Matrix B:")
    print(MatrixB)

    # Display non-parallel multiplication elapsed time
    print("\nNon-parallel multiplication elapsed time: ", Elapsed, "ms")

    # matrix parallel multiplication
    print("\nStart parallel multiplication...")
    ParallelElapsed = matrix_parallel_multiplication(Dimension)

    # Display parallel multiplication elapsed time
    print("\nParallel multiplication elapsed time: ", ParallelElapsed, "ms")

    # display result matrix
    print("\nDisplay Result Matrix C:")
    print(MatrixC)

    # difference of two process
    print("\nDifference of two process is: ", Elapsed - ParallelElapsed, "ms")

    # difference of two process
    print("\nDifference of two process is: ", (Elapsed - ParallelElapsed) / 1000, "s")

    print("\n ==== Program end ====")

if __name__ == '__main__':
    main()
