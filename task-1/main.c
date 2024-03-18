#include <stdio.h>
#include <math.h>

#include "parallel.c"

double u_1(double x, double y) { return y * sin(x); }
double d2u_1 (double x, double y) { return -y * sin(x); }

double u_2(double x, double y) { return 1000 * pow(x, 3) + 2000 * pow(y, 3); }
double d2u_2 (double x, double y) { return 6000 * x + 12000 * y; }

double u_3(double x, double y) { return exp(x*y); }
double d2u_3 (double x, double y) { return exp(x*y)*pow(y, 2) + exp(x*y)*pow(x, 2); }

double u_4(double x, double y) { return x + y; }
double d2u_4 (double x, double y) { return 0; }

int main() {

    int size[] = {100, 200, 300, 500, 1000};
    int threads[] = {1, 8};

    int lsize = sizeof(size) / sizeof(size[0]);
    int lthreads = sizeof(threads) / sizeof(threads[0]);

    for (int n = 0; n < lsize; n++) {
        for (int i = 0; i < lthreads; ++i) {
            printf("\n--------------------------------------- \n");
            res test = run_parallel(size[n], threads[i], d2u_2, u_2);
            printf("Res for N: %d, threads: %d \n", size[n], threads[i]);
            printf("%d iterations, %7.2f s. \n", test.iter, test.t);
        }
    }
    return 0;
}