#include <stdio.h›
#include <unistd.h›
#include
<sys/wait.h>
#include
<string.h>
#include
<stdlib.h›
int main() {
int pipefd[2]; // pipefd[0] = leitura, pipefd[1] = escrita
char
buffer [100];
if
(pipe (pipefd) == -1) {
perror ("pipe"); exit (EXIT_FAILURE) ;
}
pid_t pid = fork();
if (pid < 0) {
perror ("fork"); exit (EXIT_FAILURE) ;
}	
