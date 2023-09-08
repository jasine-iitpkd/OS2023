    /* Disclaimer : code is adapted from Linux man pages */ 
    
       #include <stdio.h>
       #include <stdlib.h>
       #include <string.h>
       #include <time.h>
       #include <unistd.h>
       #include <errno.h>
       #include <sys/types.h>
       #include <sys/ipc.h>
       #include <sys/msg.h>

       struct msgbuf {
           long mtype;
           char mtext[80];
       };
       int main()
       {
           int qid, opt;
           int msgtype = 1;
           int msgkey = 1234;
           
           struct msgbuf msg;

           
           qid = msgget(msgkey, IPC_CREAT | 0666);

           if (qid == -1) {
               perror("msgget");
               exit(EXIT_FAILURE);
           }
       
          if (msgrcv(qid, &msg, sizeof(msg.mtext), msgtype,
                      MSG_NOERROR) == -1) {
               if (errno) {
                   exit(EXIT_FAILURE);
               }
               
           } else
               printf("message received: %s\n", msg.mtext);

       }
       
