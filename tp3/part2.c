/*
 * processlab - part2.c
 *
 * Ecole polytechnique de Montreal, GIGL, Hiver 2024
 * Benzekri Omar, 244082
 * Michaud Mael, 2209239
*/

#include <pthread.h>
#include <stdio.h>
#include "./libprocesslab/libprocesslab.h"

#define m 1000000
#define nb 4

long somme[nb];

void* contribution(void*p)
{
  long no = (long)p;
  long start = (no * m/nb) + 1;
  long end = (no + 1) * m/nb;
  somme[no] = 0;
  for (long i = start; i <= end; i++) {
      somme[no] += i;
  }
  return NULL;
}


void question2( )
{
  pthread_t threads[nb];
  for (long i = 0; i < nb; i++) {
      pthread_create(&threads[i], NULL, contribution, (void*)i);
  }
  for (int i = 0; i < nb; i++) {
      pthread_join(threads[i], NULL);
  }
  long total = 0;
  for (int i = 0; i < nb; i++) {
      total += somme[i];
  }
  printf("Total: %ld, Expected: %ld\n", total, ((long)m * (m + 1)) / 2);
}
