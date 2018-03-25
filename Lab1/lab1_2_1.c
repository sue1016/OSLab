#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    pid_t pid;
    int ret = 0;
    pid = fork();
    
    if(pid == -1)
    {
        printf("failed to fork");
    } 
    else if(pid == 0)
    {
       if((ret = execlp("./lab1_1_2","lab1_1_2",NULL)) < 0)
       {
           printf("execlp error");
       }    
        
    }
    else
    {
       printf("father process");
    } 
   
    return 0;


}
