#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(void) {
  char str[5];
  int pid;
  int offset1, offset2;
  //const void *buf = &str1;
  

  int output_fds1 = open("./outfile.txt", O_RDWR | O_CREAT);
  if (output_fds1<0)
     exit(EXIT_FAILURE);
  int output_fds2 = open("./outfile.txt", O_RDWR | O_CREAT);
  if (output_fds2<0)
     exit(EXIT_FAILURE);
  
  
  offset1=lseek(output_fds1, 0, SEEK_END);
  offset2=lseek(output_fds2, 0, SEEK_END); 
  printf("initial offsets \n");
  printf("offset 1 = %d offset 2 = %d \n", offset1, offset2);
  
  strcpy(str, "abcd");
  write(output_fds1, &str, sizeof(str));
  offset1=lseek(output_fds1, 0, SEEK_CUR);
  offset2=lseek(output_fds2, 0, SEEK_CUR);   
  printf("after write using fds1\n");
  printf("offset 1 = %d offset 2 = %d \n", offset1, offset2);
   
  strcpy(str, "efgh"); 
  write(output_fds2, &str, sizeof(str));
  offset1=lseek(output_fds1, 0, SEEK_CUR);
  offset2=lseek(output_fds2, 0, SEEK_CUR);   
  printf("after write using fds2\n");
  printf("offset 1 = %d offset 2 = %d \n", offset1, offset2);
   

  close(output_fds1);
  close(output_fds2);
   
  return EXIT_SUCCESS;
}
