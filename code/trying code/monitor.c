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

  union semun semun;
  struct semid_ds semid_ds;
  semun.buf = &semid_ds;

  if(argc < 2){
    printf("Usage: monitor semid\n");
    exit(0);
  }

  int monitor_SEMID=atoi(argv[1]);
  time_t last_otime = 0;

  while(1){
    /*
      semctl : voir sur le fichier semaphore1.h je l'ai bien expliqué   
      IPC_STAT :  copier dans la structure pointée  par  semun.buf
                   la  structure de données concernant l'ensemble
                   de sémaphores.   L'argument  semnmun  est  alors
                   ignoré.   Le processus appelant doit avoir des
                   privilèges de lecture sur le jeu de sémaphores
                   */
    int ipc_stat = semctl(monitor_SEMID, 0, IPC_STAT, semun);

    if(ipc_stat !=-1){
      // on prend (time) du changement des resource de meme semaphore
      time_t new_otime = semun.buf->sem_otime;

      // ici On teste si il y'a des changement sur les resource de semaphore 'values' on reaffiche 
      // une fois  'time' est changé , cela veut dire qu'il y'a un changement surevenu ce sémaphore 
      if (last_otime != new_otime) {
        // on reaffiche la date du dernier changement 
        printf("semaphore changed last_ctime = %s, new_ctime = %s", ctime(&last_otime), ctime(&new_otime));
        
        // et la pour faire le traitement du (ipcs -s -i monitor_SEMID)
        printf("\nSemaphore Array semid=%d\n",monitor_SEMID);
        int nbsems = semun.buf->sem_nsems;
        printf("uid=%d\t",semun.buf->sem_perm.uid);
        printf("gid=%d\t",semun.buf->sem_perm.gid);
        printf("cuid=%d\t",semun.buf->sem_perm.cuid);
        printf("cgid=%d\n",semun.buf->sem_perm.cgid);

        printf("mode=0%o, ",semun.buf->sem_perm.mode);
        printf("access perms=0%o\n",semun.buf->sem_perm.mode);
        printf("nsems= %d\n",nbsems);
        printf ("otime= %s",ctime(&semun.buf->sem_otime) );
        printf ("ctime= %s",ctime(&semun.buf->sem_ctime));

        int ligne=0;
        printf("semnum\t   ");
        printf("value\t");
        printf("ncount\t  ");
        printf("zcount\t");
        printf("pid\n");
        while(ligne<nbsems){
          int val  = semctl(monitor_SEMID , ligne , GETVAL  , semun);
          int ncount = semctl(monitor_SEMID , ligne , GETNCNT , semun);
          int zcount = semctl(monitor_SEMID , ligne , GETZCNT , semun);
          int pid  = semctl(monitor_SEMID , ligne , GETPID  , semun);

          printf("%d\t   ",ligne);
          printf("%d\t\t",val);
          printf("%d\t  ",ncount);
          printf("%d\t\t",zcount);
          printf("%d\n",pid);
          ligne++;
        }
        //mis a jour de la derniére date de changement du resource 
        last_otime = new_otime;
      }
    }
  }
}
