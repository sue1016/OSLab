#include"Scheduler.h"
Scheduler::Scheduler()
{
//抱歉我的进程和线程混了，虽然我创建的是线程，但是我是在模拟调度进程
        int ret1;
	ret1 = pthread_create(&mainThread_,NULL,&Children,NULL);
        if(ret1 == 0)
        {
		printf("create main thread: ok");
	}
	else
	{
		printf("create main thread: failed");
	
	}

}
void* Scheduler::createChildrenThreads(void*)
{
	int ret[processNum_];
	

}
void Scheduler::runProcess(int pid);
void Scheduler::FCFS();
void Scheduler::SJF();
void Scheduler::RR();
void Scheduler::prioritySche();
