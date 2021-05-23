typedef void * matmul_Map_FinalHandle_t;
extern "C" matmul_Map_FinalHandle_t __dace_init_matmul_Map_Final(int F, int G, int H);
extern "C" void __dace_exit_matmul_Map_Final(matmul_Map_FinalHandle_t handle);
extern "C" void __program_matmul_Map_Final(matmul_Map_FinalHandle_t handle, dace::complex128 * __restrict__ A, dace::complex128 * __restrict__ B, dace::complex128 * __restrict__ C, int F, int G, int H);
