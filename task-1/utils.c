#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 32
#define EPS 0.1

typedef struct grid {
    int size;
    double h;
    double **u;
    double **f;
} grid;

typedef double (*fun_p)(double, double);

double** create_arr (int size) {
    double **arr = calloc(size, sizeof(*arr));
    for (int i = 0; i < size ; i++)
        arr[i] = calloc(size, sizeof(*arr[i]));
    return arr;
}

void free_arr (double** arr, int sz) {
    for (int i = 0; i < sz ; i++) {
        free(arr[i]);
        arr[i] = NULL;
    }

    free(arr);
    arr = NULL;
}

grid *create_grid (int size, fun_p f, fun_p u) {

    grid *g = malloc(sizeof(*g));

    g->size = size;
    g->h = 1.0 / (size + 1);
    g->u = create_arr(size + 2); // n+1 - corner of the grid
    g->f = create_arr(size + 2);

    // D domain
    for (int i = 1; i < size + 1; i++) {
        for (int j = 1; j < size + 1; j++) {
            g->f[i][j] = f(i * g->h, j * g->h);
        }
    }

    // bound values
    for (int i = 0; i < size + 2; i++) {
        g->u[i][0] = u(i * g->h, 0);
        g->u[i][size + 1] = u(i * g->h, (size + 1) * g->h);
        g->u[0][i] = u(0, i * g->h);
        g->u[size + 1][i] = u((size + 1) * g->h, i * g->h);
    }

    return g;
}

void free_grid(grid *g) {
    free_arr(g->f, g->size);
    free_arr(g->u, g->size);

    free(g);
    g = NULL;
}