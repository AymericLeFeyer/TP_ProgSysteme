// Ecrire un programme avec 2 processus communiquant par tubes. Le premier processus evoie au second le message "Je suis le processus 1"
// le second lui renvoie le message "Je suis le processus 2". 
// Les 2 processus affichent les messages recus

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX 64

int main(int argc, char** argv) {
    char message1[MAX], message2[MAX];
    
    int pid, s, n;
    int p1[2], p2[2];

    pipe(p1); // Creation de tube 1
    pipe(p2); // Creation du tube 2

    if (fork() == 0) {
        close(p1[1]); // Fermeture du tube p1 en ecriture
        close(p2[0]); // Fermeture du tube p2 en lecture

        // Code du fils
        strcpy(message2, "Je suis le processus 1\n");
        write(p2[1], message2, MAX);
        read(p1[0], message1, MAX);
        printf("Processus 1 recoit : %s", message1);

        close(p1[0]); //Fermeture de p1 en lecture
        close(p2[1]); // Fermeture de p2 en ecriture
        exit(0);
    }
    else {
        close (p1[0]); //Fermeture de p1 en lecture
        close (p2[1]); // Fermeture de p2 en ecriture

        // Code du pere
        strcpy(message1, "Je suis le processus 2\n");
        write(p1[1], message1, MAX);
        read(p2[0], message2, MAX);
        printf("Processus 2 recoit : %s", message2);

        close (p1[1]); // Fermeture du tube p1 en ecriture
        close (p2[0]); // Fermeture du tube p2 en lecture
    }
    
    
    
    return EXIT_SUCCESS;
}


