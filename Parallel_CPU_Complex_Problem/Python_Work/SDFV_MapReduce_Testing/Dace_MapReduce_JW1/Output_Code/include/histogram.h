typedef void * histogramHandle_t;
extern "C" histogramHandle_t __dace_init_histogram(int H, int W);
extern "C" void __dace_exit_histogram(histogramHandle_t handle);
extern "C" void __program_histogram(histogramHandle_t handle, unsigned char * __restrict__ A, unsigned int * __restrict__ hist, int H, int W);
