typedef void * mapreduce_test_3Handle_t;
extern "C" mapreduce_test_3Handle_t __dace_init_mapreduce_test_3(int H, int W);
extern "C" void __dace_exit_mapreduce_test_3(mapreduce_test_3Handle_t handle);
extern "C" void __program_mapreduce_test_3(mapreduce_test_3Handle_t handle, float * __restrict__ A, float * __restrict__ B, float * __restrict__ sum, int H, int W);
