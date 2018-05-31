#include "Process.h"

MyProcess::MyProcess(int pid,int priority,int runTime)
{
	pid_ = pid;
	priority_ = priority;
	runTime_ = runTime;
	arriveTime_ = 0;
	tempRunTime_ = runTime;
	visited_ = 0;
	waitTime_ = 0;

}
MyProcess::MyProcess()
{
	pid_ = -1;
	priority_ = -1;
	runTime_ = -1;
	arriveTime_ = 0;
	tempRunTime_ = runTime_;
	visited_ = 0;
	waitTime_ = 0;
}
void MyProcess::setRunTime(int runTime)
{
	runTime_ = runTime;
}
void MyProcess::setPriority(int priority)
{
	priority_ = priority;
}
void MyProcess::setPid(int pid)
{
	pid_ = pid;

}
int MyProcess::getPid()
{
	return pid_;
}
int MyProcess::getWaitTime()
{
	return waitTime_;
}
int MyProcess::getPriority()
{
	return priority_;
}	
int MyProcess::getRunTime()
{
	return runTime_;
}
int MyProcess::getArriveTime()
{
	return arriveTime_;
}
void MyProcess::setVisited(int visited)
{
	visited_ = visited;
}
int MyProcess::getVisited()
{
	return visited_;
}
int MyProcess::getTempRunTime()
{
	return tempRunTime_;
}
void MyProcess::setWaitTime(int waitTime)
{
	waitTime_ = waitTime;
}
void MyProcess::setTempRunTime(int tempRunTime)
{
       	tempRunTime_ = tempRunTime_ - tempRunTime;
}


