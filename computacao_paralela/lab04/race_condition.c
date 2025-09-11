#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 8
#define INCREMENTS_PER_THREAD 1000000

/* Variável global: acessível a todas as threads */
long long counter = 0;

void* thread_func(void* arg) {
    long thread_id = (long) arg;
    printf("Thread %ld iniciando o trabalho...\n", thread_id);

    for (int i = 0; i < INCREMENTS_PER_THREAD; ++i) {
        // A operação "counter++" não é atômica!
        // Ela envolve 3 passos:
        // 1. Ler o valor de 'counter' da memória para um registrador.
        // 2. Incrementar o valor no registrador.
        // 3. Escrever o novo valor de volta na memória.
        // Outra thread pode interferir entre esses passos!
        counter++;
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Criar as threads
    for (long i = 0; i < NUM_THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, thread_func, (void*) i) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Esperar todas as threads terminarem
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    long long expected = (long long) NUM_THREADS * INCREMENTS_PER_THREAD;

    printf("\n--- Resultados ---\n");
    printf("Valor final do contador: %lld\n", counter);
    printf("Valor esperado: %lld\n", expected);

    if (counter != expected) {
        printf("Diferença: %lld. CONDIÇÃO DE CORRIDA DETECTADA!\n", expected - counter);
    } else {
        printf("Resultado correto!\n");
    }

    return 0;
}
