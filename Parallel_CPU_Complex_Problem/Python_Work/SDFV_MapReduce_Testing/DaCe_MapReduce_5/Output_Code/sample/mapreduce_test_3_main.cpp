#include <cstdlib>
#include "../include/mapreduce_test_3.h"

int main(int argc, char **argv) {
    mapreduce_test_3Handle_t handle;
    int H = 42;
    int W = 42;
    float * __restrict__ A = (float*) calloc((H * W), sizeof(float));
    float * __restrict__ B = (float*) calloc((H * W), sizeof(float));
    float * __restrict__ sum = (float*) calloc(1, sizeof(float));


    handle = __dace_init_mapreduce_test_3(H, W);
    __program_mapreduce_test_3(handle, A, B, sum, H, W);
    __dace_exit_mapreduce_test_3(handle);

    free(A);
    free(B);
    free(sum);


    return 0;
}
