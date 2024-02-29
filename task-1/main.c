//#include "/opt/homebrew/Cellar/libomp/17.0.6/include/omp.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EPS 0.1

double** create_arr(size_t sz) {
    double** res = calloc(sz, sizeof(*res));
    for (int i = 0; i < sz ; i++)
        res[i] = calloc(sz, sizeof(*res[i]));
    return res;
}

void free_arr(double** arr, size_t sz) {
    for (int i = 0; i < sz ; i++)
        free(arr[i]);
    return free(arr);
}

double** create_u_matrix(int N) {
    double** u_matrix = create_arr(N);
    for (int i = 0; i < N ; i++) {
        for (int j = 0; j < N ; j++) {
            double x = (double)i / (N);
            double y = (double)j / (N);
            if (y == 0) {
                u_matrix[i][j] = 100 - 200 * x;
            } else if (x == 0) {
                u_matrix[i][j] = 100 - 200 * y;
            } else if (y == 1) {
                u_matrix[i][j] = -100 + 200 * x;
            } else if (x == 1) {
                u_matrix[i][j] = -100 + 200 * y;
            }
        }
    }
    return u_matrix;
}

void print_tb(double** tb, size_t sz) {
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            printf("%7.2f ", tb[i][j]);
        }
        printf("\n");
    }
}

//неправильно тут
void gaudess_zeidel (int N, double** u, double** f) {
    double h = 1.0 / (N + 1);
    double dmax = 0;
    while (dmax > EPS) {
        for (int i = 1; i < N + 1; i++) {
            for (int j = 1; j < N + 1; j++) {
                double temp = u[i][j];
                u[i][j] = 0.25 * (u[i-1][j] + u[i+1][j] + u[i][j-1] + u[i][j+1] - h * h * f[i][j]);
                double dm = fabs(temp - u[i][j]);
                if (dmax < dm) {
                    dmax = dm;
                }
            }
        }
    }
}

int main() {
    int N = 10;
    double** f_matrix = create_arr(N);
    double** u_matrix = create_u_matrix(N);

    gaudess_zeidel(N, u_matrix, f_matrix);

    printf("\n####### Result ########\n");
    print_tb(u_matrix, 10);

    free_arr(f_matrix, N );
    free_arr(u_matrix, N );
}


