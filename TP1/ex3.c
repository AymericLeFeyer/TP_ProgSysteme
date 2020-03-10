// Ecrire deux programmes (chacun avec son main) qui communiquent par file de messages. Le client envoie a l'aide d'une file de messages 2 nombres entiers
// au serveur qui effectue leur addition et renvoie le resultat au client dans la file de messages. Ce dernier affiche le resultat a l'ecran
// Serveur : ex3_server.c
// Client : ex3_client.c

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <string.h>

int main(int argc, char** argv) {
    return EXIT_SUCCESS;
}