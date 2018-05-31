#ifndef PROCESS_H
#define PROCESS_H
#include<iostream>

#include<stdio.h>
#include<stdlib.h>  

#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>


class MyProcess
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
		    MyProcess(int pid,int priority,int runTime);
		    MyProcess();
		    void setPid(int pid);
	        int getPid();
	        int getWaitTime();
	        int getPriority();
	        void setPriority(int priority);
		    int getRunTime();
		    void setRunTime(int runTime);
		    int getArriveTime();
		    void setVisited(int visited);
		    int getVisited();
		    int getTempRunTime();
		    void setWaitTime(int waitTime);
		    void setTempRunTime(int tempRunTime);

};


#endif