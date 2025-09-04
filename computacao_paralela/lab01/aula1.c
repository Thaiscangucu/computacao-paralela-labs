#include <stdio.h>
#include <stdlib.h>
#include <time.h>  

#define tam 100000000

//Calcular o tempo de soma de todos os elementos de um vetor com 100.000.000 elementos

int main() {
    int *ptr;
    ptr = (int *)malloc(tam * sizeof(int));
    
    if (ptr == NULL) {
        printf("Erro na alocação de memória!\n");
        return 1;
    }
    
    srand(time(NULL));
    
    long long soma = rand();
    
    clock_t inicio = clock();
    
    for (int i = 0; i < tam; i++) {
        ptr[i] = 1;
        soma += ptr[i];
    }

    printf("Soma = %lld\n", soma);
    
    free(ptr);
    
    clock_t fim = clock();
    double tempo_total = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo = %f", tempo_total);
    
    return 0;
}

