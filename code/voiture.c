//
// Created by mohammedi on 12/25/17.
//

#include <stdio.h>
#include "semaphore1.h"
#include "parc.h"

void chargement(int i);

void rouler();

void dechargement();

void init_semaphores(int semid);

int main() {
  //disable buffering stdout, this makes printf print the messages directly (without buffering them)
  setbuf(stdout, NULL);

  key_t key;
  if ((key = ftok(shared, 'p')) == -1) {
    perror("cannot create key");
    exit(EXIT_FAILURE);
  }
  int semid = createsem(key, SEMNUM);
  init_semaphores(semid);

  int shmid = createshm(key, sizeof(state));
  setNbEmbarques(shmid, 0);
  setNbDebarques(shmid, 0);
  initialiseClients(shmid);

  int i = 1;
  while (1) {
    chargement(i++);
    for (int j = 0; j < p; ++j) {
      V(semid, semEmbarquement);
    }
    P(semid, semTousAbord);
    rouler();
    dechargement();
    for (int k = 0; k < p; ++k) {
      V(semid, semDebarquement);
    }
    P(semid, semTousDehors);
  }
  return 0;
}

void init_semaphores(int semid) {
  ushort values[] = {1, 1, 1, 0, 0, 0, 0};
  initall(semid, SEMNUM, values);
  printf("Initialisation des sémaphores : \n");
  printf("mutex1          --> %d\n", values[mutex1]);
  printf("mutex2          --> %d\n", values[mutex2]);
  printf("mutex3          --> %d\n", values[mutex3]);
  printf("semEmbarquement --> %d\n", values[semEmbarquement]);
  printf("semDebarquement --> %d\n", values[semDebarquement]);
  printf("semTousAbord    --> %d\n", values[semTousAbord]);
  printf("semTousDehors   --> %d\n", values[semTousDehors]);
}

void dechargement() {
  printf("processus voiture prêt pour le déchargement\n");
}

void rouler() {
  printf("processus voiture entraine de rouler\n");
  sleep(5);
}

void chargement(int i) {
  printf("nouveau chargement tournée numéro %d\n", i);
}
