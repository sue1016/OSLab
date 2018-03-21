#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<wait.h>
#include<errno.h>
#include<stdlib.h>



int main()
{
  int counter = 0;
  pid_t pid = fork();
  int status = -1;

  if(pid < 0)
  {
      printf("fork error");
  }
  else if(0 == pid)
  {
      printf("I am the child process,wait for me to do sth:\n");
      while(counter < 10)
      {
          counter++;
          sleep(1);
          printf("%d sec has passed\n",counter);
      }
      exit(5);
  }
  else
  {
     printf("I am the parent, and I choose to wait my child to do all its stuff\n");
     wait(&status);
  }
  
printf("child exit status is %d\n", WEXITSTATUS(status));//status是按位存储的状态信息，需要调用相应的宏来还原一下

printf("end of program from pid = %d\n",getpid() );

return 0;
 
}
