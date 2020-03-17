// Serveur de l'exercice 3

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/ipc.h> 

#define MAX 64

// structure for message queue 
struct mesg_buffer { 
    long mesg_type; 
    char mesg_text[100]; 
} message; 
  
int main() 
{ 
    key_t key; 
    int msgid; 
    
    
    if (fork() == 0) {
        // Code du fils
        int s = 0;

        char delim[] = ",";

        
    
        // ftok to generate unique key 
        key = ftok("progfile", 65); 
    
        // msgget creates a message queue 
        // and returns identifier 
        msgid = msgget(key, 0666 | IPC_CREAT); 
    
        // msgrcv to receive message 
        msgrcv(msgid, &message, sizeof(message), 1, 0); 
    
        // display the message 
        printf("Data Received by server is : %s \n",  
                        message.mesg_text); 

        char *ptr = strtok(message.mesg_text, delim);

        while(ptr != NULL)
        {
            s += atoi(ptr);
            ptr = strtok(NULL, delim);
        }

        sprintf(message.mesg_text, "%d", s);
        msgsnd(msgid, &message, sizeof(message), 0); 

        
        exit(0);
    }
    else {
        // Code du pere
        
       
    

    
    }
    
  
    // to destroy the message queue 
    msgctl(msgid, IPC_RMID, NULL); 
  
    return 0; 
} 