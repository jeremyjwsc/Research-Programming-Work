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
DaCe_Parallel = 0
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

#####################################################################
#Data-centric functions

# Map-Reduce version of matrix multiplication
@dace.program
def matmul_Map_Final(A: dtype[F, G], B: dtype[G, H], C: dtype[F, H]):
    tmp = dace.define_local([F, H, G], dtype=A.dtype)

    # Multiply every pair of values to a large 3D temporary array
    for i, j, k in dace.map[0:F, 0:H, 0:G]:
        with dace.tasklet:
            in_A << A[i, k]
            in_B << B[k, j]
            out >> tmp[i, j, k]

            out = in_A * in_B

    # Sum last dimension of temporary array to obtain resulting matrix
    dace.reduce(lambda a, b: a + b, tmp, C, axis=2, identity=0)


# Generalized matrix multiplication (gemm method)
@dace.program
def multmul_Gemm_Final(A: dtype[F, G], B: dtype[G, H], C: dtype[F, H]):
    C[:] = A @ B

# toc = time.time()
#
# time_taken = toc - tic  # time in s

# # Generalized matrix-matrix multiplication (gemm method)
# @dace.program(dtype[F, G], dtype[G, H], dtype[F, H])
# def matmul_Update_Parallel(A, B, C):
#
#     C[:] = A @ B

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

def matrix_parallel_multiplication_DACE_Gemm(DaCe_Parallel):
    start = time.time()
    cpucount = multiprocessing.cpu_count()

    with ThreadPoolExecutor(cpucount) as pool:
        result = pool.map(multmul_Gemm_Final, [(C, DaCe_Parallel) for C in range(DaCe_Parallel)])
    end = time.time()
    return end - start

