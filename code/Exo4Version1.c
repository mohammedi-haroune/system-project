#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
/*
Dans cette version on va traiter que le cas de recupération des commandes et l'exécuté ,
dans la version suivante, on gérer ça avec des processus en utilisant la fonction fork()
*/


int main(int argc, char* argv[]) {
    int i;
    if (argc == 1) {
        printf("ERROR\n");
        exit(1);
    }
   
    for (i = 1; i < argc; i++) {
        
        char *cmd = argv[i];
        printf("%s\n",cmd);
        
                    printf("---------------------------command N°:%d is <: %s :> ---------------------- \n",i,cmd);
                    system(cmd);
                    //execlp(cmd, "", (char *) NULL);
                    printf("\n-----------------------------------------------------------------------\n");
                    sleep(5);
                  
                
    }
}