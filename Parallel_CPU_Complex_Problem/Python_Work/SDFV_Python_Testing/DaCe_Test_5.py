from __future__ import print_function

import argparse
import dace
import numpy as np
from typing import List

from dace.transformation.dataflow import (MapReduceFusion, MapFusion,
                                          MapWCRFusion)

# For library node implementations
import dace.libraries.blas

import time

# Define symbolic sizes for arbitrary inputs
F = dace.symbol('F')
G = dace.symbol('G')
H = dace.symbol('H')

# sdfg = dace.SDFG('MatrixMultipy')

# Define data type to use
# Complex number, represented by two 64-bit floats (real and imaginary components)
dtype = dace.complex128
np_dtype = np.complex128

# A = np.array([[1+2j,2+4j,3+6j], [4+2j,5+4j,6+6j]])
# B = np.array([[1+2j,1+4j,1+6j], [0+2j,1+4j,0+6j]])

# computing multiplication time on CPU
tic = time.time()

#####################################################################
# Data-centric functions

# Map-Reduce version of matrix multiplication
@dace.program
def matmul_mapreduce(A: dtype[F, G], B: dtype[G, H], C: dtype[F, H]):
    tmp = np.ndarray([F, H, G], dtype=A.dtype)

    # Multiply every pair of values to a large 3D temporary array
    for i, j, k in dace.map[0:G, 0:H, 0:F]:
        with dace.tasklet:
            in_A << A[i, k]
            in_B << B[k, j]
            out >> tmp[i, j, k]

            out = in_A * in_B

    # Sum last dimension of temporary array to obtain resulting matrix
    C[:] = dace.reduce(lambda a, b: a + b, tmp, axis=2, identity=0)

# # Library node version of matrix multiplication, using the numpy interface
# @dace.program
# def matmul_lib(A: dtype[F, G], B: dtype[G, H]):
#     return A @ B

toc = time.time()

time_taken = toc - tic #time in s

sdfg = matmul_mapreduce.to_sdfg()

sdfg

#####################################################################
# Main function

def matmul_main():
    print("\n==== Program begins ==== \n")

    # Arugments
    parser = argparse.ArgumentParser()
    parser.add_argument("-F", type=complex, nargs="?", default=128)
    parser.add_argument("-G", type=complex, nargs="?", default=128)
    parser.add_argument("-H", type=complex, nargs="?", default=128)
    args = vars(parser.parse_args())

    # Prepare data with numpy
    f = args["F"]
    g = args["G"]
    h = args["H"]

    # Matrix Multiplication Dimensions
    print(f'Matrix Multiplication {f}x{g}x{h} \n')

    A = np.random.rand(f, g).astype(np_dtype)
    A.imag = np.random.rand(f, g)
    B = np.random.rand(g, h).astype(np_dtype)
    B.imag = np.random.rand(g, h)
    C = np.zeros((f, h), dtype=np_dtype)

    # expected = A @ B

    matmul_mapreduce(A, B, C)

    # matmul_lib(A, B)

    ComplexMatC = A @ B

    diff = np.linalg.norm(C - ComplexMatC) / np.linalg.norm(ComplexMatC)

    print("\n Matrix A is:\n", A)

    print("\n Matrix B is:\n", B)

    print("\n Matrix multiplication of matrix A and B is:\n", ComplexMatC)

    print('\n Difference:', diff)

    print("\n Time taken on CPU (in ms) = {}".format(time_taken * 1000))

    # exit(0 if diff <= 1e-5 else 1)

    print("\n ==== Program end ====")

    assert diff < 1e-5


if __name__ == "__main__":
    matmul_main()