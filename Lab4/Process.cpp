#include "Process.h"
Process::Process(int pid,int priority,int runTime)
{
	srand(time(NULL));
	pid_ = pid;
	priority_ = priority;
	runTime_ = runTime;
        arriveTime_ = 0;
	tempRunTime_ = runTime;
	visited_ = 0;
	waitTime_ = 0;

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
      

