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
#define nsem 0
#define initval 0

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

  //**************
  union semun semun;
  struct semid_ds semid_ds;
  semun.buf = &semid_ds;


  //G-KEY:
  key_t G_Key = ftok("shared",'c');
  // Creation de sémaphore avec la clé précidente, On recupére le SEMID dans "monitor_ID"
  int monitor_ID = createsem(G_Key,1);
  //initialisation du semaphore qui a la clé monitor_ID ,
  V(monitor_ID,0);
  // if argc <2  :  pour confirmer que le test est fait de la façon demandé (./exe semid)
  if(argc < 2){
    printf(" u have to insert the semid after ./EXE_NAME\n");
    exit(0);
  }else{
    int monitor_SEMID=atoi(argv[1]);
    sd->semid = monitor_SEMID;

    // la premiere fois on est sure qu'on va rentré
    while(1){

      printf("\nThe new semid= %d \n", sd->semid);

      P(monitor_ID,0);

      // atoit ( argv[1] )   --->  return  the input argv[1]  (PS: atoit(STRING) ::> INT )

      // récuperer les details de la resource input --> monitor_SEMId ---> semid ce qu'on a met ici ( ./exe semid)
      int ipc_stat = semctl(monitor_SEMID, nsem , IPC_STAT, semun);

      /*
        IPC_STAT : Copy   information   from   the   kernel   data  structure  associated
        with monitor_SEMID into the semid_ds structure pointed to by semun.buf.
        The    argument    semnum   is   ignored.   The  calling  process  must
        have read permission on the semaphore set.

      */

      if(ipc_stat !=-1){
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
      }

      /*printf("You want to insert a new SEMID ? : (Yes ==> 1 / No==>0 )\n");
        int answer ;
        scanf("%d",&answer);
        if(answer == 1){
        scanf("%d",&monitor_SEMID);
        sd->semid = monitor_SEMID ;
        }else{*/

      //  on  fait rien jusqu'a  l'arrivé d'un nouveau SEMID , si un user lance l'exe avec un autre semid
      while(monitor_SEMID == sd->semid){}

      // To wait the next update of semid :  pour l'utiliser au deuxiéme affichage
      monitor_SEMID = sd->semid;
      //}
      // ici  On est sure qu'un (nouveau user/ ou bien le meme user) a lancé l'exécution avec un semid différent

      // Alors On exécute V(semaphore) pour permt l'utilisateur bloqué a afficher les resource du nouveau SEMID
      V(monitor_ID,0);


    }
  }
}
