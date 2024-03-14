#include <math.h>
#include <time.h>

#include "utils.c"

static int min(int a, int b) { return a < b ? a : b; }

double process_block(grid *g, int a, int b) {
    int i_start = 1 + a * BLOCK_SIZE;
    int i_end = min(i_start + BLOCK_SIZE, g->size);
    int j_start = 1 + b * BLOCK_SIZE;
    int j_end = min(j_start + BLOCK_SIZE, g->size);

    double dmax = 0;
    for (int i = i_start; i < i_end; i++) {
        for (int j = j_start; j < j_end; j++) {
            double temp = g->u[i][j];
            g->u[i][j] = 0.25 * (g->u[i - 1][j] + g->u[i + 1][j] + g->u[i][j - 1] +
                                 g->u[i][j + 1] - g->h * g->h * g->f[i][j]);
            double dm = fabs(temp - g->u[i][j]);
            if (dmax < dm) dmax = dm;
        }
    }
    return dmax;
}

int process_grid (grid* g) {
    int iter = 0;
    double dmax; // max change in u values

    int nb = g->size - 2 / BLOCK_SIZE; //number of blocks. (n-2) because bounds are already given
    if (BLOCK_SIZE * nb != g->size) nb += 1;

    double* dm = calloc(nb, sizeof(*dm));

    // i,j = 0 & i,j = n+1 are bounds and their values already given (in utils.c)
    // nx + 1 is a number of processing blocks

    do {
        iter++;
        dmax = 0;

        //process blocks above the diagonal (wave rising)
        for (int nx = 0; nx < nb; nx++) {
            dm[nx] = 0;

            int i, j;
            double d;

#pragma omp parallel for shared(nx, dm) private(i, j, d)
            for (i = 0; i < nx + 1; i++) {
                j = nx - i;
                d = process_block(g, i, j);
                if (dm[i] < d) dm[i] = d;
            }
        }

        //process blocks under the diagonal (fading)
        for (int nx = nb - 2; nx >= 0; nx--) {
            int i, j;
            double d;

#pragma omp parallel for shared(nx, dm) private(i, j, d)
            for (i = nb - nx - 1; i < nb; i++) {
                j = 2 * (nb - 1) - nx - i;
                d = process_block(g, i, j);
                if (dm[i] < d) dm[i] = d;
            }
        }

        for (int i = 0; i < nb; i++)
            if (dmax < dm[i]) dmax = dm[i];

    } while (dmax > EPS);
    free(dm);

    return iter;
}

void run_parallel(int n, int threads, fun_p f, fun_p u) {
    int iter;
    grid *g = create_grid(n, f, u);

    omp_set_num_threads(threads);

    time_t t1 = time (NULL);
    iter = process_grid(g);
    time_t t2 = time (NULL);
    time_t t =  t1 - t2;

    printf("%ld\n", t1);
    printf("%ld\n", t2);

    printf("time: %0.30ld, iterations: %d \n", t, iter);
}