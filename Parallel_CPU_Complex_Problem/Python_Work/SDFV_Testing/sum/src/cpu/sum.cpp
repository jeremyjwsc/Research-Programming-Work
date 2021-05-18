/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void reduce_0_0_2(float* _in, float* _out, int N) {

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
            for (auto _i0 = 0; _i0 < N; _i0 += 1) {
                {
                    float inp = _in[_i0];
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

void __program_sum_internal(float * __restrict__ A, float * __restrict__ out, int N)
{

    {
        
        
        reduce_0_0_2(&A[0], &out[0], N);
    }
}

DACE_EXPORTED void __program_sum(float * __restrict__ A, float * __restrict__ out, int N)
{
    __program_sum_internal(A, out, N);
}

DACE_EXPORTED int __dace_init_sum(float * __restrict__ A, float * __restrict__ out, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_sum(float * __restrict__ A, float * __restrict__ out, int N)
{
}

