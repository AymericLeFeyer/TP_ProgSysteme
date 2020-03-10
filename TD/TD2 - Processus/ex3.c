// Ecrire un programme qui permet d'executer une commande ou un autre programme passe en argument

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    int pid = fork();
    if (pid < 0) printf("Erreur de parametres");
    if (pid == 0) {
        execvp(argv[1], &argv[1]);
        printf("erreur exec");

    }
}