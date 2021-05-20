typedef void * mapreduce_testHandle_t;
extern "C" mapreduce_testHandle_t __dace_init_mapreduce_test(int H, int W);
extern "C" void __dace_exit_mapreduce_test(mapreduce_testHandle_t handle);
extern "C" void __program_mapreduce_test(mapreduce_testHandle_t handle, float * __restrict__ A, float * __restrict__ B, float * __restrict__ sum, int H, int W);
