#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
    int N = 4; 
    for(int i = 0; i < N; i++) {
        pid_t pid = fork();
        
        if(pid < 0) {
            fprintf(stderr, "Fork falhou!\n");
            return 1;
        } else if(pid == 0) {
            printf("Filho: Eu sou o filho! Meu PID é %d, meu pai é %d.\n", getpid(), getppid());
            return 0;
        } else {
            printf("Pai: Eu sou o pai! Meu PID é %d, criei o filho %d.\n", getpid(), pid);
        }
    }

    for(int i = 0; i < N; i++) {
        wait(NULL);
        printf("Meu filho terminou, agora eu posso terminar.\n");
    }

    return 0;
}


//1. Qual a principal diferença entre o valor da variável pid no processo pai e no processo filho,
//logo apóos a chamada fork()? Por que essa diferença é tão importante? 

//2. O que aconteceria no exemplo fork_example.c se você removesse a linha wait(NULL); do código do processo pai? 
// Compile e execute para testar sua hipótese. (Pesquise sobre "processos zumbis" e 
// "processos órfãos" para entender o comportamento).