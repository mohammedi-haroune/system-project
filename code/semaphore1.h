// Created by mohammedi on 12/25/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define shared "shared"

//copied from the man semctl
union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
                              (Linux-specific) */
};

int initsem(int semid, int semnum, int initval) {
  int ret = semctl(semid, semnum, SETVAL, initval);
  if (ret == -1) perror("seminit:");
  return ret;
}

int createsem(key_t cle, int nsem) {
  int semid = semget(cle, nsem, IPC_CREAT|IPC_EXCL|0666);
  if (semid == -1) {
    semid = semget(cle, nsem, 0);
    printf("groupe de sema deja creer et son id est : %d\n", semid);
  }
  return semid;
}

//this should be used only if the use is sure that the semid is created with createsem
int getcreatedsem(key_t cle, int nsem) {
  return semget(cle, nsem, 0);
}

int initall(int semid, int semnum, ushort *values) {
  union semun s;
  s.array = values;
  int ret = semctl(semid, semnum, SETALL, s);
  if (ret == -1) perror("initall:");
  return ret;
}

int dropsem(int semid) {
  return semctl(semid, 0, IPC_RMID);
}
int getsem(int semid, int id) {
  return semctl(semid, id, GETVAL);
}

ushort *getall(int semid, int semnum)  {
  union semun s;
  s.array = malloc(semnum * sizeof(ushort));
  semctl(semid, semnum, GETALL, s);
  return s.array;
}

// c'est le P des TD

int P(int semid, unsigned short id) {
  struct sembuf op;
  op.sem_num= id;  /* semaphore number */
  op.sem_op =-1;   /* semaphore operation */
  op.sem_flg=0;  /* operation flags */

  return semop(semid, &op, 1);
}

// c'est le V des TD
int V(int semid, unsigned short id) {

  struct sembuf op;
  op.sem_num= id;  /* semaphore number */
  op.sem_op =1;   /* semaphore operation */
  op.sem_flg=0;  /* operation flags */

  return semop(semid,&op,1);
}

// Le Z bloq  le processus , il fait  rien jusqu'a la valeur de semaphore sera egale a 0

int Z(int semid, unsigned short id) {

  struct sembuf op;
  op.sem_num= id;  /* semaphore number */
  op.sem_op =0;   /* semaphore operation */
  op.sem_flg=0;  /* operation flags */

  return semop(semid,&op,1);

}

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
  //donnes dans la zone partagÈe.
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

int getNConf(int semid, int id) {
  return semctl(semid , id, GETNCNT);
}

void join(int n) {
  key_t key;
  //this assumes that the file exist in the current directory
  if ((key = ftok(shared, 'j')) == -1) {
    perror("cannot create key");
    exit(EXIT_FAILURE);
  }

  int semid = semget(key, 1, IPC_CREAT|IPC_EXCL|0666);
  if (semid == -1) {
    semid = semget(key, 1, 0);
    if (semid == -1) {
      perror("cannot create semid ");
      exit(EXIT_FAILURE);
    }
  } else {
    //if the join s√©maphore did't exist then initilaze it to zero
    initsem(semid, 0, 0);
  }

  //get NCONF : number of process waiting for increase
  int waiting = getNConf(semid, 0);

  //if the number of waiting is N (couting the current process) then free them. otherwise wait
  if (waiting == n - 1) {
    printf("last process, freeing all others\n");
    for(int i = 0; i < waiting; i++) {
      V(semid, 0);
    }
    //drop the semaphore. this gives the access for eventual other joins
    dropsem(semid);
  } else {
    printf("waiting in the barrier\n");
    P(semid, 0);
  }
}
