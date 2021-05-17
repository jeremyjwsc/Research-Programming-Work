/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_cflow_internal(float * __restrict__ A, float * __restrict__ B, int T)
{
    long long k;

    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < 2; i += 1) {
                {
                    float a = A[i];
                    float b;

                    ///////////////////
                    // Tasklet code (aaa2)
                    b = a;
                    ///////////////////

                    B[i] = b;
                }
            }
        }
    }
    for (k = 0; (k < T); k = k+1) {
        {
            
            
            {
                #pragma omp parallel for
                for (auto i = 0; i < 2; i += 1) {
                    {
                        float a = A[i];
                        float b;

                        ///////////////////
                        // Tasklet code (aaa2)
                        b = a;
                        ///////////////////

                        B[i] = b;
                    }
                }
            }
            {
                #pragma omp parallel for
                for (auto i = 0; i < 2; i += 1) {
                    {
                        float a = B[i];
                        float b;

                        ///////////////////
                        // Tasklet code (aaa2)
                        b = a;
                        ///////////////////

                        A[i] = b;
                    }
                }
            }
        }
    }
    {
        
        
        {
            float a = A[0];

            ///////////////////
            // Tasklet code (endtask)
            printf("done %f\n", a);
            ///////////////////

        }
    }
}

DACE_EXPORTED void __program_cflow(float * __restrict__ A, float * __restrict__ B, int T)
{
    __program_cflow_internal(A, B, T);
}

DACE_EXPORTED int __dace_init_cflow(float * __restrict__ A, float * __restrict__ B, int T)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_cflow(float * __restrict__ A, float * __restrict__ B, int T)
{
}

