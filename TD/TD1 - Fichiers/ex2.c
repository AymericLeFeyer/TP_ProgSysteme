// Ecrire un programme qui affiche en sortie std les fichiers passes en arguments
// si pas d'arguments alors le programme affiche sur la sortie std l'entree std


#include <stdio.h>
#include <stdlib.h>
#define MAX 64

int main(int argc, char **argv) {
    int i, desc, charTampon[MAX];
    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            desc = open(argv[i], 0_RDONLY);
            if (desc == -1) {
                exit(1);
            }
            
            while (n = read(desc, charTampon, MAX)) {
                write(1, charTampon, n)
            }

            close(desc);
        }
    }
    else {
        while (n = read(0, charTampon, MAX)) {
            write(1, charTampon, n);
        }
    }

       
        
}