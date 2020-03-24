// Client de l'exercice 3

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
  
int main(int argc, char ** argv) 
{ 
    key_t key; 
    int msgid; 
    

    if (fork() == 0) {

        
        // Code du pere
        // ftok to generate unique key 
        key = ftok("progfile", 65); 
    
        // msgget creates a message queue 
        // and returns identifier 
        msgid = msgget(key, 0666 | IPC_CREAT); 
        msgrcv(msgid, &message, sizeof(message), 1, 0); 
        printf("Data Received by client is : %s \n",  
                    message.mesg_text); 


        exit(0);
        
    }
    else {
        

        // Code du fils
        strcpy(message.mesg_text, "8"); 
        strcat(message.mesg_text, ",");
        strcat(message.mesg_text, "2");
    
        // ftok to generate unique key 
        key = ftok("progfile", 65); 
    
        // msgget creates a message queue 
        // and returns identifier 
        msgid = msgget(key, 0666 | IPC_CREAT); 
        message.mesg_type = 1; 
        
    
        // msgsnd to send message 
        msgsnd(msgid, &message, sizeof(message), 0); 
        
    
        // display the message 
        printf("Data send by client is : %s \n", message.mesg_text); 

        printf("Appel du server\n");
        execv("/home/aymeric/Git/TP_ProgSysteme/TP1/server", argv);
       
        exit(0);
       
    }
       
  
    return 0; 
} 