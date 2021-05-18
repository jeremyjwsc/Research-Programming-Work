/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void _MatMult__sdfg_0_0_3(dace::complex128* _a, dace::complex128* _b, dace::complex128* _c, int F, int G, int H) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < F; _o0 += 1) {
                for (auto _o1 = 0; _o1 < H; _o1 += 1) {
                    {
                        dace::complex128 out;

                        ///////////////////
                        // Tasklet code (gemm_init)
                        out = 0;
                        ///////////////////

                        _c[((H * _o0) + _o1)] = out;
                    }
                }
            }
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < F; __i0 += 1) {
                for (auto __i1 = 0; __i1 < H; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < G; __i2 += 1) {
                        {
                            dace::complex128 __a = _a[((G * __i0) + __i2)];
                            dace::complex128 __b = _b[((H * __i2) + __i1)];
                            dace::complex128 __out;

                            ///////////////////
                            // Tasklet code (_GEMM_)
                            __out = (__a * __b);
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, dace::complex128>::reduce_atomic(_c + ((H * __i0) + __i1), __out);
                        }
                    }
                }
            }
        }
    }
    
}

void __program_matmul_lib_internal(dace::complex128 * __restrict__ A, dace::complex128 * __restrict__ B, dace::complex128 * __restrict__ __return, int F, int G, int H)
{

    {
        
        
        _MatMult__sdfg_0_0_3(&A[0], &B[0], &__return[0], F, G, H);
    }
}

DACE_EXPORTED void __program_matmul_lib(dace::complex128 * __restrict__ A, dace::complex128 * __restrict__ B, dace::complex128 * __restrict__ __return, int F, int G, int H)
{
    __program_matmul_lib_internal(A, B, __return, F, G, H);
}

DACE_EXPORTED int __dace_init_matmul_lib(dace::complex128 * __restrict__ A, dace::complex128 * __restrict__ B, dace::complex128 * __restrict__ __return, int F, int G, int H)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_matmul_lib(dace::complex128 * __restrict__ A, dace::complex128 * __restrict__ B, dace::complex128 * __restrict__ __return, int F, int G, int H)
{
}

