// Ecrire un message identique au precedent mais utilisant les files de messages a la place des tubes
// Enonce de l'exercice precedent :
// Ecrire un programme avec 2 processus communiquant par tubes. Le premier processus evoie au second le message "Je suis le processus 1"
// le second lui renvoie le message "Je suis le processus 2". 
// Les 2 processus affichent les messages recus

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <string.h>

#define MAX 64

int main(int argc, char** argv) {
    char message1[MAX], message2[MAX];    

    // Creation de la file 1
    int msqid1 = msgget(IPC_PRIVATE, IPC_CREAT | 0600);
    if (msqid1 == -1) {
        perror("msgget1");

        return EXIT_FAILURE;
    }

    // Creation de la file 2
    int msqid2 = msgget(IPC_PRIVATE, IPC_CREAT | 0600);
    if (msqid2 == -1) {
        perror("msgget2");

        return EXIT_FAILURE;
    }


    if (fork() == 0) {
        // Code du fils
        // Envoie du message dans la file 2
        strcpy(message2, "Je suis le processus 1");
        if (msgsnd(msqid2, &message2, MAX, 0) == -1) {
            perror("msgsnd");

            return EXIT_FAILURE;
        }
        // Reception du message dans la file 1
        if (msgrcv(msqid1, &message1, 8192, 0, 0) == -1) {
            perror("msgrcv");

            return EXIT_FAILURE;
        }
        printf("Processus 1 recoit : %s\n", message1);
       
        exit(0);
    }
    else {
        // Code du pere
        // Envoie du message dans la file 2
        strcpy(message1, "Je suis le processus 2");
        if (msgsnd(msqid1, &message1, MAX, 0) == -1) {
            perror("msgsnd");

            return EXIT_FAILURE;
        }
        // Reception du message dans la file 1
        if (msgrcv(msqid2, &message2, 8192, 0, 0) == -1) {
            perror("msgrcv");

            return EXIT_FAILURE;
        }
        printf("Processus 2 recoit : %s\n", message2);
       
    }
    
    
    
    return EXIT_SUCCESS;
}

