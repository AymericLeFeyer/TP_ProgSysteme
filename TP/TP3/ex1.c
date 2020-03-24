#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t sem;
pthread_mutex_t mutex;
int var_glob = 1;

void *redacteuur()
{
    sem_wait(&sem);
    // On incremente la valeur de 3 a chaque appel, afin de simuler l'ecriture en continu
    var_glob+=3;
    printf("Le redacteur écrit :%d\n",var_glob);

    sem_post(&sem);

}
void *lecteuur(void *rno)
{
    // Le lecteur enleve le verrou avant de modifier la valeur
    pthread_mutex_lock(&mutex);
    sem_wait(&sem); 
    pthread_mutex_unlock(&mutex);
    // Affichage de la lecture
    printf("Le lecteur lit :%d\n",var_glob);
    pthread_mutex_lock(&mutex);
    sem_post(&sem); // On réveille le rédacteur
    pthread_mutex_unlock(&mutex);
}

int main()
{
    pthread_t redacteur,lecteur;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&sem,0,1);

    int id[10] = {1,2,3,4,5,6,7,8,9,10}; //Utiliser pour l'exercice suivant
    while(1){
        // La boucle est infinie, il faut faire Ctrl+Break pour arreter le programme
        pthread_create(&redacteur, NULL, (void *)redacteuur, (void *)&id[0]);
        pthread_create(&lecteur, NULL, (void *)lecteuur, (void *)&id[0]);

        pthread_join(redacteur, NULL);
        pthread_join(lecteur, NULL);
        sleep(1);
    } 
    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);

    return 0;

}