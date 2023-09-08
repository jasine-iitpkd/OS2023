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
                      MSG_NOERROR | IPC_NOWAIT) == -1) {
               if (errno != ENOMSG) {
                   exit(EXIT_FAILURE);
               }
               printf("No message available for msgrcv()\n");
           } else
               printf("message received: %s\n", msg.mtext);

       }
       
