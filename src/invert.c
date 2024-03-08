#include <stdio.h>
#include <stdlib.h>

void invert(double **matrix, int n, int m);
int input(double ***matrix, int *n, int *m);
void output(double **matrix, int n, int m);

int main() {
    double **matrix = NULL;
    int n, m;

    if (!input(&matrix, &n, &m)) {
			invert(matrix, n, m);
        output(matrix, n, m);
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
    } else {
        *matrix = (double **)malloc(*n * sizeof(double *));
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
    }
    return isNA;
}

void output(double **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int q = 0; q < m; q++) {
            printf("%.6lf", matrix[i][q]);
            if (q != m - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void invert(double **matrix, int n, int m) {
    // Создаем временную единичную матрицу
    double **temp = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        temp[i] = (double *)malloc(m * sizeof(double));
        for (int j = 0; j < m; j++) {
            if (i == j) {
                temp[i][j] = 1.0;
            } else {
                temp[i][j] = 0.0;
            }
        }
    }

    // Приводим исходную матрицу к единичной
    for (int i = 0; i < n; i++) {
        double pivot = matrix[i][i];
        for (int j = 0; j < m; j++) {
            matrix[i][j] /= pivot;
            temp[i][j] /= pivot;
        }
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = 0; j < m; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                    temp[k][j] -= factor * temp[i][j];
                }
            }
        }
    }

    // Заменяем значения исходной матрицы значениями временной матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = temp[i][j];
        }
    }

    // Освобождаем память, выделенную для временной матрицы
    for (int i = 0; i < n; i++) {
        free(temp[i]);
    }
    free(temp);
}
