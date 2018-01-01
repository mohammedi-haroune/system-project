#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(void)
{ int p[2];
pid_t pid;
char buf[50];
if (pipe(p)){ 
	perror("pipe");
	exit(1);
}

if ((pid = fork())== -1){
	 perror("fork");
	 exit(1);
}

if (pid>0){
    close(p[0]);//le pere ferme descripteur lecture
	write(p[1],"Bonjour fils!\n", strlen("Bonjour fils--t'es la!\n"));
	printf("Processus pere- message ecris.\n");
	fflush(NULL);
	//close(p[1]);
	wait(NULL); //attendre fin fils
}else{ //le fils 
		// close(p[1]);//ferme descripteur ecriture
		while(read(p[0],buf, 20)>0){
			printf("Processus fils-message lu est:%s\n",buf);
			}
		printf("Processus fils-FIN \n");
		close(p[0]);
	}
return 0;
}
