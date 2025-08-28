#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define VECTOR_SIZE 1000
#define NUM_PROCESSOS 4

int main() {
    double *vector = (double *) malloc(VECTOR_SIZE * sizeof(double));
    double partial_sum = 0;
    double total_sum = 0;

    if (vector == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        return 1;
    }

    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = (double) i;
    }

    int chunk_size = VECTOR_SIZE / NUM_PROCESSOS;
    int pipes[NUM_PROCESSOS - 1][2];

    for (int i = 0; i < NUM_PROCESSOS - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Fork falhou!\n");
            return 1;
        }

        if (pid == 0) { // child
            close(pipes[i][0]); // close read end
            double local_sum = 0;
            int inicio = i * chunk_size;
            int fim = (i + 1) * chunk_size;

            for (int j = inicio; j < fim; j++) {
                local_sum += vector[j];
            }

            write(pipes[i][1], &local_sum, sizeof(double));
            close(pipes[i][1]);
            free(vector);
            exit(0);
        }

        // parent
        close(pipes[i][1]); // close write end
    }

    // Parent handles the last chunk
    int inicio = (NUM_PROCESSOS - 1) * chunk_size;
    int fim = VECTOR_SIZE;
    for (int i = inicio; i < fim; i++) {
        total_sum += vector[i];
    }

    // Collect partial sums from children
    for (int i = 0; i < NUM_PROCESSOS - 1; i++) {
        double received_sum = 0;
        read(pipes[i][0], &received_sum, sizeof(double));
        total_sum += received_sum;
        close(pipes[i][0]);
        wait(NULL);
    }

    printf("Soma total: %f\n", total_sum);

    free(vector);
    return 0;
}

