typedef void * sfusionHandle_t;
extern "C" sfusionHandle_t __dace_init_sfusion();
extern "C" void __dace_exit_sfusion(sfusionHandle_t handle);
extern "C" void __program_sfusion(sfusionHandle_t handle, float * __restrict__ A, float * __restrict__ B);
