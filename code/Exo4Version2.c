//
// Created by kadri on 30/12/17.
//

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int main(int avrgc , char* argv[])
{
	int pid1,i;

	pid1 = fork() ;

	if(pid1 == -1){
		printf("error");
		exit(0);
	}

	if(pid1 == 0){
	//the child is running
	
		printf("I'm the child my pid = %d, \n\t\t\t   my father's pid = %d \n\n",getpid(),getppid());


		//le processus fils va éxécuter la commande "ls"
		execl( "/bin/ls","ls", (char *) NULL);

		//si on veut afficher une commande avec deux argument par exemple ls -l : execl( "/bin/ls","ls","-l", (char *) NULL);

		//si il a exécuté la command "ls"  il va pas afficher le message suivant .
		printf("error de l execution du exec !! \n");

	
	}else{
	
	//the father is running
	printf("\nI'm the father my pid = %d and i'm waiting for my children! \n\n",getpid());
	wait();
	}

	return 0;
	
}
	