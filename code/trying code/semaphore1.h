#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

//copied from the man semctl
union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO
                               (Linux-specific) */
};

int initsem(int semid, int semnum, int initval) {
	/*DESCRIPTION : semctl(semid, semnum, SETVAL, initval);
       Cette fonction effectue l'opération de  contrôle  indiquée
       par cmd sur l'ensemble de sémaphores (ou sur le semno-ième
       sémaphore de l'ensemble) identifié par semid.  Le  premier
       sémaphore de l'ensemble est identifié par la valeur 0 dans
       l'argument semnum.*/
	int ret = semctl(semid, semnum, SETVAL, initval);
	  /*SETVAL :
	  				Placer la valeur arg.val dans le champ  semval
                    du   semno-ième  sémaphore  de  l'ensemble  e
	  */
	if (ret == -1) perror("seminit:");
	return ret;
}

int createsem(key_t cle, int nsem) {
	int semid = semget(cle, nsem, IPC_CREAT|IPC_EXCL|0666);
	if (semid == -1) {
		semid = semget(cle, nsem, 0);
		//printf("groupe de sema deja crée et son id est : %d\n", semid);
	}
	return semid;
}

int initall(int semid, int semnum, ushort *values) {
	union semun s;
	s.array = values;
	/* SETALL      Positionner  le  champ  semval  de  tous   les
                   sémaphores   de  l'ensemble  en  utilisant  le
                   tableau arg.array , et en mettant  à  jour  le
                   champ  sem_ctime  de  la structure semid_ds de
                   contrôle du jeu de sémaphores.  Les  processus
                   en  attente sont réveillés si semval devient 0
                   ou augmente.  L'argument semno est ignoré.  Le
                   processus  appelant  doit avoir des privilèges
                   d'écriture sur le jeu de sémaphores.
	*/
	int ret = semctl(semid, semnum, SETALL, s);
	if (ret == -1) perror("initall:");
	return ret;
}

int dropsem(int semid) {
	semctl(semid, 0, IPC_RMID);
}
int getsem(int semid, int id) {
	/*GETVAL :
	  Renvoyer   la   valeur   du  champ  semval  du
                   semno-ième sémaphore de l'ensemble Le  proces­
                   sus appelant doit avoir des privilèges de lec­
                   ture sur le jeu de sémaphores.
	*/
	semctl(semid, id, GETVAL);
}

ushort *getall(int semid, int semnum)  {
	union semun s;
	s.array = malloc(semnum * sizeof(ushort));
	semctl(semid, semnum, GETALL, s);
	/* GETALL      Renvoyer  la valeur semval de chaque sémaphore
                   de  l'ensemble  dans  le  tableau   s.array.
                   L'argument  semno  est  ignoré.   Le processus
                   appelant doit avoir des privilèges de  lecture
                   sur le jeu de sémaphores.
                   */
	return s.array;
}

// c'est le P des TD

int P(int semid, int id) {
	struct sembuf op;
	op.sem_num= id;  /* semaphore number */
    op.sem_op =-1;   /* semaphore operation */
    op.sem_flg=0;  /* operation flags */

    return semop(semid,&op,1);


}

// c'est le V des TD
int V(int semid, int id) {

	struct sembuf op;
	op.sem_num= id;  /* semaphore number */
    op.sem_op =1;   /* semaphore operation */
    op.sem_flg=0;  /* operation flags */

    return semop(semid,&op,1);

}

// Le Z bloq  le processus , il fait  rien jusqu'a la valeur de semaphore sera egale a 0 

int Z(int semid, int id) {

	struct sembuf op;
	op.sem_num= id;  /* semaphore number */
    op.sem_op =0;   /* semaphore operation */
    op.sem_flg=0;  /* operation flags */

    return semop(semid,&op,1);

}
