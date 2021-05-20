typedef void * mapreduce_twomapsHandle_t;
extern "C" mapreduce_twomapsHandle_t __dace_init_mapreduce_twomaps(int K, int M, int N);
extern "C" void __dace_exit_mapreduce_twomaps(mapreduce_twomapsHandle_t handle);
extern "C" void __program_mapreduce_twomaps(mapreduce_twomapsHandle_t handle, double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int K, int M, int N);
