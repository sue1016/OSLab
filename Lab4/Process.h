#include<iostream>

#include<stdio.h>
#include<stdlib.h>  

#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>


using namespace std;

pthread_mutex_t Device_mutex;
class Process
{
	private:
		int pid_;
		int priority_;
		int waitTime_;
		int runTime_;
		int arriveTime_;
		int visited_;
 		int tempRunTime_;
        public:
		Process(int pid,int priority,int runTime);
	        int getPid();
	        int getWaitTime();
	        int getPriority();
		int getRunTime();
                int getArriveTime();
		void setVisited(int visited);
		int getVisited();
		int getTempRunTime();
		void setWaitTime(int waitTime);
                void setTempRunTime(int tempRunTime);

      

};


