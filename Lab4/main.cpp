


#include "Scheduler.h"
#include "Process.h"
int processNum_ = 20;
MyProcess* pChildren_ = new  MyProcess[processNum_];
pthread_mutex_t Device_mutex;

void* printProcess(void *arg);
void* createChildren(void *);
int main()
{
    Scheduler* s = new Scheduler();
    pthread_t pid1;
    int ret1;
    int processNum  = 20;
    ret1 = pthread_create(&pid1,NULL,createChildren,NULL);
    if(ret1 == 0)
    {
        std::cout<<"create main thread: ok"<<std::endl;
        sleep(20);
    }
    else
    {
        std::cout<<"create main thread: failed"<<std::endl;

    }
    s->FCFS();
    s->SJF();
    std::cout<<"enter RR time: "<<std::endl;
    int rr;
    std::cin>>rr;
    s->RR(rr);
    s->prioritySche();
    return 0;
}


void* printProcess(void *arg)
{
    int n = *(int *)arg;
    while(1)
    {
        std::cout<<"Process pid: "<<pChildren_[n-1].getPid();
        std::cout<<"      priority: "<< pChildren_[n-1].getPriority();
        std::cout<<"      run time: "<< pChildren_[n-1].getRunTime()<<std::endl;
        pthread_mutex_unlock(&Device_mutex);
        sleep(1);
        break;
    }
    pthread_exit(0);


}
void* createChildren(void *)
{
    int ret[processNum_];
    srand(time(NULL));
    for(int i = 0; i < processNum_; i++)
    {
        int pid;
        int priority;
        int runTime;

        pid = i + 1;
        priority = 1 + rand()%19;
        runTime = 1 + rand()%19;

        pChildren_[i].setPid(pid);
        pChildren_[i].setPriority(priority);
        pChildren_[i].setRunTime(runTime);
        pChildren_[i].setTempRunTime(runTime);
    }

    pthread_t pid[processNum_];
    pthread_mutex_init(&Device_mutex,NULL);

    for(int i =  0; i < processNum_; i++)
    {
        int k = i + 1;
        ret[i] = pthread_create(&pid[i],NULL,printProcess,&k);
        if(ret[i] == 0)
        {
            sleep(1);
        }
        else
        {
            std::cout<<"Process pid="<<k<<" failed"<<std::endl;
        }
    }
    for(int j = 0; j < processNum_; j++)
    {
        pthread_join(pid[j],NULL);
    }
    pthread_mutex_destroy(&Device_mutex);
    pthread_exit(0);
    return NULL;

}