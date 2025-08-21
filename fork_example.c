#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
pid_t pid = fork () ;

if ( pid < 0) {
 fprintf ( stderr , " Fork falhou !\n") ;
 return 1;
 } else if ( pid == 0) {
 printf ("Eu sou o filho ! Meu PID e %d, meu pai e %d.\n", getpid () ,
getppid () ) ;
 } else {
 printf ("Eu sou o pai! Meu PID e %d, criei o filho %d.\n", getpid () , pid )
;
 wait ( NULL ) ;
 printf (" Meu filho terminou , agora eu posso terminar .\n") ;
}
return 0;
 }