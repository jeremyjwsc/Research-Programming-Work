#include <cstdlib>
#include "../include/sfusion.h"

int main(int argc, char **argv) {
    sfusionHandle_t handle;
    float * __restrict__ A = (float*) calloc(2, sizeof(float));
    float * __restrict__ B = (float*) calloc(2, sizeof(float));


    handle = __dace_init_sfusion();
    __program_sfusion(handle, A, B);
    __dace_exit_sfusion(handle);

    free(A);
    free(B);


    return 0;
}
