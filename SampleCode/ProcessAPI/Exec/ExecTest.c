#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  pid_t p1, pid, exitpid;
  int wstatus; 
  char *newargv[] = { "hello.out", NULL };
  char *newenviron[] = { NULL };

  p1= getpid(); 
  printf("I am parent. Before fork. My pid is %d\n", p1);
  pid=fork();
  if (pid < 0)
     exit(EXIT_FAILURE);
  else if (pid ==0)
  {   
      printf("I am child, my pid is %d \n", getpid());
      printf("My parent has pid %d \n", getppid());
      printf("Going to load hello program \n");
      execve("hello.out", newargv, newenviron);
      printf("This will not be printed\n");
  }
  else 
  { 
    printf("I am parent, pid of my child is %d \n", pid);      
    exitpid=wait(&wstatus);
    printf("Now my child has finished. Ret value of wait is %d \n", exitpid); 
    if (WIFEXITED(wstatus)) 
    {
       printf("Child exited normally, status=%d\n", WEXITSTATUS(wstatus));
    }
    else if  (WIFSIGNALED(wstatus))
    {
      printf("child was killed externally, terminating signal is %d \n",  WTERMSIG(wstatus));
    }     
 }   
      
}  
    
