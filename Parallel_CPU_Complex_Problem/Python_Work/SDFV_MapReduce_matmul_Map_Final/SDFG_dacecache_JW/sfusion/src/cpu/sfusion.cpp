/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"

struct sfusion_t {

};

void __program_sfusion_internal(sfusion_t *__state, float * __restrict__ A, float * __restrict__ B)
{

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

DACE_EXPORTED void __program_sfusion(sfusion_t *__state, float * __restrict__ A, float * __restrict__ B)
{
    __program_sfusion_internal(__state, A, B);
}

DACE_EXPORTED sfusion_t *__dace_init_sfusion()
{
    int __result = 0;
    sfusion_t *__state = new sfusion_t;



    if (__result) {
        delete __state;
        return nullptr;
    }
    return __state;
}

DACE_EXPORTED void __dace_exit_sfusion(sfusion_t *__state)
{
    delete __state;
}

