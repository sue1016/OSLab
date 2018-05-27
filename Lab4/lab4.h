#include<iostream>

#include<stdio.h>
#include<stdlib.h>  

#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

#define threadNum 20
#include "lab4.cpp"
Process::Process()
{
	int n;
	srand(time(NULL));
	for( n=0; n < threadNum; n++)
	{
		tid_ =  
	
	}

}
int Process::getPid()
{
	return pid_;
}
int Process::getWaitTime()
{
	return waitTime_;
}
int Process::getPriority()
{
	return priority_;
}	
int Process::getRunTime()
{
	return runTime_;
}
int Process::getArriveTime()
{
	return arrivetime_;
}
void Process::setVisited(int visited)
{
	visited_ = visited;
}
int Process::getVisited()
{
	return visited_;
}
int Process::getTempRunTime()
{
	return tempRunTime_;
}
void Process::setWaitTime(int waitTime)
{
	waitTime_ = waitTime;
}
void Process::setTempRunTime(int tempRunTime)
{
       	tempRunTime_ = tempRunTime_ - tempRunTime;
}
      

