#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <string.h>
#include <wait.h>

#define SHMKEY 75

char* shmPointer;
int shmid,i;
char str[] = {"Hello world"};

void processA()
{   
    //CREATE THE SHARE MEMORY WITH KEY
    shmid = shmget(SHMKEY, 512 ,0777|IPC_CREAT);
    printf("I am process A, I create the share memory\n");
    
    //WAIT FOR B TO WRITE IN SHARE MEMORY
    printf("I am process A, I am waiting for B to write in the share memory\n");
    wait(0);
   
    //TO SHOW THE STR TO WRITE IN THE SHARE MEMORY
    shmPointer  = (char*)shmat(shmid,0,0);
    printf("I am process A, I got the str B wrote in share memory: '%s'\n ",shmPointer);
    exit(0);
}

void processB()
{
    //TO WRITE STH IN THE SHARE MEMEORY A CREATED
    shmid = shmget(SHMKEY, 512, 0777);
    shmPointer = (char*)shmat(shmid,0,0);  //共享内存附加到自己的地址空间
    memset(shmPointer, '\0', 512);
    strncpy(shmPointer,str, 512);
    printf("I am process B, I am writing in the share memory\n");
    exit(0);
}

int main()
{
   pid_t pid = fork();
   if( pid < 0 )
   {
       printf("fork failed\n"); 
   }
   else if( 0 == pid)
   {
      processB();
   }
   else
   {
      processA();
   }
  
   return 0;
}
