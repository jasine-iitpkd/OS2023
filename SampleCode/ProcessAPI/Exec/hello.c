#include <stdio.h>
#include <stdlib.h>
 #include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
int main()
{
  printf("hello\n");
  sleep(20);
 // exit(255);
  exit(EXIT_SUCCESS);
}  
