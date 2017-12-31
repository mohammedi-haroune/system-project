#include <stdio.h>
#include "semaphore1.h"

int main() {
  key_t key = ftok("shared", 't');
  int semid = createsem(key, 1);
  initsem(semid, 0, 0);
  printf("using semid : %d\n", semid);
  for(int i = 0; i < 10; i++) {
    V(semid, 0);
    sleep(i * 2);
  }
}
