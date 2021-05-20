typedef void * mapreduce_test_2Handle_t;
extern "C" mapreduce_test_2Handle_t __dace_init_mapreduce_test_2(int K, int M, int N);
extern "C" void __dace_exit_mapreduce_test_2(mapreduce_test_2Handle_t handle);
extern "C" void __program_mapreduce_test_2(mapreduce_test_2Handle_t handle, double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int K, int M, int N);
