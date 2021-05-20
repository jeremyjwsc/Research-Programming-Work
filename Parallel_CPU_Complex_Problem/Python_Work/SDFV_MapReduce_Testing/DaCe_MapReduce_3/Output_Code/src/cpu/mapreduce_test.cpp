/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"

struct mapreduce_test_t {

};

inline void reduce_0_0_9(mapreduce_test_t *__state, float* _in, float* _out, int H, int W) {

    {


        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < 1; _o0 += 1) {
                {
                    float out;

                    ///////////////////
                    // Tasklet code (reduce_init)
                    out = 0;
                    ///////////////////

                    _out[_o0] = out;
                }
            }
        }

    }
    {


        {
            #pragma omp parallel for
            for (auto _i0 = 0; _i0 < H; _i0 += 1) {
                for (auto _i1 = 0; _i1 < W; _i1 += 1) {
                    {
                        float inp = _in[((W * _i0) + _i1)];
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

void __program_mapreduce_test_internal(mapreduce_test_t *__state, float * __restrict__ A, float * __restrict__ B, float * __restrict__ sum, int H, int W)
{

    {
        float *tmp;
        tmp = new float DACE_ALIGN(64)[(H * W)];
        float *__tmp1;
        __tmp1 = new float DACE_ALIGN(64)[1];


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
        reduce_0_0_9(__state, &tmp[0], &__tmp1[0], H, W);
        {
            float __inp = __tmp1[0];
            float __out;

            ///////////////////
            // Tasklet code (assign_48_4)
            __out = __inp;
            ///////////////////

            sum[0] = __out;
        }
        delete[] tmp;
        delete[] __tmp1;

    }
}

DACE_EXPORTED void __program_mapreduce_test(mapreduce_test_t *__state, float * __restrict__ A, float * __restrict__ B, float * __restrict__ sum, int H, int W)
{
    __program_mapreduce_test_internal(__state, A, B, sum, H, W);
}

DACE_EXPORTED mapreduce_test_t *__dace_init_mapreduce_test(int H, int W)
{
    int __result = 0;
    mapreduce_test_t *__state = new mapreduce_test_t;



    if (__result) {
        delete __state;
        return nullptr;
    }
    return __state;
}

DACE_EXPORTED void __dace_exit_mapreduce_test(mapreduce_test_t *__state)
{
    delete __state;
}

