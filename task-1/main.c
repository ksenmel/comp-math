#include <stdio.h>
#include "/opt/homebrew/Cellar/libomp/17.0.6/include/omp.h" //i'm pathetic macos user

int main() {
#pragma omp parallel
    printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());
}