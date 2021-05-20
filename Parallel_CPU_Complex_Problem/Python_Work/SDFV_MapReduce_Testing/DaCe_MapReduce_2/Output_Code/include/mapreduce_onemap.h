typedef void * mapreduce_onemapHandle_t;
extern "C" mapreduce_onemapHandle_t __dace_init_mapreduce_onemap(int K, int M, int N);
extern "C" void __dace_exit_mapreduce_onemap(mapreduce_onemapHandle_t handle);
extern "C" void __program_mapreduce_onemap(mapreduce_onemapHandle_t handle, double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int K, int M, int N);
