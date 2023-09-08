#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(void) {
  int number1, number2, sum;
  int pid;
  int offset;
  
  scanf("%d %d", &number1, &number2);
  int output_fds = open("./output.txt", O_WRONLY | O_CREAT);
  if (output_fds < 0)
     exit(EXIT_FAILURE);
   
  pid = fork();
  if (pid<0)
     exit(EXIT_FAILURE);
     
  sum = number1 + number2;
  dup2(output_fds, STDOUT_FILENO);
  
  if (pid == 0)
  { 
     printf("from child %d + %d = %d\n", number1, number2, sum);
     offset = lseek(output_fds, 0, SEEK_CUR);
     printf("from child offset %d \n", offset);
  }   
  else
  {  
     printf("from parent %d + %d = %d\n", number1, number2, sum);
     offset = lseek(output_fds, 0, SEEK_CUR);
     printf("from parent offset %d \n", offset);
   }  
   
  return EXIT_SUCCESS;
}
