#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
  char str[5];
  int pid, wstatus;
  int offset;
    
  
  int output_fds = open("./output_test.txt", O_RDWR | O_CREAT);
  if (output_fds <0)
    exit(EXIT_FAILURE);
  
  offset=lseek(output_fds, 0, SEEK_CUR); 
  printf("initial offsets \n");
  printf("offset  = %d  \n", offset);
  
  
  pid = fork();
  if (pid < 0)
    exit(EXIT_FAILURE);
   
  if (pid == 0)
  { 
     strcpy(str, "abcd"); 
     write(output_fds, &str, sizeof(str));
     offset = lseek(output_fds, 0, SEEK_CUR);
     printf("offset from child %d, mypid=%d \n", offset, getpid());
     close(output_fds);
  }   
  else
  { 
     wait(&wstatus); 
     strcpy(str, "efgh"); 
     offset = lseek(output_fds, 0, SEEK_CUR);
     printf("offset from parent %d, mypid=%d \n", offset, getpid());
     write(output_fds, &str, sizeof(str));
     offset = lseek(output_fds, 0, SEEK_CUR);
     printf("offset from parent %d, mypid=%d \n", offset, getpid());
     close(output_fds);
     
  } 
  
  printf("hello \n");
 
  return EXIT_SUCCESS;
}
