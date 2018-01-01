#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(void)
{ int p[2][2];
   pid_t pid[2];
   char buf[50];
int i;
for( i=0; i<2; i++){
if (pipe((*p)+i))
   { 	perror("pipe");  exit(1);
   }
}
   
   for( i=0; i<2; i++){  
     if((pid[i] = fork())==-1){ perror("fork");  exit(1);}
   } 



   if (pid[0]>0&&pid[1]>0)
   {  close(p[0][0]);//le pere ferme descripteur lecture
     //dup2(p[i,1],1);
      //execlp("ps","ps","aux");
      write(p[0][1],"Bonjour fils!\n", strlen("Bonjour fils!\n"));
      printf("Processus pere- message ecris.\n");
     fflush(NULL);
     close(p[0][1]);
      wait(NULL); //attendre fin fils
   }
   else {//le fils
   for( i=0; i<2; i++)
   { close(p[i][0]);//ferme descripteur ecriture
      while(read(p[i][0],buf, 20)>0){
      printf("Processus fils-message lu est : %s\n",buf);
      }
      printf("Processus fils-FIN \n");
      close(p[i][0]);
  }
}
   return 0;
}

