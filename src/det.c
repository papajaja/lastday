#include <stdio.h>
#include <stdlib.h>

double det(double **matrix, int n);
int input(double ***matrix, int *n, int *m);
void output(double det);

int main() {
    double **matrix = NULL;
    int n, m;

    if (!input(&matrix, &n, &m)) {
        output(det(matrix, n));
    }

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

int input(double ***matrix, int *n, int *m) {
    int isNA = 0;
    double inp;

    if (scanf("%d %d", n, m) != 2 || *n <= 0 || *m <= 0 || *n != *m) {
        printf("n/a");
        isNA = 1;
    }

    *matrix = (double **)realloc(*matrix, *n * sizeof(double *));
    for (int i = 0; i < *n && !isNA; i++) {
        (*matrix)[i] = (double *)malloc(*m * sizeof(double));
        for (int q = 0; q < *m && !isNA; q++) {
            if (scanf("%lf", &inp) != 1) {
                printf("n/a");
                isNA = 1;
            } else {
                (*matrix)[i][q] = inp;
            }
        }
    }
    return isNA;
}

void output(double det) {
    printf("%.6lf", det);
}

double det(double **matrix, int n) {
    int i, j, k;
    double det = 1.0;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            double ratio = matrix[j][i] / matrix[i][i];
            for (k = i; k < n; k++) {
                matrix[j][k] -= ratio * matrix[i][k];
            }
        }
    }

    for (i = 0; i < n; i++) {
        det *= matrix[i][i];
    }

    double product = 1.0;
    for (i = 0, j = n - 1; i < n; i++, j--) {
        product *= matrix[i][j];
    }
    det -= product;

    return det;
}
