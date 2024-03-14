#include <stdio.h>
#include <math.h>

#include "parallel.c"

double d2u_1 (double x, double y) { return 6 * x + 6 * y; }
double u_1 (double x, double y) { return pow(x, 3) + pow(y, 3); }

double d2u_2 (double x, double y) { return 6000 * x + 12000 * y; }
double u_2(double x, double y) { return 1000 * pow(x, 3) + 2000 * pow(y, 3); }

int main() {

    int N = 10;
    int threads[] = {1, 4, 8, 12}; // max 12 threads on M2

    int lthreads = sizeof(threads) / sizeof(threads[0]);

    for (int i = 0; i < lthreads; ++i) {
        printf("\n--------------------------------------- \n");
        printf("N: %d, threads: %d \n \n", N, threads[i]);
        run_parallel(N, threads[i], d2u_2, u_2);
        }

    return 0;
}