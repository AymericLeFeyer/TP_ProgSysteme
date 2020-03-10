// n processus en parallele qui partagent 1 tampon

void i() {
    while (1) {
        acces_tampon(i);
        utiliser_tampon();
        quitter_tampon(i);
    }
}

// En utilisant les semaphores, donner le code des fonctions acces_tampon et quitter_tampon dans les cas suivants

// 1) L'utilisation de l'acces au tampon se fait par 1 seul processus a la fois

// int S;

acces_tampon(i) {
    P(S);
}

quitter_tampon(i) {
    V(S);
}

// 2) Le processus utilisent le tampon de maniere circulaire dans l'ordre suivant P1 P2 P3 ... Pn, P1 P2 ...

// S[n] tableau de semaphore
int S[100];
int N = 100;

acces_tampon(i) {
    P(S[i]);
}

quitter_tampon(i) {
    V(S[(i+1)%N]);
}

// 3) L'utilisation du tampon se fait en exclusion mutuelle et les processus pairs sont prioritaires aux premiers impaires

