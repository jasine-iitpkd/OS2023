/*Compile as a.out and 
execute ./a.out & ./a.out  
check pids printed
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char *argv[])
{
  int *p;
  int i=0;
  while(i<100) 
  {   
      printf("(process id %d), i: %d\n", getpid(),i);
      i++;
  }
  return 0;
}
