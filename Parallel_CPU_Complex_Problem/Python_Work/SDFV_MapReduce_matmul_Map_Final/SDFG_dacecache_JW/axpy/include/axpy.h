typedef void * axpyHandle_t;
extern "C" axpyHandle_t __dace_init_axpy(double A, int N);
extern "C" void __dace_exit_axpy(axpyHandle_t handle);
extern "C" void __program_axpy(axpyHandle_t handle, double * __restrict__ X, double * __restrict__ Y, double A, int N);
