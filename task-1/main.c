#include <stdio.h>
#include <math.h>

#include "parallel.c"

double d2u_2 (double x, double y) { return 6000 * x + 12000 * y; }
double u_2(double x, double y) { return 1000 * pow(x, 3) + 2000 * pow(y, 3); }

int main() {

    int size[] = {100, 200, 300, 500, 1000};
    int threads[] = {1, 4, 8, 12}; // max 12 threads on M2

    int lsize = sizeof(size) / sizeof(size[0]);
    int lthreads = sizeof(threads) / sizeof(threads[0]);

    for (int n = 0; n < lsize; n++) {
        for (int i = 0; i < lthreads; ++i) {
            printf("\n--------------------------------------- \n");
            printf("N: %d, threads: %d \n \n", size[n], threads[i]);
            run_parallel(size[n], threads[i], d2u_2, u_2);
        }
    }

    return 0;
}