// Created by mohammedi on 12/25/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>


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
  op.sem_flg=SEM_UNDO;  /* operation flags */

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
