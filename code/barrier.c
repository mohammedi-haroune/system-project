#include <stdio.h>
#include "semaphore1.h"

int main() {
  printf("waiting in the barrier\n");
  join(3);
  printf("all the process came, I'm free now");
}
