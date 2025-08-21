#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
    pid_t pid = fork ();

    if (pid < 0) {
        fprintf(stderr, "Fork falhou!\n");
        return 1;
    } else if(pid == 0){
        printf("Filho: Eu sou o filho! Meu PID é %d, meu pai é %d.\n", getpid(), getppid());
    } else {
        printf("Pai: Eu sou o pai! Meu PID é %d, criei o filho %d.\n", getpid(), pid);
        wait(NULL);
        printf("Pai: Meu filho terminou, agora eu posso terminar.\n");
    }
    return 0;
}