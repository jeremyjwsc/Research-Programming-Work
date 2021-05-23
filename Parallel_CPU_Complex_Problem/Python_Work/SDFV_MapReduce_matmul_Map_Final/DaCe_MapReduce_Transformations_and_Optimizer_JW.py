from __future__ import print_function

import argparse
import dace
import time
import numpy as np
from random import randint

# For library node implementations
import dace.libraries.blas

import multiprocessing
from concurrent.futures import ThreadPoolExecutor

# For transformations
from dace.transformation.dataflow import (MapExpansion, MapReduceFusion,
                                          MapFusion, MapWCRFusion, 
                                          MapTiling, MapCollapse)

# For interactive optimizer 
from dace.transformation.optimizer import Optimizer

from dace.transformation.interstate import StateFusion

# Enumerating Matches
from dace.transformation.pattern_matching import enumerate_matches
from dace.sdfg import utils as sdutil  # For creating path graphs

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

#####################################################################
#Data-centric functions
    
# Map-Reduce version of matrix multiplication
@dace.program
def matmul_Map_Final(A: dtype[F, G], B: dtype[G, H], C: dtype[F, H]):
    # Transient variable
    tmp = dace.define_local([F, H, G], dtype=A.dtype)

    # Multiply every pair of values to a large 3D temporary array
    @dace.map
    def mult_Map_Final(i: _[0:F], j: _[0:H], k: _[0:G]):
            in_A << A[i, k]
            in_B << B[k, j]
            out >> tmp[i, j, k]

            out = in_A * in_B

    # Sum last dimension of temporary array to obtain resulting matrix
    dace.reduce(lambda a, b: a + b, tmp, C, axis=2, identity=0)

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
        pool.map(matrixmul, [(ii, jj, Dimension) 
                             for ii in range(Dimension) 
                             for jj in range(Dimension)])

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
    global _real
    global _imag
    global MaxRndVal
    global Elapsed
    global ParallelElapsed
    
    # Arugments
    parser = argparse.ArgumentParser()
    parser.add_argument("-F", type=complex, nargs="?", default=Dimension)
    parser.add_argument("-G", type=complex, nargs="?", default=Dimension)
    parser.add_argument("-H", type=complex, nargs="?", default=Dimension)
    args = vars(parser.parse_args())

    # Prepare Arugments
    f = args["F"]
    g = args["G"]
    h = args["H"]

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

    MaxRndVal = complex(_real, _imag)

    A = set_random_value(MatrixA, Dimension, MaxRndVal)
    B = set_random_value(MatrixA, Dimension, MaxRndVal)
    C = set_random_value(MatrixC, Dimension, 0)

    # Display First Matrix Multiply Processes - DaCe
    print("\n DaCe - MapReduce Process 0...")

    # display matrix
    print("\n Display Matrix A - DaCe")
    print(A)
    print("\n Display Matrix B - DaCe")
    print(B)
    
    ticmap = time.time()
    # matrix non-parallel multiplication - DaCe using gemm method
    print("\n Starting DaCe MapReduce Process 0: matrix multiplicationsdfg.optimize() - DaCe using map reduce...")
    matmul_Map_Final(A, B, C)
    tocmap = time.time()
    time_takenmap = tocmap - ticmap  # time in s
    
    # Apply Transformations
    sdfg = matmul_Map_Final.to_sdfg()
    sdfg.apply_strict_transformations()
    sdfg.apply_transformations([MapFusion, MapWCRFusion, StateFusion])
    sdfg.apply_transformations_repeated([MapFusion, MapWCRFusion, StateFusion])
    
    # Feed Symbols
    sdfg(A=A, B=B, C=C, F=f, G=g, H=h) 
    
    # Enumerating Matches
    for xform in Optimizer(sdfg).get_pattern_matches(patterns=[MapTiling]):
        print("Match:", xform.print_match(sdfg))
        
    # Construct subgraph pattern (MapExit -> AccessNode -> MapEntry)
    pattern = sdutil.node_path_graph(dace.nodes.MapExit, dace.nodes.AccessNode,
                                      dace.nodes.MapEntry)
    # Loop over matches
    for subgraph in enumerate_matches(sdfg, pattern):
        print("Match found in state", subgraph.graph.label, ". Nodes:", subgraph.nodes())
        

    # Interactive Optimization
    sdfg.optimize()
    
    # Display non-parallel multiplication - DaCe elapsed time
    print("\n Time taken - DaCe MapReduce x1 on CPU - Serial (in ms) = {}".format(time_takenmap * 1000))

    # Display matrix multiplication elapsed time
    print("\n Matrix multiplication DACE MapReduce - elapsed time: {}".format(time_takenmap), "s")    

    # display result matrix
    print("\n Display Result Matrix C - DaCe")
    print(C)

    # set random value in the matrix
    MatrixA = set_random_value(MatrixA, Dimension, MaxRndVal)
    MatrixB = set_random_value(MatrixB, Dimension, MaxRndVal)
    MatrixC = set_random_value(MatrixC, Dimension, 0)  # because of result matrix must be zero

    # Display Second Matrix Multiply Processes - non-DaCe
    print("\n Non-DaCe Matrix Multiplication Process 1 and 2 Review....")

    # display matrix
    print("\n Display Matrix A")
    print(MatrixA)
    print("\n Display Matrix B")
    print(MatrixB)

    # matrix non-parallel multiplication
    print("\n Starting Process 1: non-parallel matrix multiplication ...")
    Elapsed = matrix_multiplication(Dimension)

    # Display non-parallel multiplication elapsed time
    print("\n Non-parallel multiplication elapsed time: ", Elapsed, "ms")

    # matrix parallel multiplication
    print("\n Starting Process 2: parallel matrix multiplication...")
    ParallelElapsed = matrix_parallel_multiplication(Dimension)

    # Display parallel multiplication elapsed time
    print("\n Parallel multiplication elapsed time: ", ParallelElapsed, "ms")

    # display result matrix
    print("\n Display Result Matrix C")
    print(MatrixC)

    # difference of two process
    print("\n Difference of non-DACE process 1 and 2 is: ", (Elapsed * 1000) - (ParallelElapsed * 1000), "ms")

    # difference of two process
    print("\n Difference of non-DACE process 1 and 2 is: ", (Elapsed) - (ParallelElapsed), "s")

    expected = MatrixA @ MatrixB
           

    diff = np.linalg.norm(MatrixC - expected)

    print('\n Difference:', diff)

    # exit(0 if diff <= 1e-5 else 1)
    
    assert diff < 1e-5

    print("\n ==== Program end ==== \n")


if __name__ == '__main__':
    main()
