#include <stdio.h>
#include <pthread.h>
#include "semaphore1.h"

int main() {
// ce semphore est pour test les changement d valeur 
  key_t key = ftok("shared", 't');
  int semid = createsem(key, 1);
  initsem(semid, 0, 0);

// mutex:
	  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER ;


  printf("semid utilisé est : %d\n", semid);
  	int i,n;
	int pid;
  	
  	printf("donner le nombre de fils a créer N = ");
	scanf("%d",&n);
	
	
	  for(i = 0; i < n; i++) {
		  	pid = fork();
		  	/*chaque processus fils va exécuter le V(semid,0); 
		  	aprés chaque exécution du V() , on aura un changement sur la valeur du semaphore 
		  	et cela sera afficher automatiquement sur la fenetre 'cmd' où on  a lancé le monitor*/
		  	if(pid == 0){
				pthread_mutex_lock(&mutex);
				printf("\tstarting => %d , incriment valeur de semaphore \n",getpid());
			    V(semid, 0);
				pthread_mutex_unlock(&mutex);
			    sleep(10);
			    getpid++;
		                }
	  	}
	  return 0;	
}

