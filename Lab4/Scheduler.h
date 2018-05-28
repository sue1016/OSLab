class Scheduler
{
	private:
		processNum_;
		pthread_t mainThread_;
	public:
	       Scheduler();
               void runProcess(int pid);
	       void FCFS();
	       void SJF();
	       void RR();
	       void prioritySche();
                         	       









};
