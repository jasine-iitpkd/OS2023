#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(void) {
  
  int number1, number2, sum;
  char *newargv[] = { "test.out", NULL };
  char *newenviron[] = { NULL };
 
  int pid;
  int output_fds = open("./output_hello.txt", O_WRONLY | O_CREAT);
  
  if (output_fds < 0)
     exit(EXIT_FAILURE);
     
  scanf("%d %d", &number1, &number2);
  sum = number1 + number2;
  pid = fork();
  if (pid < 0)
    exit(EXIT_FAILURE);
  if (pid == 0)
  { 
    dup2(output_fds, STDOUT_FILENO);
    execve("./test.out", newargv, newenviron);
  }
  else
  {  
     printf("from parent %d + %d = %d\n", number1, number2, sum);
  }
   
  return EXIT_SUCCESS;
}
