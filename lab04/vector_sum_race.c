#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 4
#define INCREMENTS_PER_THREAD 1000000
#define tam 100000000

/* Variável global: acessível a todas as threads */
long long counter = 0;

/* Struct para passar múltiplos argumentos */
typedef struct {
    long thread_id;
    int *vetor;
    int comeco;
    int final;
    long long *local_sum;
} ThreadArgs;

void* thread_func(void* arg) {
    ThreadArgs *args = (ThreadArgs*) arg;

    printf("Thread %ld iniciando o trabalho: intervalo [%d, %d]\n",
           args->thread_id, args->comeco, args->final);

    // Aqui você pode escolher: incrementar counter ou processar vetor
    for (int i = 0; i < INCREMENTS_PER_THREAD; ++i) {
        // args->local_sum += args->vetor[i];
        counter++;  // cuidado: não é thread-safe sem mutex
    }

    return NULL;
}

int main() {
    int *vetor = (int*) malloc(tam * sizeof(int));
    if (!vetor) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // inicializa vetor
    for (int i = 0; i < tam; i++) {
        vetor[i] = 1;  // só para teste
    }

    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];

    // Criar as threads
    for (long i = 0; i < NUM_THREADS; ++i) {
        args[i].thread_id = i;
        args[i].vetor = vetor;
        args[i].comeco = i * (tam / NUM_THREADS);
        args[i].final = (i + 1) * (tam / NUM_THREADS) - 1;
        args[i].local_sum = 0;

        if (pthread_create(&threads[i], NULL, thread_func, &args[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }

    }

    // Esperar todas as threads terminarem
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        // printf("%lln", args[i].local_sum);
        counter += args[i].local_sum;

    }

    printf("Counter final = %lld\n", counter);

    free(vetor);
    return 0;
}
