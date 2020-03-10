// Ecrire en C un programme ayant 2 processus communiquant par tube
// - Le premier processus lit le contenu du fichier passe en premier argument et l'envoi via le tube dans le deuxieme processus
// - Le deuxieme processus ecrit le contenu recu dans le fichier passe en 2e argument du programme
// Les deux processus travaillent en parallele
// ./a.out fichier1 fichier2

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 64

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Il faut 3 parametres, vous en avez mis %d\n", argc);
        return EXIT_FAILURE;
    }
    char tampon[MAX];
    int pid, T[2], s, n, d1, d2;
    if (pipe(T) == -1) return EXIT_FAILURE;
    pid = fork();
    if (pid < 0) return EXIT_FAILURE;
    if (pid == 0) {
        // fils
        close(T[0]);
        d1 = open(argv[1], 'O_RDONLY');
        if (d1 < 0) return EXIT_FAILURE;
        while (n = read(d1, tampon, MAX)) {
            write(T[1], tampon, n);
        }
        close(d1);
        close(T[1]);
        exit(0);
    } else {
        // pere
        close(T[1]);
        d2 = open(argv[2], 'O_WRONLY | O_CREATE | O_EXCP');
        if (d2 < 0) return EXIT_FAILURE;
        while (n = read(T[0], tampon, MAX)) {
            write(d2, tampon, n);
        }
        close(d2);
        close(T[0]);
        waitpid(pid, &s, 0);
    }
    return EXIT_SUCCESS;
}
