/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"

struct histogram_t {

};

void __program_histogram_internal(histogram_t *__state, unsigned char * __restrict__ A, unsigned int * __restrict__ hist, int H, int W)
{

    {
        unsigned int *tmp;
        tmp = new unsigned int DACE_ALIGN(64)[((256 * H) * W)];


        {
            #pragma omp parallel for
            for (auto i = 0; i < H; i += 1) {
                for (auto j = 0; j < W; j += 1) {
                    for (auto b = 0; b < 256; b += 1) {
                        {
                            unsigned int t;

                            ///////////////////
                            // Tasklet code (zero_tmp)
                            t = 0;
                            ///////////////////

                            tmp[((((H * W) * b) + (W * i)) + j)] = t;
                        }
                    }
                }
            }
        }
        delete[] tmp;

    }
    {


        {
            #pragma omp parallel for
            for (auto i = 0; i < H; i += 1) {
                for (auto j = 0; j < W; j += 1) {
                    {
                        unsigned char a = A[((W * i) + j)];
                        unsigned int* out = hist;

                        ///////////////////
                        // Tasklet code (compute_declarative)
                        dace::wcr_fixed<dace::ReductionType::Sum, unsigned int>::reduce_atomic(hist + a, 1);
                        ///////////////////

                    }
                }
            }
        }

    }
}

DACE_EXPORTED void __program_histogram(histogram_t *__state, unsigned char * __restrict__ A, unsigned int * __restrict__ hist, int H, int W)
{
    __program_histogram_internal(__state, A, hist, H, W);
}

DACE_EXPORTED histogram_t *__dace_init_histogram(int H, int W)
{
    int __result = 0;
    histogram_t *__state = new histogram_t;



    if (__result) {
        delete __state;
        return nullptr;
    }
    return __state;
}

DACE_EXPORTED void __dace_exit_histogram(histogram_t *__state)
{
    delete __state;
}

