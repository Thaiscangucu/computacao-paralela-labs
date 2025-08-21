#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define VECTOR_SIZE 200000000

// Função que simula uma carga de trabalho pesada
void heavy_work(double *vector, int start, int end) {
    for (int i = start; i < end; ++i) {
        vector[i] = sin(vector[i]) * cos(vector[i]) + sqrt(vector[i]);
    }
}

int main() {
    double *vector = (double *) malloc(VECTOR_SIZE * sizeof(double));
    if (vector == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        return 1;
    }

    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = (double) i;
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    heavy_work(vector, 0, VECTOR_SIZE);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_spent = (end.tv_sec - start.tv_sec) + 
                        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Versão sequencial executou em %f segundos\n", time_spent);

    free(vector);
    return 0;
}
