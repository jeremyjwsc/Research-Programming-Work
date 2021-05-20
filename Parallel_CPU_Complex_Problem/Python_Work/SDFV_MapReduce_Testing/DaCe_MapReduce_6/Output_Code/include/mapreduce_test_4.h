typedef void * mapreduce_test_4Handle_t;
extern "C" mapreduce_test_4Handle_t __dace_init_mapreduce_test_4(int K, int M, int N);
extern "C" void __dace_exit_mapreduce_test_4(mapreduce_test_4Handle_t handle);
extern "C" void __program_mapreduce_test_4(mapreduce_test_4Handle_t handle, double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, double * __restrict__ D, int K, int M, int N);
