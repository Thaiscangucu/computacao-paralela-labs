#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int pipefd[2]; // pipefd[0] = leitura, pipefd[1] = escrita
    char buffer[100];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Processo Filho: escreve no pipe
        close(pipefd[0]); // Filho não lê, fecha a ponta de leitura

        const char* msg = "Olá do filho!";
        printf("Filho: enviando mensagem...\n");
        write(pipefd[1], msg, strlen(msg) + 1); // +1 para incluir o terminador '\0'

        close(pipefd[1]); // Fecha a ponta de escrita após o uso
        exit(EXIT_SUCCESS);
    } else { // Processo Pai: lê do pipe
        close(pipefd[1]); // Pai não escreve, fecha a ponta de escrita

        printf("Pai: esperando mensagem...\n");
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Pai: recebeu a mensagem: '%s'\n", buffer);

        close(pipefd[0]); // Fecha a ponta de leitura após o uso
        wait(NULL); // Espera o processo filho terminar
    }

    return 0;
}
