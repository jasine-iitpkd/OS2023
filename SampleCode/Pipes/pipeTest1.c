#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
   int pipe1fd[2];
   int pipe2fd[2];
   pid_t cpid;
   int a, b, sum, output;

   if (pipe(pipe1fd) == -1) {
          exit(EXIT_FAILURE);
   }
   if (pipe(pipe2fd) == -1) {
          exit(EXIT_FAILURE);
   }
   
   cpid = fork();
   if (cpid == -1) {
        exit(EXIT_FAILURE);
   }

   if (cpid == 0) 
   {    /* Child reads from pipe1  and writes to pipe2*/
           close(pipe1fd[1]); 
           close(pipe2fd[0]);
           read(pipe1fd[0], &a, sizeof(int));
           read(pipe1fd[0], &b, sizeof(int));
           sum = a + b;
           write(pipe2fd[1], &sum, sizeof(int));           
           close(pipe1fd[0]);
           close(pipe2fd[1]);
           _exit(EXIT_SUCCESS);

    } 
    else 
    {            /* Parent writes to pipe */
         close(pipe1fd[0]);    
         close(pipe2fd[1]);
         a = 50; b = 40;
         write(pipe1fd[1],&a,sizeof(int));
         write(pipe1fd[1],&b,sizeof(int));
         close(pipe1fd[1]); 
         /* Reader will see EOF */
                           
         wait(NULL);                /* Wait for child */
         read(pipe2fd[0],&output, sizeof(int));
         printf("output is %d \n", output);      
         close(pipe2fd[0]);
         exit(EXIT_SUCCESS);
        
       }
}

