#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


//paralelizar este código
//comando pra compilar código: gcc lab02.c -o lab02 -lm


#define VECTOR_SIZE 200000000
#define NUM_PROCESSOS 4

// Função que simula uma carga dae trabalho pesada
void heavy_work(double *vector, int start, int end) {
    for (int i = start; i < end; ++i) {
        vector[i] = sin(vector[i]) * cos(vector[i]) + sqrt(vector[i]);
    }
}

int main() {
    int chunk_size = VECTOR_SIZE / NUM_PROCESSOS;
    double *vector = (double *) malloc(VECTOR_SIZE * sizeof(double));

    if (vector == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        return 1;
    }

    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = (double) i;
    }

    for(int i = 0; i < NUM_PROCESSOS -1; i++){
        pid_t pid = fork();

        if(pid < 0){
            fprintf(stderr, "Fork falhou!\n");
            return 1;
        }

        if(pid == 0){
            int inicio = i * chunk_size;
            int fim = (i + 1) * chunk_size;

            heavy_work(vector, inicio, fim);
            exit(0);
        }
    }


    int start = (NUM_PROCESSOS - 1) * chunk_size;
    int end = VECTOR_SIZE;
    heavy_work(vector, start, end);

    free(vector);
    return 0;
}
