// Created by mohammedi on 12/25/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdbool.h>

#define mutex1 0 // mutex1 1initialise a 1. Protéger la variable nbEmbarques.
#define mutex2 1 // mutex2 initialise a 1. Protéger la variable nbDebarques.
#define mutex3 2 // mutex3 initialise a 1. Protéger la variable nbClients.
#define semEmbarquement 3 //  pour bloquer les clients avant d'embarquer.
#define semDebarquement 4 // sémaphore pour bloquer les clients avant de descendre.
#define semTousAbord 5 //sémaphore pour signaler au processus voiture que P clients
#define semTousDehors 6 //sémaphore pour signaler au processus voiture que tout les clients sont maintenant descendus, la voiture peut faire un autre tour avec un autre groupe.
#define p 3
#define SEMNUM 7
#define shared "shared"
#define MAX_CLIENTS 5

int MAX_TOURS = 3; // le nombre de tours maximum pour chaque clients.

// shared memory helpers

typedef struct data{
  int nbEmbarques;
  int nbDebarques;
  int nbClients;
  int clients[MAX_CLIENTS];
  int tours[MAX_CLIENTS];
} state;

void printClients(state* s) {
  printf("--------------Clients %d--------------\n", s->nbClients);
  for (int i = 0; i < s->nbClients; i++) {
    printf("client %d a fait %d tours\n", s->clients[i], s->tours[i]);
  }
  printf("--------------Clients--------------\n");
}

void initialiseClients(int shmid) {
  //attach an state structure in order to put in the buffer
  state *s = NULL;
  s = shmat(shmid,s,0);
  s->nbClients = 0;
}

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

int clientIndex(int clients[]) {
  int pid = getpid();
  int i;
  for (i = 0; i < MAX_CLIENTS && clients[i] != pid; i++) {}
  if (i < MAX_CLIENTS) return i;
  return -1;
}

void inscription(int shmid) {
  //attach an state structure in order to put in the buffer
  state *s = NULL;
  s = shmat(shmid,s,0);
  if (s->nbClients == MAX_CLIENTS) {
    fprintf(stderr, "overflow can't add other clients");
    exit(EXIT_FAILURE);
  }
  s->clients[s->nbClients] = getpid();
  s->tours[s->nbClients] = 0;
  s->nbClients = s->nbClients + 1;
  printf("Inscription d'un nouveau client %d \n", getpid());
  printClients(s);
}

void finTour(int shmid) {
  state *s = NULL;
  s = shmat(shmid,s,0);
  int index = clientIndex(s->clients);
  if (index == -1) {
    fprintf(stderr, "client %d not signed up and finish a tour! this should not happen", getpid());
    exit(EXIT_FAILURE);
  }
  s->tours[index] = s->tours[index] + 1;
  printf("client %d fin de tours numéro %d\n", getpid(), s->tours[index]);
  printClients(s);
}

bool peutTourner(int shmid) {
  state *s = NULL;
  s = shmat(shmid,s,0);
  int index = clientIndex(s->clients);
  if (index == -1) {
    fprintf(stderr, "client %d not signed up and want a tour! this should not happen", getpid());
    exit(EXIT_FAILURE);
  }
  return s->tours[index] < MAX_TOURS;
}
