/**
 * Multivariate gaussian random number generation using GSL
 * https://www.gnu.org/software/gsl/doc/html/randist.html#c.gsl_ran_multivariate_gaussian
 * Compile with:
 * g++ -lgsl -lgslcblas -lm `root-config --cflags` `root-config --libs` -Wall test_gsl.c 
 * For additional printing
 * g++ -D DEBUG -lgsl -lgslcblas -lm `root-config --cflags` `root-config --libs` -Wall test_gsl.c 
**/

#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

int main()
{
    const gsl_rng_type* T;
    gsl_rng* r;

    /* create a generator chosen by the
     environment variable GSL_RNG_TYPE */

    gsl_rng_env_setup();

    T = gsl_rng_default;
    r = gsl_rng_alloc(T);

    const int dim = 3;
    double pars[dim] = { 0, 0, 0.1 };
    double covmat[dim * dim] = { 1.0, -0.2, 0.0,
                                 -0.2, 1.0, 0.0,
                                 0.0, 0.0, 1.0 };
    double genpars[dim] = { 0, 0, 0 };

    // Gaussian Multivariate distribution
    gsl_vector* mu = gsl_vector_alloc(dim);
    for (int i = 0; i < dim; ++i) {
        gsl_vector_set(mu, i, pars[i]);
    }
    gsl_matrix* L = gsl_matrix_alloc(dim, dim);
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            // printf("gsl_matrix_set(L, %d, %d, covmat[%d]) = %f\n", i, j, i * dim + j, covmat[i * dim + j]);
            gsl_matrix_set(L, i, j, covmat[i * dim + j]);
        }
    }
    gsl_linalg_cholesky_decomp(L);
    gsl_vector* result = gsl_vector_alloc(dim);

    int max = 10000;
    // printf("Generated %d pars:\n", max);
    int n = 0;
    while (n++ < max) {
        gsl_ran_multivariate_gaussian(r, mu, L, result);
        for (int i = 0; i < dim; ++i) {
            genpars[i] = gsl_vector_get(result, i);
        }
        for (int i = 0; i < dim; ++i) {
            printf("%f\t", genpars[i]);
        }
        printf("\n");
    }
}