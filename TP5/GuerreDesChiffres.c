#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <semaphore.h>

static bool flag_de_fin = false;

static int *tampon;
static int sizeTampon;
static int sommeProduit = 0;
static int sommeConsommee = 0;

static int ip = 0;
static int ic = 0;

static sem_t libre;
static sem_t occupe;
static sem_t mutex;

void *producteur(void *pid)
{
   int *nbGenere = malloc(sizeof(int));
   srand(time(NULL));

   while (!flag_de_fin)
   {
      sem_wait(&libre);
      int chiffreRandom = rand() % 9 + 1;

      sem_wait(&mutex);
      tampon[ip] = chiffreRandom;
      sommeProduit += chiffreRandom;
      ip = (ip + 1) % sizeTampon;
      sem_post(&mutex);

      sem_post(&occupe);

      ++(*nbGenere);
   }

   sem_wait(&libre);
   sem_wait(&mutex);
   tampon[ip] = 0;
   ip = (ip + 1) % sizeTampon;
   sem_post(&mutex);
   sem_post(&occupe);

   printf("Fin de production du thread %d\n", (int)(long)pid);
   pthread_exit(nbGenere);
}

void *consommateur(void *cid)
{
   int *nbConsomme = malloc(sizeof(int));
   int objRecupere;

   do
   {
      printf("Consommation du thread %d\n", (int)(long)cid);
      sem_wait(&occupe);

      sem_wait(&mutex);
      objRecupere = tampon[ic];
      sommeConsommee += objRecupere;
      ic = (ic + 1) % sizeTampon;
      sem_post(&mutex);

      sem_post(&libre);

      ++(*nbConsomme);
   } while (objRecupere != 0);

   printf("Fin de consommation du thread %d\n", (int)(long)cid);
   pthread_exit(nbConsomme);
}


void actionAlarme()
{
   flag_de_fin = true;
}

int main(int argc, char *argv[])
{
   int numProd = atoi(argv[1]);
   int numCons = atoi(argv[2]);
   sizeTampon = atoi(argv[3]);

   pthread_t *prodThreads = malloc(numProd * sizeof(pthread_t));
   pthread_t *consThreads = malloc(numCons * sizeof(pthread_t));
   tampon = malloc(sizeTampon * sizeof(int));

   sem_init(&mutex, 0, 1);
   sem_init(&libre, 0, sizeTampon);
   sem_init(&occupe, 0, 0);

   for (size_t i = 0; i < numProd; ++i)
      pthread_create(&prodThreads[i], NULL, producteur, (void *)i);

   for (size_t i = 0; i < numCons; ++i)
      pthread_create(&consThreads[i], NULL, consommateur, (void *)i);

   signal(SIGALRM, actionAlarme);
   alarm(1);

   int nbTotalProduction = 0;
   for (size_t i = 0; i < numProd; ++i)
   {
      int *exit_status;
      pthread_join(prodThreads[i], (void **)&exit_status);

      nbTotalProduction += *exit_status;
      free(exit_status);
   }

   sem_wait(&mutex);
   int nbOverwrite = 0;
   bool isOverwriting = false;
   for (size_t i = 0; i < sizeTampon; ++i)
   {
      int value = tampon[ip];
      tampon[ip] = 0;

      isOverwriting = ip == ic || isOverwriting;
      isOverwriting = value != 0 && isOverwriting;

      if (isOverwriting)
      {
         sommeConsommee += value;
         ++nbOverwrite;
      }

      ip = (ip + 1) % sizeTampon;
   }
   sem_post(&mutex);

   int nbTotalConsommation = nbOverwrite;
   for (size_t i = 0; i < numCons; ++i)
   {
      int *exit_status;
      pthread_join(consThreads[i], (void **)&exit_status);

      nbTotalConsommation += *exit_status;
      free(exit_status);
   }
   printf("\033[0;31m\n");
   printf("Somme totale produite: %d\n", nbTotalProduction);
   printf("Somme totale consommée: %d\n", nbTotalConsommation);

   printf("Total chiffres produits: %d\n", sommeProduit);
   printf("Total chiffres consommés: %d\n", sommeConsommee);
   printf("\033[0m");

   free(prodThreads);
   free(consThreads);
   free(tampon);

   return 0;
}