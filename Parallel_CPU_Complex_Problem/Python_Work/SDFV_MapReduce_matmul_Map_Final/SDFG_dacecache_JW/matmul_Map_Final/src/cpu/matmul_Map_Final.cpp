/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"

struct matmul_Map_Final_t {

};

inline void reduce_0_0_7(matmul_Map_Final_t *__state, dace::complex128* _in, dace::complex128* _out, int F, int G, int H) {

    {


        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < F; _o0 += 1) {
                for (auto _o1 = 0; _o1 < H; _o1 += 1) {
                    {
                        dace::complex128 out;

                        ///////////////////
                        // Tasklet code (reduce_init)
                        out = 0;
                        ///////////////////

                        _out[((H * _o0) + _o1)] = out;
                    }
                }
            }
        }

    }
    {


        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < F; _o0 += 1) {
                for (auto _o1 = 0; _o1 < H; _o1 += 1) {
                    {
                        for (auto _i0 = 0; _i0 < G; _i0 += 1) {
                            {
                                dace::complex128 inp = _in[((((G * H) * _o0) + (G * _o1)) + _i0)];
                                dace::complex128 out;

                                ///////////////////
                                // Tasklet code (identity)
                                out = inp;
                                ///////////////////

                                dace::wcr_fixed<dace::ReductionType::Sum, dace::complex128>::reduce(_out + ((H * _o0) + _o1), out);
                            }
                        }
                    }
                }
            }
        }

    }
    
}

void __program_matmul_Map_Final_internal(matmul_Map_Final_t *__state, dace::complex128 * __restrict__ A, dace::complex128 * __restrict__ B, dace::complex128 * __restrict__ C, int F, int G, int H)
{

    {
        dace::complex128 *tmp;
        tmp = new dace::complex128 DACE_ALIGN(64)[((F * G) * H)];


        {
            #pragma omp parallel for
            for (auto i = 0; i < F; i += 1) {
                for (auto j = 0; j < H; j += 1) {
                    for (auto k = 0; k < G; k += 1) {
                        {
                            dace::complex128 in_A = A[((G * i) + k)];
                            dace::complex128 in_B = B[((H * k) + j)];
                            dace::complex128 out;

                            ///////////////////
                            // Tasklet code (matmul_Map_Final_53)
                            out = (in_A * in_B);
                            ///////////////////

                            tmp[((((G * H) * i) + (G * j)) + k)] = out;
                        }
                    }
                }
            }
        }
        reduce_0_0_7(__state, &tmp[0], &C[0], F, G, H);
        delete[] tmp;

    }
}

DACE_EXPORTED void __program_matmul_Map_Final(matmul_Map_Final_t *__state, dace::complex128 * __restrict__ A, dace::complex128 * __restrict__ B, dace::complex128 * __restrict__ C, int F, int G, int H)
{
    __program_matmul_Map_Final_internal(__state, A, B, C, F, G, H);
}

DACE_EXPORTED matmul_Map_Final_t *__dace_init_matmul_Map_Final(int F, int G, int H)
{
    int __result = 0;
    matmul_Map_Final_t *__state = new matmul_Map_Final_t;



    if (__result) {
        delete __state;
        return nullptr;
    }
    return __state;
}

DACE_EXPORTED void __dace_exit_matmul_Map_Final(matmul_Map_Final_t *__state)
{
    delete __state;
}

