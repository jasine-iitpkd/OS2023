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
   #include <assert.h>
   
       int main()
       {
           int qid;
           unsigned int mprio=0;
           
           time_t t;
           
           qid = mq_open ("/test_q3", O_RDONLY);

           if (qid == -1) {
               printf("failed\n");
               exit(EXIT_FAILURE);
           }
           
           struct mq_attr attr;
           assert (mq_getattr (qid, &attr) != -1);

           char *buffer = calloc (attr.mq_msgsize, 1);
           assert (buffer != NULL);

/* Retrieve message from the queue and get its priority level */

          if ((mq_receive (qid, buffer, attr.mq_msgsize, &mprio)) == -1)
             printf ("Failed to receive message\n");
          else
             printf ("Received [priority %u]: '%s'\n", mprio, buffer);

/* Clean up the allocated memory and message queue */
          free (buffer);
          buffer = NULL;
          mq_close (qid);


       }
       
