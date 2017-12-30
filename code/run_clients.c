#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printUsage() {
  printf("Usage : run_clients nb_clients\n");
}

int main(int argc, char *argv[]) {
  if (argc != 2) printUsage();
  else {
    int nb_clients = atoi(argv[1]);
    for(int i = 0; i < nb_clients; i++) {
      int c;
      if ((c = fork()) == -1) {
        perror("can't create client : ");
      } else {
        if (c > 1) {
          execlp("./clients", "./clients", NULL);
        }
      }
    }
  }
}
