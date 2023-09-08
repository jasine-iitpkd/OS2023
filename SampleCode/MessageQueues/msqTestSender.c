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
           time_t t;
           
           qid = msgget(msgkey, IPC_CREAT | 0666);

           if (qid == -1) {
               perror("msgget");
               exit(EXIT_FAILURE);
           }
           
           msg.mtype = msgtype;
           time(&t);
           snprintf(msg.mtext, sizeof(msg.mtext), "a message at %s",
                   ctime(&t));

           if (msgsnd(qid, &msg, sizeof(msg.mtext),
                       IPC_NOWAIT) == -1) {
               exit(EXIT_FAILURE);
           }
           printf("sent: %s\n", msg.mtext);
       }
       
