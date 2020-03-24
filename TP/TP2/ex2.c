#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Ecrire un programme avec 2 processus légers (pthreads) et une variable globale x de type int
// initialisée à 0. Le père incrémente x de 20 et l’affiche, le fils (processus léger) incrémente x de
// 30 et l’affiche. Les opérations incrémente x et afficher s’exécutent en exclusion mutuelle donc
// encadrées des primitives P et V.

int x = 0;

/* deuxieme thread */
void *inc_x(void *x_void_ptr)
{
    /* incrementer x de 30 */
    int *x_ptr = (int *)x_void_ptr;
    x += 30;

    /* affichage de x */
    printf("x : %d\n", x);
}

int main()
{
    printf("x: %d\n", x);

    /* reference deuxieme thread */
    pthread_t inc_x_thread;

    /* creation du second thread et executoin inc_x(&x) */
    if(pthread_create(&inc_x_thread, NULL, inc_x, &x)) {

        fprintf(stderr, "Error creating thread\n");
        return 1;

    }
    /* incrementer x dans la premier thread */
    x += 20;

    /* affichage de x */
    printf("x : %d\n", x);

    /* wait for the second thread to finish */
    if(pthread_join(inc_x_thread, NULL)) {

        fprintf(stderr, "Error joining thread\n");
        return 2;

    }

    return 0;

}