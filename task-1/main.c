#include <stdio.h>
#include <math.h>

#include "parallel.c"

double d2u (double x, double y) { return 6 * x + 6 * y; }
double u (double x, double y) { return pow(x, 3) + pow(y, 3); }

int main() {

    int N = 10;
    int threads[] = {1, 4, 8, 12}; // max 12 threads on M2

    int lthreads = sizeof(threads) / sizeof(threads[0]);

    for (int i = 0; i < lthreads; ++i) {
        printf("\n--------------------------------------- \n");
        printf("N: %d, threads: %d \n \n", N, threads[i]);
        printf("serial alg: ");
        run_parallel(N, threads[i], d2u, u);
        }

    return 0;
}