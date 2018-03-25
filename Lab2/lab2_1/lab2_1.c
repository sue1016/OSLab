#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define MSGKEY 75
#define REQ 1


struct Msg{
   long mtype;
   char mtext[256];
}Msg;
int msgqid, pid, *pint, i;

void serverProcess()
{ 
    printf("I am the server process, my pid = %d\n",getpid());
    //CREATE MSGQUEUE
    msgqid = msgget(MSGKEY, 0777|IPC_CREAT);          //To create a message queue with the key 75,and return the message queue id
    printf("I am the server process, I create a msg queue\n");
    printf("I am the server process, I am waiting for a msg from client\n"); 
   // RECEIVE FROM CLIENT 
    msgrcv(msgqid, &Msg, 256, 1, 0);                  // wait to receive  a msg through the msg queue in the form of Msg struct 
    pint = (int*)Msg.mtext;                           //to convert the msg text, in reality the pid of client process, to int
    pid = *pint;                                      // to get the content of the int pointer pointing to
    printf("I am the server process, I have received a msg from client\n");
    printf("I am the server process, I am serving for client process of which pid = %d\n",pid);
 
  //SEND TO CLIENT
   Msg.mtype = pid;
   *pint = getpid();
   printf("I am the server process, I send a  msg to client \n");
   msgsnd(msgqid, &Msg, sizeof(int), 0);
   exit(0);
}

void clientProcess()
{
    printf("I am the client  process, my pid = %d\n",getpid());
    //SEND MSG TO SERVER
    msgqid = msgget(MSGKEY,  0777);
    pid = getpid();
    pint = (int*)Msg.mtext;
    *pint = pid;
    Msg.mtype = REQ;
    printf("I am the client process, I send a msg to client\n");
    msgsnd(msgqid, &Msg,sizeof(int), 0);


    //RECEIVE MSG FROM SERVER
    msgrcv(msgqid, &Msg, 256, pid, 0);
    printf("I am the client process,  I receive reply from pid = %d\n", *pint );
    exit(0);
}


int main()
{
  /* while((i = fork()) == -1);
   if(!i)
   {
      serverProcess(); 
   }
   while((i=fork()) == -1);
  if(!i)
  {
     clientProcess();
  }
  
  wait(0);
  wait(0);*/
 
      pid_t cpid;
      cpid = fork();
      if(-1 == cpid)
      {
          printf("failed to fork child process");
       }
      else if(0 == cpid)
      {
          clientProcess();
      }
      else
      {
          serverProcess();
      }
     
 
  return 0;
}
