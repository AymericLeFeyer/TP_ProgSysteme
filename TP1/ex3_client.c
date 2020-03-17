// Client de l'exercice 3

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <string.h>

#define MAX 64

int main(int argc, char** argv) {
    key_t key; 
    int msgid; 
    char message[MAX];
    strcpy(message, "");
    strcat(message, "5");
    strcat(message, ",");
    strcat(message, "8");
  
    // ftok to generate unique key 
    key = ftok("progfile", 65); 
  
    // msgget creates a message queue 
    // and returns identifier 
    msgid = msgget(key, 0666 | IPC_CREAT); 
  
    printf("Write Data : "); 

  
    // msgsnd to send message 
    msgsnd(msgid, &message, sizeof(message), 0); 
  
    // display the message 
    printf("Data send is : %s \n", message); 
  
    return 0; 
}