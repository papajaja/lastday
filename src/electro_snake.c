#include <stdio.h>
#include <stdlib.h>

void sort_vertical(int n, int m, int **result_matrix, int *array);
void sort_horizontal(int n, int m, int **result_matrix, int *array);

int input(int ***matrix, int *n, int *m, int **array);
void output(int **matrix, int n, int m);

int main() {
    int **matrix = NULL, **result = NULL;
    int *array = NULL;
    int n = 0, m = 0;

    if (!input(&matrix, &n, &m, &array)) {
        result = (int **)realloc(result, n * sizeof(int *));
        for (int i = 0; i < n; i++) {
            result[i] = (int *)malloc(m * sizeof(int));
        }

        for (int i = 0; i < n * m - 1; i++) {
            for (int q = i + 1; q < n * m; q++) {
                if (array[i] > array[q]) {
                    int temp = array[i];
                    array[i] = array[q];
                    array[q] = temp;
                }
            }
        }

        sort_vertical(n, m, result, array);
        output(result, n, m);
        printf("\n");
        sort_horizontal(n, m, result, array);
        output(result, n, m);
    }

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
        free(result[i]);
    }
    free(matrix);
    free(result);
    free(array);

    return 0;
}

void sort_vertical(int n, int m, int **result_matrix, int *array) {
    int left = 0, index = 0;
    while (left < m) {
        for (int i = 0; i < n; i++) {
            result_matrix[i][left] = array[index];
            index += 1;
        }
        left += 1;
        for (int i = n - 1; i >= 0; i--) {
            result_matrix[i][left] = array[index];
            index += 1;
        }
        left += 1;
    }
}

void sort_horizontal(int n, int m, int **result_matrix, int *array) {
    int top = 0, index = 0;
    while (top < n - 1) {
        for (int i = 0; i < m; i++) {
            result_matrix[top][i] = array[index];
            index += 1;
        }
        top += 1;
        for (int i = m - 1; i >= 0; i--) {
            result_matrix[top][i] = array[index];
            index += 1;
        }
        top += 1;
    }
}


int input(int ***matrix, int *n, int *m, int **array) {
    int isNA = 0, inp, index = 0;
    if (scanf("%d %d", n, m) != 2 || *n <= 0 || *m <= 0) {
        printf("n/a");
        isNA = 1;
    }
    *array = (int *)realloc(*array, *n * *m * sizeof(int));
    *matrix = (int **)realloc(*matrix, *n * sizeof(int *));
    for (int i = 0; i < *n && !isNA; i++) {
        (*matrix)[i] = (int *)malloc(*m * sizeof(int));
        for (int q = 0; q < *m && !isNA; q++) {
            if (scanf("%d", &inp) != 1) {
                printf("n/a");
                isNA = 1;
            } else {
                (*array)[index] = inp;
                (*matrix)[i][q] = inp;
                index += 1;
            }
        }
    }
    return isNA;
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int q = 0; q < m; q++) {
            printf("%d", matrix[i][q]);
            if (q != m - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}
