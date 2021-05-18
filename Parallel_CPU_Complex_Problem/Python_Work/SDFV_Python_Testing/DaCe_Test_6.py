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

sdfg = dace.SDFG('MatrixMultipy')

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
def matmul(A: dtype[F, G], B: dtype[G, H], C: dtype[F, H]):
    tmp = np.ndarray([F, H, G], dtype=A.dtype)

    # Multiply every pair of values to a large 3D temporary array
    for i, j, k in dace.map[0:F, 0:H, 0:G]:
        with dace.tasklet:
            in_A << A[i, k]
            in_B << B[k, j]
            out >> tmp[i, j, k]

            out = in_A * in_B

    # Sum last dimension of temporary array to obtain resulting matrix
    dace.reduce(lambda a, b: a + b, tmp, C, axis=2, identity=0)

# Library node version of matrix multiplication, using the numpy interface
@dace.program
def matmul_lib(A: dtype[F, G], B: dtype[G, H]):
    return A @ B

toc = time.time()

time_taken = toc - tic #time in s

#####################################################################
# Main function

def matmul_main():
    F.set(128)
    H.set(128)
    G.set(128)

    print('Matrix multiplication %dx%dx%d' % (F.get(), H.get(), G.get()))

    # # Arugments
    # parser = argparse.ArgumentParser()
    # parser.add_argument("-F", type=complex, nargs="?", default=128)
    # parser.add_argument("-G", type=complex, nargs="?", default=128)
    # parser.add_argument("-H", type=complex, nargs="?", default=128)
    # args = vars(parser.parse_args())
    #
    # # Prepare data with numpy
    # f = args["F"]
    # g = args["G"]
    # h = args["H"]
    A = np.random.rand(F.get(), G.get()).astype(np_dtype)
    A.imag = np.random.rand(F.get(), G.get())

    B = np.random.rand(G.get(), H.get()).astype(np_dtype)
    B.imag = np.random.rand(G.get(), H.get())

    #C = np.zeros([M.get(), N.get()], np.float64)
    C = np.zeros((F.get(), H.get()), dtype=np_dtype)

    ComplexMatC = A @ B

    # A = np.random.rand(f, g).astype(np_dtype)
    # A.imag = np.random.rand(f, g)
    # B = np.random.rand(g, h).astype(np_dtype)
    # B.imag = np.random.rand(g, h)
    # C = np.zeros((f, h), dtype=np_dtype)

    matmul(A, B, C)

    # expected = A @ B

    sdfg = program.to_sdfg()
    sdfg.apply_strict_transformations()
    sdfg.apply_transformations([MapFusion, MapWCRFusion])
    sdfg(A=A, B=B, C=C, F=F, H=H, G=G)

    diff = np.linalg.norm(C - ComplexMatC) / (F.get() * H.get())

    # diff = np.linalg.norm(C - ComplexMatC) / np.linalg.norm(ComplexMatC)

    # diff = np.linalg.norm(C - expected) / (f * h)

    print("Matrix A is:\n", A)

    print("Matrix B is:\n", B)

    print("Matrix multiplication of matrix A and B is:\n", ComplexMatC)

    print('Difference:', diff)

    print("Time taken on CPU (in ms) = {}".format(time_taken * 1000))

    #exit(0 if diff <= 1e-5 else 1)

    print("==== Program end ====")

    assert diff < 1e-5


if __name__ == "__main__":
    matmul_main()