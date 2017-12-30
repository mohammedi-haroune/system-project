//
// Created by mohammedi on 12/25/17.
//

#include <stdio.h>
#include "semaphore1.h"
#include "parc.h"
<<<<<<< HEAD
=======
#include <errno.h>
>>>>>>> parc/question4

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
<<<<<<< HEAD
  initialiseClients(shmid);
=======

  int timeout = 5; //mesurer en secondes, voir l'implementation de la fonction Ptimed dans semaphore1.h
>>>>>>> parc/question4

  int i = 1;
  while (1) {
    chargement(i++);
    for (int j = 0; j < p; ++j) {
      V(semid, semEmbarquement);
    }
<<<<<<< HEAD
    P(semid, semTousAbord);
    rouler();
=======

    int ptimed = Ptimed(semid, semTousAbord, timeout);
    if(ptimed == -1) {
      if (errno == EAGAIN) {
        printf("Chargmemet : temps d'attente %d secondes ecoulé\n", timeout);
        P(semid, mutex1);
        int nbEmbarques = getNbEmbarques(shmid);
        //remetre le sémaphore à zero pour bloquer le eventueles clients qui arrivent
        for (int k = 0; k < p - nbEmbarques; k++) {
          P(semid, semEmbarquement);
        }

        //remetre la variable nbEmbarques à zero pour préparer la prochaine trounée
        setNbEmbarques(shmid, 0);
        V(semid, mutex1);

        if (nbEmbarques > p / 3) {
          printf("tourner quand même avec %d clients \n", nbEmbarques);
          goto rouler;
        } else {
          fprintf(stderr, "il y a pas autan de clients pour démarer. %d clients. Décharge imediat!!\n", nbEmbarques);
          goto dechargement;
        }

      } else {
        perror("Ptimed(semTousAbord) ");
        exit(EXIT_FAILURE);
      }
    }

  rouler:
    rouler();

  dechargement:
>>>>>>> parc/question4
    dechargement();
    for (int k = 0; k < p; ++k) {
      V(semid, semDebarquement);
    }
<<<<<<< HEAD
    P(semid, semTousDehors);
=======

    P(semid, mutex1); getNbEmbarques(shmid); V(semid, mutex1);
    P(semid, mutex2); getNbDebarques(shmid); V(semid, mutex2);
    printf("calling Ptimed(semid, semTousDehors, timeout)");

    /* sleep(20); */

    int ptimed1 = Ptimed(semid, semTousDehors, timeout);

    if(ptimed1 == -1) {
      if (errno == EAGAIN) {
        printf("Déchargement: temps d'attente %d secondes ecoulé\n", timeout);
        P(semid, mutex2);
        int nbDebarques = getNbDebarques(shmid);
        //remetre le sémaphore à zero pour bloquer les clients du prochaines tours
        for (int k = 0; k < p - nbDebarques; k++) {
          P(semid, semDebarquement);
        }

        //remetre la variable nbEmbarques à zero pour préparer la prochaine trounée
        setNbDebarques(shmid, 0);

        V(semid, mutex2);
      } else {
        perror("Ptimed(semTousDehors) ");
        exit(EXIT_FAILURE);
      }
    }
>>>>>>> parc/question4
  }
  return 0;
}

void init_semaphores(int semid) {
<<<<<<< HEAD
  ushort values[] = {1, 1, 1, 0, 0, 0, 0};
  initall(semid, SEMNUM, values);
  printf("Initialisation des sémaphores : \n");
  printf("mutex1          --> %d\n", values[mutex1]);
  printf("mutex2          --> %d\n", values[mutex2]);
  printf("mutex3          --> %d\n", values[mutex3]);
=======
  ushort values[] = {1, 1, 0, 0, 0, 0};
  initall(semid, 6, values);
  printf("Initialisation des sémaphores : \n");
  printf("mutex1          --> %d\n", values[mutex1]);
  printf("mutex2          --> %d\n", values[mutex2]);
>>>>>>> parc/question4
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
<<<<<<< HEAD
  sleep(5);
=======
  sleep(3);
>>>>>>> parc/question4
}

void chargement(int i) {
  printf("nouveau chargement tournée numéro %d\n", i);
}
<<<<<<< HEAD
=======

>>>>>>> parc/question4
