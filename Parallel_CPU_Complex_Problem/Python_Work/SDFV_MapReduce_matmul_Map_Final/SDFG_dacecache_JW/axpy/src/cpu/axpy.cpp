/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"

struct axpy_t {

};

void __program_axpy_internal(axpy_t *__state, double * __restrict__ X, double * __restrict__ Y, double A, int N)
{

    {


        {
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                {
                    double in_A = A;
                    double in_X = X[i];
                    double in_Y = Y[i];
                    double out;

                    ///////////////////
                    // Tasklet code (multiplication)
                    out = ((in_A * in_X) + in_Y);
                    ///////////////////

                    Y[i] = out;
                }
            }
        }

    }
}

DACE_EXPORTED void __program_axpy(axpy_t *__state, double * __restrict__ X, double * __restrict__ Y, double A, int N)
{
    __program_axpy_internal(__state, X, Y, A, N);
}

DACE_EXPORTED axpy_t *__dace_init_axpy(double A, int N)
{
    int __result = 0;
    axpy_t *__state = new axpy_t;



    if (__result) {
        delete __state;
        return nullptr;
    }
    return __state;
}

DACE_EXPORTED void __dace_exit_axpy(axpy_t *__state)
{
    delete __state;
}

