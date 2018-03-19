#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
    pid_t cpid1, cpid2;
    cpid1 = fork();
    if(-1 == cpid1)
    {
        printf("failed to fork child process1");
    }
    else if(0 == cpid1)
    {
        printf("b");

         //This is the child process1, and it has to return 0,
         // otherwise it will fork the second child process too
        
         return 0;       
     }
    
    //only the father process can fork the second process
   
    cpid2 = fork();
    if(-1 == cpid2)
    {
       printf("failed to fork child process2");
    }
    else if(0 == cpid2)
    {
        printf("c");
    }
    else
    {
        printf("a"); 
    }
    
    return 0;
 
}
