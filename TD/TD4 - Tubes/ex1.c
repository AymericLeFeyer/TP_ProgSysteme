// Ecrire un programme en langage C ayant 2 processus communiquant par tube
// - Le premier processus lit des chaines a partir de l'entrée standard et le transmet via le tube au deuxieme processus
// - Le deuxieme processus transforme les minuscules en majuscules et affichent les resultats a l'ecran sur la sortie standard
// Les deux processus travaillent en parallele et se font en boucle infinie

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

char min2maj(char c) {
    if (c >= 'a' && c <= 'z') {
        return c + 'A' - 'a';
    }
    else {
        return c;
    }

}

#define MAX 64

int main(int argc, char** argv) {
    char tampon[MAX];
    int pid, T[2], s, n;
    if (pipe(T) == -1) return EXIT_FAILURE;
    pid = fork();
    if (pid < 0) return EXIT_FAILURE;
    if (pid == 0) {
        close(T[0]);
        while(n = read(0, tampon, MAX))
        {
            write(T[1], tampon, n);
        }
        close(T[1]);
        exit(0);
    }
    else {
        close(T[1]);
        while(n = read(T[0], tampon, MAX)) {
            for (int i = 0; i < n; i++) {
                tampon[i] = min2maj(tampon[i]);
            }
            write(1, tampon, n);
        }
        close(T[0]);
        waitpid(pid, &s, 0);
    }
    return EXIT_SUCCESS;
}
