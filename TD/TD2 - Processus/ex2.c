// Generaliser l'ex1 pour n processus

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    int pid, n, debut, fin, pas, i, j, a, s;
    if (argc != 4) {
        printf("Erreur de parametres");
    }
    n = atoi(argv[1]);
    debut = atoi(argv[2]);
    fin = atoi(argv[3]);
    pas = (fin - debut + 1) / n;
    a = debut;
    for (i = 0; i < n; i++) {
        pid = fork();
        if (pid < 0) {
            printf("marche pas");
        }
        if (pid == 0) { //fils
            for (j = a; j <= a + pas; j++) {
                printf("%d\n", i);
            exit(0);
            }
        } else { //pere
            waitpid(pid, &s, 0);
            a += pas;
        }

    }
    return 0;
}