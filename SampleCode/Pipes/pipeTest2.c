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
   pid_t cpid1=-1, cpid2=-1;
   int a, sum, output1, output2;
   int x[10]={10, 15, 20, 25, 30, 35, 40, 45};

   if (pipe(pipe1fd) == -1) {
          exit(EXIT_FAILURE);
   }
   if (pipe(pipe2fd) == -1) {
          exit(EXIT_FAILURE);
   }
   
   cpid1 = fork();
   if (cpid1 == -1) {
        exit(EXIT_FAILURE);
   }
   if (cpid1 != 0)
   {  //parent 
      cpid2 =fork();
      if (cpid2 == -1) {
        exit(EXIT_FAILURE);
      }  
    }   
    if ((cpid2 == 0) || (cpid1 ==0))  // children
    { 
           close(pipe1fd[1]); // not writing to pipe1 
           close(pipe2fd[0]); //not reading from pipe2
           sum = 0;
           for(int i=0; i <4; i++)
           { 
             read(pipe1fd[0], &a, sizeof(int));
             sum = sum + a;
           }   
           write(pipe2fd[1], &sum, sizeof(int));           
           close(pipe1fd[0]);
           close(pipe2fd[1]);
           _exit(EXIT_SUCCESS);

      }
      else if (cpid2>0) //parent
      {
                  /* Parent writes to pipe */
         close(pipe1fd[0]);    
         close(pipe2fd[1]);
         for (int i =0; i <8; i++)
            write(pipe1fd[1],&x[i],sizeof(int));
         close(pipe1fd[1]); 

                           
         wait(NULL);                /* Wait for child */
         wait(NULL);
         read(pipe2fd[0],&output1, sizeof(int));
         read(pipe2fd[0],&output2, sizeof(int));
         printf("sum is %d \n", output1+output2);      
         close(pipe2fd[0]);
         exit(EXIT_SUCCESS);
        
      }
}    
   
   


