
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
  
// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    // Boucle infinie afin de parler avec le client
    for (;;) { 
        bzero(buff, MAX); 
  
        // Lecture du message et stockage dans le buffer
        read(sockfd, buff, sizeof(buff)); 
        // Affichage du buffer 
        printf("Recu du client: %s\t A envoyer en retour : ", buff); 
        bzero(buff, MAX); 
        n = 0; 
        // Copie du message
        while ((buff[n++] = getchar()) != '\n') 
            ; 
  
        // Envoie au client
        write(sockfd, buff, sizeof(buff)); 
  
        // Le mot clé Exit arrete le serveur 
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Fermeture du serveur...\n"); 
            break; 
        } 
    } 
} 
  
int main() 
{ 
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
  
    // creation du socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("Echec de la creation du socket...\n"); 
        exit(0); 
    } 
    else
        printf("Le socket est créé..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assignation ip ports 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    // Appairage IP
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("Appairage echoué...\n"); 
        exit(0); 
    } 
    else
        printf("Socket appairé..\n"); 


    if ((listen(sockfd, 5)) != 0) { 
        printf("Echec de l'ecoute...\n"); 
        exit(0); 
    } 
    else
        printf("Ecoute en cours..\n"); 
    len = sizeof(cli); 
  
    // Connection
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("Echec de connection du serveur...\n"); 
        exit(0); 
    } 
    else
        printf("Le client et le serveur sont connectés...\n"); 
  
    // Discussion entre client et serveur
    func(connfd); 
  
    // En fin de discussion, on ferme le socket
    close(sockfd); 
} 
