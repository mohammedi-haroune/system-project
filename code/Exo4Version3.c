#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/*
dans cette version on va gérer le cas de lancer l'éxécution avec des arguement 
on récupére les arguement  , par exemple 'man ls'  or 'ls -l ' ....etc 
et on exécute la commande , 
vous trouvez dans le meme dossier, deux capture d'ecran de la commande (ls -l  )
*/
char *concat_string(char *s1,char *s2)
{
     char *s3=NULL;
     s3=(char *)malloc((strlen(s1)+strlen(s2))*sizeof(char));
     strcpy(s3,s1);
     
     strcat(s3,s2);
     return s3;
}

int main(int argc, char* argv[]) {
    int i;
    pid_t pid;
    char* bin = "/bin/";
    if (argc == 1) {
        printf("ERROR\n");
        exit(1);
    }
    printf("argc = %d\n",argc );
    printf("arg 0 %s\n",argv[0] );
    printf("arg 1 %s\n",argv[1] );
    printf("arg 2 %s\n",argv[2] );
    for (i = 1; i < argc; i++) {
        pid = fork();
        
        char *cmd = argv[i];

        printf("%s\n",cmd);
        
        int status = 0;
        int options = 0;
        
        if (pid == -1) {
            printf("cannot create the process !\n");
            exit(0);
        }
        else{ 
            if (pid == 0) {
                    printf("je suis le processues %s: Mon pid %d --> ppid: %d\n", cmd, getpid(), getppid());
                    printf("---------------------------command is <: %s :> ---------------------- \n",cmd);
                    //ici par exemple  si on veut traiter le cas d'une commande 'les commande composé de deux mots'
                    if(strcmp(argv[i] ,(char *) "man")==0) {
                        printf("tu veux le manuel ?\n");
                        //cmd = concat_command(cmd,argv[i]);
                        //     strcat(cmd," ");
                          //   strcat(cmd,argv[i]);
                        i++; 
                        printf("bin %s\n", concat_string(bin,cmd));
                         execlp(cmd,cmd,argv[i], NULL);
                        sleep(3);
                        printf("q");
                    }else{
                        if(strcmp(argv[i+1] ,(char *) "-l")==0) {
                        printf("ls -l va étre exécuter ?\n");
                        //cmd = concat_command(cmd,argv[i]);
                        //     strcat(cmd," ");
                          //   strcat(cmd,argv[i]);
                        i++; 
                        printf("bin %s\n", concat_string(bin,cmd));
                         execlp(cmd,cmd,argv[i], NULL);
                        sleep(3);
                        printf("q");
                         }else{
                    //execlp(cmd, "", (char *) NULL);
                    //execl( "/bin/ls",cmd, (char *) NULL);
                     execlp(cmd,cmd, NULL);
                     sleep(3);
                        }
                        exit(0);
                    
                    printf("\n-----------------------------------------------------------------------\n");
                    sleep(2);
                    }
                }else {
                     printf("je suis le processus pshell de PID : %d , je vais attendre la fin de tous les processus que j'ai crées\n",pid);
                     waitpid(pid, &status, options);
                        exit(0);
                     }
                }
    }
}