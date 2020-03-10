// Ecrire un programme qui affiche en sortie std les chaines passees en argument
// pas de retour a la ligne enter les arugments
// l'option -n supprime le retour a la ligne apres la derniere ecriture



#include <stdio.h>

int main(int argc, char** argv[]){
    int i, j, d;
    if(argv[1][0]=='-' && argv[1][1]=='n' && argv[1][2]=='\0'){
        d=2;
    }else{
        d=1;
    }
    
    for(i=d, i<argc, i++){
        j=0;
        while(argv[i][j]! == '\0') j++;
        fwrite(1,argv[i],j);
        fwrite(1,"",1);
    }
}

