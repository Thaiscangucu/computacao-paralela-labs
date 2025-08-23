#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


//paralelizar este código
//comando pra compilar código: gcc lab02.c -o lab02 -lm


#define VECTOR_SIZE 200000000
#define NUM_PROCESSOS 4

// Função que simula uma carga de trabalho pesada
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

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

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


    int last_start = (NUM_PROCESSOS - 1) * chunk_size;
    int last_end = VECTOR_SIZE;
    heavy_work(vector, last_start, last_end);


    for(int i = 0; i < NUM_PROCESSOS - 1; i++) {
        wait(NULL);
    }
    printf("Resultado de verificacao: vector[10] = %f\n", vector[10]);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_spent = (end.tv_sec - start.tv_sec) + 
                        (end.tv_nsec - start.tv_nsec) / 1e9;
    
    printf("Versão paralela executou em %f segundos\n", time_spent);

    double speed_up = 6.855270/time_spent;
    printf("Speed up foi de %f\n", speed_up);

    free(vector);
    return 0;
}

// Você observou uma aceleração?
// R: Não, o speed up foi de 0.671. A versão sequencial foi mais rápida.
