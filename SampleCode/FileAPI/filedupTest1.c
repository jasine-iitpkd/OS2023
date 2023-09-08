#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(void) {
  int number1, number2, sum;
  int output_fds = open("./output.txt", O_WRONLY | O_CREAT);
  if (output_fds < 0)
  {  
     printf("file open error \n");
     exit(EXIT_FAILURE);
  } 
  scanf("%d %d", &number1, &number2);
  sum = number1 + number2;
  
  dup2(output_fds, STDOUT_FILENO);
  printf("%d + %d = %d\n", number1, number2, sum);
  return EXIT_SUCCESS;
}
