// Redirection des entrees/sorties
// Ecrire en c un programme permettant d'execiter la commande
// ls -l | grep test

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 64

int main(int argc, char** argv) {
    int pid, s, T[2];
    if (pipe(T) == -1) return EXIT_FAILURE;
    pid = fork();
    if (pid < 0) return EXIT_FAILURE;
    else if (pid == 0) {
        close(1);
        // ????
        execlp("ls", "ls", "-l", NULL);
    } else {
        close(0);
        // ???
        execlp("grep", "grep", "test", NULL);
    }
    return EXIT_SUCCESS;
}