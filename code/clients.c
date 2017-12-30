//
// Created by mohammedi on 12/25/17.
//

#include <stdio.h>
#include "semaphore1.h"
#include "parc.h"

void embarquement();
void debarquement();
void enBalade();
int getNbEmbarques();
int getNbDebarques();
void setNbEmbarques();
void setNbDebarques();

int main() {
  //disable buffering stdout, this makes printf print the messages directly (without buffering them)
  setbuf(stdout, NULL);

  key_t key = ftok(shared, 'p');
  int semid = createsem(key, 6);
  int shmid = createshm(key, sizeof(state));


  while(1){
    P(semid, semEmbarquement); //faire la chaine pour monter, attendre d’être libéré par le processus voiture

    embarquement(); //affiche un message : “client pid: je vais monter”

    P(semid, mutex1);

    int nbEmbarques = getNbEmbarques(shmid);
    nbEmbarques = nbEmbarques + 1;

    if (nbEmbarques == p) {
      V(semid, semTousAbord); // le dernier client qui monte va réveiller le processus voiture pour qu'il démarre
      nbEmbarques = 0; //il remet le compteur a zero
    }

    setNbEmbarques(shmid, nbEmbarques);

    V(semid, mutex1); //libere la SC

    enBalade(); //affiche un message “client pid: je suis en balade ” et sleep(1)

    P(semid, semDebarquement); //se met en attente du debarquement (il fait la chaine) pour descendre

    debarquement (); //affiche un message “client pid: FIN de la balade je descend”

    P(semid, mutex2);

    int nbDebarques = getNbDebarques(shmid);
    nbDebarques = nbDebarques + 1;

    if (nbDebarques == p) {
      V(semid, semTousDehors); //réveiller le processus voiture, quand tout le monde est descendu pour qu'i charge a nouveau.
      nbDebarques = 0;
    }

    setNbDebarques(shmid, nbDebarques);

    V(semid, mutex2);

    sleep(rand() % 2);
  }
}

void enBalade() {
  printf("client %d: je suis en balade\n", getpid());
  sleep(1);
}

void debarquement() {
  printf("client %d: FIN de la balade je descend\n", getpid());
}

void embarquement() {
  printf("client %d: je vais monter\n", getpid());
}
