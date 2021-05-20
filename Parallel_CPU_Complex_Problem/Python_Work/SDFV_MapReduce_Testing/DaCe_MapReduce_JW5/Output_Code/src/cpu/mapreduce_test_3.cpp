/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"

struct mapreduce_test_3_t {

};

inline void reduce_0_0_7(mapreduce_test_3_t *__state, float* _in, float* _out, int H, int W) {

    {


        {
            #pragma omp parallel for
            for (auto _i0 = 0; _i0 < 1; _i0 += 1) {
                for (auto _i1 = 0; _i1 < H; _i1 += 1) {
                    for (auto _i2 = 0; _i2 < 1; _i2 += 1) {
                        for (auto _i3 = 0; _i3 < W; _i3 += 1) {
                            for (auto _i4 = 0; _i4 < 1; _i4 += 1) {
                                {
                                    float inp = _in[((((((H * W) * _i0) + (W * _i1)) + (W * _i2)) + _i3) + _i4)];
                                    float out;

                                    ///////////////////
                                    // Tasklet code (identity)
                                    out = inp;
                                    ///////////////////

                                    dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(_out, out);
                                }
                            }
                        }
                    }
                }
            }
        }

    }
    
}

void __program_mapreduce_test_3_internal(mapreduce_test_3_t *__state, float * __restrict__ A, float * __restrict__ B, float * __restrict__ sum, int H, int W)
{

    {
        float *tmp;
        tmp = new float DACE_ALIGN(64)[(H * W)];


        {
            #pragma omp parallel for
            for (auto i = 0; i < H; i += 1) {
                for (auto j = 0; j < W; j += 1) {
                    {
                        float a = A[((W * i) + j)];
                        float b;
                        float t;

                        ///////////////////
                        // Tasklet code (compute_tile)
                        b = (a * 5);
                        t = (a * 5);
                        ///////////////////

                        B[((W * i) + j)] = b;
                        tmp[((W * i) + j)] = t;
                    }
                }
            }
        }
        reduce_0_0_7(__state, &tmp[0], &sum[0], H, W);
        delete[] tmp;

    }
}

DACE_EXPORTED void __program_mapreduce_test_3(mapreduce_test_3_t *__state, float * __restrict__ A, float * __restrict__ B, float * __restrict__ sum, int H, int W)
{
    __program_mapreduce_test_3_internal(__state, A, B, sum, H, W);
}

DACE_EXPORTED mapreduce_test_3_t *__dace_init_mapreduce_test_3(int H, int W)
{
    int __result = 0;
    mapreduce_test_3_t *__state = new mapreduce_test_3_t;



    if (__result) {
        delete __state;
        return nullptr;
    }
    return __state;
}

DACE_EXPORTED void __dace_exit_mapreduce_test_3(mapreduce_test_3_t *__state)
{
    delete __state;
}

