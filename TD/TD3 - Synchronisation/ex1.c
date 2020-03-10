// On considere 2 processus A et B
// Utiliser les semaphores pour la synchronisation

// Synchroniser les processus A et B pour que a chaque instant il y ait plus d'actions A terminee que d'actions B commencees

int S, S1, S2;

void A() {
    while (1) {
        // A1
        // A2
        V(S);
    }
}

void B() {
    while (1) {
        P(S);
        // B1
        // B2
    }
}

// Synchroniser A et B pour que si A est dans A1 alors B n'est pas dans B1 et Si A est dans A1 alors B n'est pas dans B2

void A() {
    while (1) {
        P(S1);
        // A1
        V(S1);
        P(S2);
        // A2
        V(S2);
        
    }
}

void B() {
    while (1) {
        P(S1);
        // B1
        V(S1);
        P(S2);
        // B2
        V(S2);
    }
}

// Synchroniser A et D pour assurer l'alternance des actions de A et de B : A B A B

void A() {
    while (1) {
        // A1
        // A2    
        V(S2);
        P(S1);
    }
}

void B() {
    while (1) {
        P(S2);
        // B1
        // B2
        V(S1);
    }
}

// Synchroniser pour avoir A1 B1 A2 B2

void A() {
    while (1) {
        P(S1);
        // A1
        V(S2);
        P(S1);
        // A2 
        V(S2);   
    }
}

void B() {
    while (1) {
        P(S2);
        // B1
        V(S1);
        P(S2);
        // B2
        V(S1);
    }
}

