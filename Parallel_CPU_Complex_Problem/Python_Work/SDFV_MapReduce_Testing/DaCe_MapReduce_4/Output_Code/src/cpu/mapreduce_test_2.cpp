/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"

struct mapreduce_test_2_t {

};

inline void reduce_0_0_8(mapreduce_test_2_t *__state, double* _in, double* _out, int K, int M, int N) {

    {


        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < M; _o0 += 1) {
                for (auto _o1 = 0; _o1 < K; _o1 += 1) {
                    {
                        double out;

                        ///////////////////
                        // Tasklet code (reduce_init)
                        out = 0;
                        ///////////////////

                        _out[((K * _o0) + _o1)] = out;
                    }
                }
            }
        }

    }
    {


        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < M; _o0 += 1) {
                for (auto _o1 = 0; _o1 < K; _o1 += 1) {
                    {
                        for (auto _i0 = 0; _i0 < N; _i0 += 1) {
                            {
                                double inp = _in[((((K * N) * _o0) + (N * _o1)) + _i0)];
                                double out;

                                ///////////////////
                                // Tasklet code (identity)
                                out = inp;
                                ///////////////////

                                dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce(_out + ((K * _o0) + _o1), out);
                            }
                        }
                    }
                }
            }
        }

    }
    
}

void __program_mapreduce_test_2_internal(mapreduce_test_2_t *__state, double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int K, int M, int N)
{

    {
        double *tmp;
        tmp = new double DACE_ALIGN(64)[((K * M) * N)];
        double* __tmp1 = &C[0];


        {
            #pragma omp parallel for
            for (auto j = 0; j < K; j += 1) {
                for (auto k = 0; k < N; k += 1) {
                    for (auto i = 0; i < M; i += 1) {
                        {
                            double in_A = A[((N * i) + k)];
                            double in_B = B[((K * k) + j)];
                            double out;

                            ///////////////////
                            // Tasklet code (multiplication)
                            out = (in_A * in_B);
                            ///////////////////

                            tmp[((((K * N) * i) + (N * j)) + k)] = out;
                        }
                    }
                }
            }
        }
        reduce_0_0_8(__state, &tmp[0], &__tmp1[0], K, M, N);
        delete[] tmp;

    }
}

DACE_EXPORTED void __program_mapreduce_test_2(mapreduce_test_2_t *__state, double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int K, int M, int N)
{
    __program_mapreduce_test_2_internal(__state, A, B, C, K, M, N);
}

DACE_EXPORTED mapreduce_test_2_t *__dace_init_mapreduce_test_2(int K, int M, int N)
{
    int __result = 0;
    mapreduce_test_2_t *__state = new mapreduce_test_2_t;



    if (__result) {
        delete __state;
        return nullptr;
    }
    return __state;
}

DACE_EXPORTED void __dace_exit_mapreduce_test_2(mapreduce_test_2_t *__state)
{
    delete __state;
}

