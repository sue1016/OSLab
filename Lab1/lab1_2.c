#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    pid_t pid;
    pid = fork();
    
    if(pid == -1)
    {
        printf("failed to fork");
    } 
    else if(pid == 0)
    {
        
    }




}
