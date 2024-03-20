#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
//..
int chiffreProduit = 0;
int chiffreConsommes = 0;
bool flag_de_fin = false;
sem_t* semProd;
sem_t* semCons;


void* producteur(void* pid) {
    srand(time(NULL));
    int sommeChiffreProduit = 0;    
    int x;
    while(!flag_de_fin) {
        sem_wait(&semCons);

        x = (rand()%9) +1;
        //mettre x dans le tampon ici
        sommeChiffreProduit += x;
        chiffreProduit += 1;

        sem_post(&semProd);
    }
    pthread_exit((void*)(long)sommeChiffreProduit);
    return NULL;
}

void* consommateur(void* cid) {
    // ...
    int sommeChiffreConsommes = 0;
    while (1) {
        sem_wait(&semProd);

        // lire du tampon ici
        // quitter la boucle si lecture = 0
        sommeChiffreConsommes; //ajouter la valeur lue
        chiffreConsommes += 1;
        sem_post(&semCons);

    }
    sem_post(&semCons); // Au cas ou on quitte la boucle (lecture=0)
    pthread_exit((void*)(long)sommeChiffreConsommes);

    return NULL;
}

void handler(int signum) {
    flag_de_fin = 1;
}


int main(int argc, char* argv[]) {
    // Les paramètres du programme sont, dans l'ordre :
    // le nombre de producteurs, le nombre de consommateurs
    // et la taille du tampon.
    int nombreDeProducteurs = atoi(argv[1]);
    int nombreDeConsommateurs = atoi(argv[2]);
    int tailleDuTampon = atoi(argv[3]);
    int tampon[tailleDuTampon];
    int sommeConsommateurs = 0;
    int sommeProducteurs = 0;


    pthread_t threadsProducteurs[nombreDeProducteurs], threadsConsommateurs[nombreDeConsommateurs];
    int ids[nombreDeProducteurs > nombreDeConsommateurs ? nombreDeProducteurs : nombreDeConsommateurs];

    // initialiser les Semaphores ici
    sem_t* semProd = calloc(1, sizeof(sem_t));
    int paratgeEntreProcessus = 0;
    int valeurDeDepart = 1;
    sem_init(semProd, paratgeEntreProcessus, valeurDeDepart);

    sem_t* semCons = calloc(1, sizeof(sem_t));
    sem_init(semCons, paratgeEntreProcessus, tailleDuTampon); // pas sur pour la taille
   
    for (int i = 0; i < nombreDeProducteurs; i++) {
        ids[i] = i;
        pthread_create(&threadsProducteurs[i], NULL, producteur, (void*)&ids[i]);
    }

    for (int i = 0; i < nombreDeConsommateurs; i++) {
        ids[i] = i;
        pthread_create(&threadsConsommateurs[i], NULL, consommateur, (void*)&ids[i]);
    }

    signal(SIGALRM, handler);
    alarm(1);

    for (int i = 0; i < nombreDeProducteurs; i++) {
        void* somme;
        pthread_join(threadsProducteurs[i], &somme);
        sommeProducteurs += (long)somme;
    }

    // Insérer des 0 dans le tampon ici

    for (int i = 0; i < nombreDeConsommateurs; i++) {
        void* somme;
        pthread_join(threadsConsommateurs[i], &somme);
        sommeConsommateurs += (long)somme;
    }
    //Affiche les résultats
    printf("Somme totale produite: %d\n", sommeProducteurs);
    printf("Somme totale consommée: %d\n", sommeConsommateurs);
    printf("Total chiffres produits: %d\n", chiffreProduit);
    printf("Total chiffres consommés: %d\n", chiffreConsommes);
    return 0;
}
