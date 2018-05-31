
#include"Scheduler.h"
extern int processNum_;
extern MyProcess* pChildren_;
extern pthread_mutex_t Device_mutex;

Scheduler::Scheduler()
{


}




void Scheduler::FCFS()
{
	std::cout<<"--------------FCFS----------------------"<<std::endl;
	int start = 0;
	float waitTime = 0;
	float avWait = 0;
	for(int i = 0; i < processNum_/2; i++)
	{
		for(int j = 0; j < processNum_; j++)
		{
			if(pChildren_[j].getArriveTime() == i && pChildren_[j].getVisited() == 0)
			{
				 std::cout<<"Thread"<<pChildren_[j].getPid()<<": start "<<start<<";  run time "<<pChildren_[j].getRunTime()<<std::endl;

				waitTime = waitTime + (float)start;  
				start = start + pChildren_[j].getRunTime();
				pChildren_[j].setVisited(1);
			}
		}
	}
	avWait = waitTime / (float)processNum_;
	std::cout<<"total waiting time: "<<waitTime<<std::endl;
	std::cout<<"average waiting time: "<<avWait<<std::endl;


}
void Scheduler::SJF()
{
	for(int k = 0; k < processNum_; k++)
	{
		pChildren_[k].setVisited(0);
	}
	std::cout<<"--------------SJF----------------------"<<std::endl;
        int start = 0;
	float waitTime = 0;
	float avWait = 0;
	for(int i = 1; i < processNum_; i++)
	{
		for(int j = 0; j < processNum_; j++)
		{
			if(pChildren_[j].getRunTime()==i && pChildren_[j].getVisited() == 0)
			{
				std::cout<<"Thread"<<pChildren_[j].getPid()<<": start "<<start<<";  run time "<<pChildren_[j].getRunTime()<<std::endl;

				waitTime = waitTime + (float)start;                     
				start = start + pChildren_[j].getRunTime();
				pChildren_[j].setVisited(1);

			}
		}
	}
        avWait = waitTime / (float)processNum_;
        std::cout<<"total waiting time: "<<waitTime<<std::endl;
        std::cout<<"average waiting time: "<<avWait<<std::endl;

}
void Scheduler::RR(int r)
{
        int totalTime;
	for(int i = 0; i < processNum_; i++)
	{
                totalTime = totalTime + pChildren_[i].getRunTime();
		         pChildren_[i].setVisited(1);
                
	}
	std::cout<<"--------------RR----------------------"<<std::endl;
        int start = 0;
	float waitTime = 0;
	float avWait = 0;
        for(int j = 0; j < 20*processNum_; j = j + r)
        {
	    int k = (j%(20*r))/r;
            int tepRunTime = r;
            if(pChildren_[k].getTempRunTime() > 0)
            {
		    int tepRunTime = r;
		    if(pChildren_[k].getTempRunTime() - r <= 0)
		    {
			    tepRunTime = pChildren_[k].getTempRunTime();
			    pChildren_[k].setWaitTime(start + tepRunTime-pChildren_[k].getRunTime());
		    }
		      std::cout<<"Thread"<<pChildren_[j].getPid()<<": start "<<start<<";  run time "<<pChildren_[j].getRunTime()<<std::endl;
		      start = start + tepRunTime;
		      pChildren_[k].setTempRunTime(r);
		    
                   
            }
	    for(int m = 0; m < processNum_; m++)
	    {
		    waitTime += pChildren_[m].getWaitTime();
	    
	    }
        }
        avWait = waitTime / (float)processNum_;
        std::cout<<"total waiting time: "<<waitTime<<std::endl;
        std::cout<<"average waiting time: "<<avWait<<std::endl;


}
void Scheduler::prioritySche()
{
	for(int k = 0; k < processNum_; k++)
	{
		pChildren_[k].setVisited(0);
	}
        std::cout<<"--------------priority-Scheduling----------------------"<<std::endl;
        int start = 0;
        float waitTime = 0;
        float avWait = 0;
        for(int i = 1; i < processNum_; i++)
	{
		for(int j = 0;j < processNum_; j++)
		{
			if(pChildren_[j].getPriority()==i && pChildren_[j].getVisited()==0)
			{
	            std::cout<<"Thread"<<pChildren_[j].getPid()<<": start "<<start<<";  run time "<<pChildren_[j].getRunTime()<<std::endl;
				waitTime = waitTime + float(start);
				start = start + pChildren_[j].getRunTime();
				pChildren_[j].setVisited(1);

			}
		
		}
	
	}
	avWait = waitTime / (float)processNum_;
        std::cout<<"total waiting time: "<<waitTime<<std::endl;
        std::cout<<"average waiting time: "<<avWait<<std::endl;



}
