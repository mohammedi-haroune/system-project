#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "semaphore1.h"

typedef struct data{
  int semid;
}sdata;

int main(int argc , char * argv [] ){

  //***** to work on the same semid , if someone change the semid -> all use the new semid

  key_t cle = ftok("shared",'c'); //modifier le chemin
  int shmid=shmget(cle,sizeof(sdata),IPC_CREAT|IPC_EXCL|0666);
  if(shmid==-1){
    //la zone existe deja !
    shmid=shmget(cle,sizeof(sdata),0); //recuperer son id
    printf("Segment existe deja d’id:%d\n",shmid);
  }else printf("Segment mémoire d’id:%d\n",shmid);
  //tout les processus doivent appeler shmat pour attacher une adresse a la zone memoire le
  //pointeur permet par la suite d'ecrire directement des donnes dans la zone partagée.

  sdata *sd=NULL; sd=(sdata*)shmat(shmid,sd,0);
  sd->semid =0;

  ////----------------------
  union semun semun;
  struct semid_ds semid_ds;
  semun.buf = &semid_ds;

  int nsem=0;
  int initval = 0;

  //G-KEY:
  key_t G_Key = ftok("shared",'c');
  // Creation de sémaphore avec la clé précidente, On recupére le SEMID dans "monitor_ID"
  int monitor_ID = createsem(G_Key,1);
  //initialisation du semaphore qui a la clé monitor_ID ,
  initsem(monitor_ID, nsem, initval);
  printf("sd->semid = %d\n",sd->semid );

}
