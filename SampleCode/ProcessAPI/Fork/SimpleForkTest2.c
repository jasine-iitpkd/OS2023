#include <sys/wait.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main()
{  
   pid_t p1, p2; 
   p1 = fork();
   printf("Hello from %d \n", getpid());
   p2 = fork();
   printf("Hi from %d \n", getpid());
}   
   
