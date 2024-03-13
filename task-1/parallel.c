#include <math.h>
#include "utils.c"

static int min(int a, int b) { return a < b ? a : b; }

double process_block(grid *g, int a, int b) {
    int i_start = 1 + a * BLOCK_SIZE;
    int i_end = min(i_start + BLOCK_SIZE, g->size);
    int j_start = 1 + b * BLOCK_SIZE;
    int j_end = min(j_start + BLOCK_SIZE, g->size);

    double dm = 0;
    for (int i = i_start; i < i_end; i++) {
        for (int j = j_start; j < j_end; j++) {
            double temp = g->u[i][j];
            g->u[i][j] = 0.25 * (g->u[i - 1][j] + g->u[i + 1][j] + g->u[i][j - 1] +
                                 g->u[i][j + 1] - g->h * g->h * g->f[i][j]);
            double d = fabs(temp - g->u[i][j]);
            if (dm < d) dm = d;
        }
    }
    return dm;
}

int process_grid (grid* g) {
    int iter = 0;
    double dmax = 0;

    int nb = g->size / BLOCK_SIZE;
    if (BLOCK_SIZE * nb != g->size) nb += 1;

    double* dm = calloc(nb, sizeof(*dm));

    //nx is a number of processing blocks - 1

    do {
        iter++;
        dmax = 0;
        for (int nx = 0; nx < nb; nx++) {
            dm[nx] = 0;

            int i, j;
            double d;

#pragma omp parallel for shared(nx, dm) private(i, j, d)

            //process blocks above the diagonal (wave rising)
            for (i = 0; i < nx + 1; i++) {
                j = nx - i;
                d = process_block(g, i, j);
                if (dm[i] < d)
                    dm[i] = d;
            }
        }

        //process blocks under the diagonal (fading)
        for (int nx = nb - 2; nx >= 0; nx--) {
            int i, j;
            double d;

#pragma omp parallel for shared(nx, dm) private(i, j, d)
            for (i = nb - nx - 1; i < nb; i++) {
                j = nb + ((nb - 2) - nx) - i;
                d = process_block(g, i, j);
                if (dm[i] < d)
                    dm[i] = d;
            }
        }
        for (int i = 0; i < nb; i++)
            if (dmax < dm[i])
                dmax = dm[i];

    } while (dmax > EPS);
    free(dm);

    return iter;
}

void run_parallel(int n, int threads, fun_p f, fun_p u) {
    uint32_t iter = 0;
    grid *g = create_grid(n, f, u);

    omp_set_num_threads(threads);
    double start_time = omp_get_wtime();
    iter = process_grid(g);
    double end_time = omp_get_wtime();
    double time_difference = end_time - start_time;
    printf("Time: %0.3f, Iterations amount: %d \n", time_difference, iter);
}