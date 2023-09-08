   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <time.h>
   #include <unistd.h>
   #include <errno.h>
   #include <sys/types.h>
   #include <fcntl.h>           /* For O_* constants */
   #include <sys/stat.h>        /* For mode constants */
   #include <mqueue.h>
   
       int main()
       {
           int qid;
           unsigned int mprio;
           char mtext[80];
           
           time_t t;
           
           qid = mq_open ("/test_q3", O_CREAT |O_WRONLY,  0600, NULL);

           if (qid == -1) {
               printf("failed\n");
               exit(EXIT_FAILURE);
           }
           
           
           mprio =1;
           time(&t);
           snprintf(mtext, sizeof(mtext), "a message at %s",
                   ctime(&t));

           if (mq_send(qid, mtext, sizeof(mtext), mprio) == -1) {          
               mq_close(qid);
               exit(EXIT_FAILURE);
           }
           mq_close(qid);
           printf("sent: %s\n", mtext);
       }
          
