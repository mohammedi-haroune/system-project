// Created by mohammedi on 12/25/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define mutex1 0 // mutex1 1initialise a 1. Protéger la variable nbEmbarques.
#define mutex2 1 // mutex2 initialise a 1. Protéger la variable nbDebarques.
#define semEmbarquement 2 //  pour bloquer les clients avant d'embarquer.
#define semDebarquement 3 // sémaphore pour bloquer les clients avant de descendre.
#define semTousAbord 4 //sémaphore pour signaler au processus voiture que P clients
#define semTousDehors 5 //sémaphore pour signaler au processus voiture que tout les clients sont maintenant descendus, la voiture peut faire un autre tour avec un autre groupe.
#define p 3
#define shared "shared"



// shared memory helpers


int createshm(key_t key, size_t __size) {
  int shmid = shmget(key,__size,IPC_CREAT|IPC_EXCL|0666);
  if(shmid == -1){
    //la zone existe deja !
    shmid=shmget(key,__size,0); //recuperer son id
    printf("Segment memoire existe deja id:%d\n",shmid);
  } else printf("Segment memoire id:%d\n",shmid);
  //tout les processus doivent appeler shmat pour attacher une adresse a la
  //zone memoire le pointeur permet par la suite d'ecrire directement des
  //donnes dans la zone partagée.
  return shmid;
}

typedef struct data{
  int nbEmbarques;
  int nbDebarques;
} state;

void printState(state* s) {
  printf("State : nbEmbarques = %d, nbDebarques = %d\n", s->nbEmbarques, s->nbDebarques);
}

int getNbEmbarques(int shmid) {
  //attach an state structure in order to put in the buffer
  state *s = NULL;
  s = shmat(shmid,s,0);
  printf("lecture nbEmbarques: ");
  printState(s);
  return s->nbEmbarques;
}


int getNbDebarques(int shmid) {
  //attach an state structure in order to put in the buffer
  state *s = NULL;
  s = shmat(shmid,s,0);
  printf("lecture nbDebarques: ");
  printState(s);
  return s->nbDebarques;
}

void setNbEmbarques(int shmid, int nb) {
  //attach an state structure in order to put in the buffer
  state *s = NULL;
  s = shmat(shmid,s,0);
  s->nbEmbarques = nb;
  printf("ecriture nbEmbarques: ");
  printState(s);
}

void setNbDebarques(int shmid, int nb) {
  //attach an state structure in order to put in the buffer
  state *s = NULL;
  s = shmat(shmid,s,0);
  s->nbDebarques= nb;
  printf("ecriture nbDebarques: ");
  printState(s);
}