def matrix_parallel_multiplication_DACE_Lib(DaCe_Parallel):
    start = time.time()
    cpucount = multiprocessing.cpu_count()

    with ThreadPoolExecutor(cpucount) as pool:
        result = pool.map(multmul_Libnode_Final, [(C, DaCe_Parallel) for C in range(DaCe_Parallel)])
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
    print("\n There are %d CPUs on this machine." % multiprocessing.cpu_count())
    global MatrixA
    global MatrixB
    global MatrixC
    global Dimension
    global DaCe_Parallel
    global _real
    global _imag
    global MaxRndVal
    global Elapsed
    global ParallelElapsed

    while True:
        Dimension = int(input("\n Enter Dimension (minimum 4): "))
        if (Dimension >= 4):
            break
        print("\n Invalid dimension. Please re-enter (minimum 4).")
    # set the dimensions
    MatrixA = set_dimension(Dimension)
    MatrixB = set_dimension(Dimension)
    MatrixC = set_dimension(Dimension)

    while True:
        _real = int(input("\n Enter Random Maximum Real Value (minimum 10): "))
        if (_real >= 10):
            break
        print("\n Invalid random maximum value. Please re-enter (minimum 10).")

    while True:
        _imag = int(input("\n Enter Random Maximum Imaginary Value (minimum 10): "))
        if (_imag >= 10):
            break
        print("\n Invalid random maximum imaginary value. Please re-enter (minimum 10).")

    while True:
        DaCe_Parallel = int(input("\n Enter Multiple Parallel DaCe Program Value (minimum 10): "))
        if (DaCe_Parallel >= 10):
            break
        print("\n Invalid parallel DaCe program execution value. Please re-enter (minimum 10).")

    MaxRndVal = complex(_real, _imag)

    A = set_random_value(MatrixA, Dimension, MaxRndVal)
    # A.imag = np.random.rand(f, g)
    B = set_random_value(MatrixA, Dimension, MaxRndVal)
    # B.imag = np.random.rand(g, h)
    C = set_random_value(MatrixC, Dimension, 0)

    # Display First Matrix Multiply Processes - DaCe
    print("\n DaCe - MapReduce Process 0, Serial Process 1 & 2 and Parallel Process 3 & 4 Review....")

    # display matrix
    print("\n Display Matrix A - DaCe")
    print(A)
    print("\n Display Matrix B - DaCe")
    print(B)
    
    
    ticmap = time.time()
    # matrix non-parallel multiplication - DaCe using gemm method
    print("\n Starting DaCe MapReduce Process 0: matrix multiplication - DaCe using map reduce...")
    matmul_Map_Final(A, B, C)
    tocmap = time.time()
    time_takenmap = tocmap - ticmap  # time in s
    
    
    matmul_Map_Final.to_sdfg()
    
    # Display non-parallel multiplication - DaCe elapsed time
    print("\n Time taken - DaCe MapReduce x1 on CPU - Serial (in ms) = {}".format(time_takenmap * 1000))

    # Display matrix multiplication elapsed time
    print("\n Matrix multiplication DACE MapReduce - elapsed time: {}".format(time_takenmap), "s")

    tic1 = time.time()
    # matrix non-parallel multiplication - DaCe using gemm method
    print("\n Starting Process 1: non-parallel matrix multiplication - DaCe using gemm method...")
    multmul_Gemm_Final(A, B, C)
    toc1 = time.time()
    time_taken1 = toc1 - tic1  # time in s

    multmul_Gemm_Final.to_sdfg()

    # Display non-parallel multiplication - DaCe elapsed time
    print("\n Time taken - DaCe using gemm method x1 on CPU - Serial (in ms) = {}".format(time_taken1 * 1000))

    # Display matrix multiplication elapsed time
    print("\n Matrix multiplication DACE using gemm method - elapsed time: {}".format(time_taken1), "s")

    tic2 = time.time()
    # matrix non-parallel multiplication - DaCe - using numpy interface
    print("\n Starting Process 2: non-parallel matrix multiplication - DaCe using numpy interface...")
    multmul_Libnode_Final(A, B, C)
    toc2 = time.time()
    time_taken2 = toc2 - tic2  # time in s

    multmul_Libnode_Final.to_sdfg()

    # Display non-parallel multiplication - DaCe elapsed time using numpy interface
    print("\n Time taken - DaCe using numpy interface x1 on CPU - Serial (in ms) = {}".format(time_taken2 * 1000))

    # Display matrix multiplication elapsed time using numpy interface
    print("\n Matrix multiplication DACE using numpy interface - elapsed time: {}".format(time_taken2), "s")

    # tic1 = time.time()
    # # matrix non-parallel multiplication - DaCe
    # print("\n Start parallel matrix multiplication - DaCe...")
    # matmul_Update_Parallel(A, B, C)
    # toc1 = time.time()
    # time_taken1 = toc1 - tic1  # time in s

    # # Display parallel multiplication - DaCe elapsed time
    # print("\n Time taken - DaCe on CPU - Parallel (in ms) = {}".format((time_taken1 * 1000)))

    tic3 = time.time()
    # matrix parallel multiplication DACE using gemm method
    print("\n Starting Process 3: parallel multiplication DACE using gemm method ", "x%d" %DaCe_Parallel)
    ParallelElapsedDaCeGemm = matrix_parallel_multiplication_DACE_Gemm(DaCe_Parallel)
    # ParallelElapsedDaCe = matrix_parallel_multiplication_DACE(DaCe_Parallel)
    toc3 = time.time()
    time_taken3 = toc3 - tic3  # time in s

    # Display parallel multiplication - DaCe using gemm method - elapsed time
    print("\n Time taken - DaCe using gemm method x%d on CPU - Parallel (in ms) = {}".format((time_taken3 * 1000) / DaCe_Parallel) %DaCe_Parallel)

    # Display parallel multiplication elapsed time
    print("\n Parallel Matrix Multiplication DACE using gemm method - elapsed time: ", ParallelElapsedDaCeGemm / DaCe_Parallel, "s")

    # difference of two processes using gemm method
    print("\n Difference of DACE process using gemm method 1 and 3 is: {}".format((time_taken1) - (ParallelElapsedDaCeGemm / DaCe_Parallel)), "s")


    tic4 = time.time()
    # matrix parallel multiplication DACE using numpy interface
    print("\n Starting Process 4: parallel multiplication DACE using numpy interface ", "x%d" % DaCe_Parallel)
    ParallelElapsedDaCeLib = matrix_parallel_multiplication_DACE_Lib(DaCe_Parallel)
    # ParallelElapsedDaCe = matrix_parallel_multiplication_DACE(DaCe_Parallel)
    toc4 = time.time()
    time_taken4 = toc4 - tic4  # time in s

    # Display parallel multiplication - DaCe elapsed time using numpy interface
    print("\n Time taken - DaCe using numpy interface x%d on CPU - Parallel (in ms) = {}".format((time_taken4 * 1000) / DaCe_Parallel) % DaCe_Parallel)

    # Display parallel multiplication elapsed time
    print("\n Parallel Matrix Multiplication DACE using numpy interface - elapsed time: ", ParallelElapsedDaCeLib / DaCe_Parallel, "s")

    # difference of two processes using numpy interface
    print("\n Difference of DACE process using numpy interface 2 and 4 is: {}".format((time_taken2) - (ParallelElapsedDaCeLib / DaCe_Parallel)), "s")

    # matmul_Update_Parallel.to_sdfg()

    # display result matrix
    print("\n Display Result Matrix C - DaCe")
    print(C)

    # set random value in the matrix
    MatrixA = set_random_value(MatrixA, Dimension, MaxRndVal)
    MatrixB = set_random_value(MatrixB, Dimension, MaxRndVal)
    MatrixC = set_random_value(MatrixC, Dimension, 0)  # because of result matrix must be zero

    # Display Second Matrix Multiply Processes - non-DaCe
    print("\n Non-DaCe Matrix Multiplication Process 5 and 6 Review....")

    # display matrix
    print("\n Display Matrix A")
    print(MatrixA)
    print("\n Display Matrix B")
    print(MatrixB)

    # matrix non-parallel multiplication
    print("\n Starting Process 3: non-parallel matrix multiplication ...")
    Elapsed = matrix_multiplication(Dimension)

    # Display non-parallel multiplication elapsed time
    print("\n Non-parallel multiplication elapsed time: ", Elapsed * 1000, "ms")

    # matrix parallel multiplication
    print("\n Starting Process 4: parallel matrix multiplication...")
    ParallelElapsed = matrix_parallel_multiplication(Dimension)

    # Display parallel multiplication elapsed time
    print("\n Parallel multiplication elapsed time: ", ParallelElapsed * 1000, "ms")

    # # Display parallel multiplication elapsed time
    # print("\n Parallel multiplication DACE elapsed time: ", ParallelElapsedDaCe/DaCe_Parallel, "ms")

    # display result matrix
    print("\n Display Result Matrix C")
    print(MatrixC)

    # difference of two process
    print("\n Difference of non-DACE process 5 and 6 is: ", (Elapsed * 1000) - (ParallelElapsed * 1000), "ms")

    # difference of two process
    print("\n Difference of non-DACE process 5 and 6 is: ", (Elapsed) - (ParallelElapsed), "s")

    # # difference of two process
    # print("\n Difference of two process is: ", (Elapsed - ParallelElapsed) / 1000, "s")

    expected = MatrixA @ MatrixB

    diff = np.linalg.norm(MatrixC - expected)

    print('\n Difference:', diff)

    # exit(0 if diff <= 1e-5 else 1)
    
    assert diff < 1e-5

    print("\n ==== Program end ==== \n")


if __name__ == '__main__':
    main()