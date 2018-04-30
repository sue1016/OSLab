#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

#define BUFFER_SIZE 16

//设置一个整数的圆形缓冲区 
struct circleBuff
{  
	int buffer[BUFFER_SIZE]; //缓冲区数组
        pthread_mutex_t lock; //互斥锁
        int readpos, writepos; //读写的位置
        pthread_cond_t notempty; //缓冲区非空信号
        pthread_cond_t notfull; //缓冲区非满信号
};   


//初始化缓冲区
void init(struct circleBuff* b)
{  
	pthread_mutex_init(&b->lock, NULL);
        pthread_cond_init(&b->notempty, NULL); 
        pthread_cond_init(&b->notfull, NULL); 
        b->readpos = 0;
        b->writepos = 0;
} 


// 向缓冲区中写入一个整数
void put(struct circleBuff* b, int data)
{       
	//拿到锁
        pthread_mutex_lock(&b->lock);

        //等待缓冲区非满
	while((b->writepos + 1) % BUFFER_SIZE == b->readpos)
	{      
                //把锁放掉，下来，到wait队列里，直到有notfull信号把它唤醒，重新把锁拿到
		printf("Buffer is full.Wait for not full\n");
		pthread_cond_wait(&b->notfull,&b->lock);
	}

        //写入数据并将写指针前移
	b->buffer[b->writepos] = data;
        b->writepos = (b->writepos + 1)%BUFFER_SIZE;

	//发出缓冲区非空信号
	pthread_cond_signal(&b->notempty);

	//释放锁
	pthread_mutex_unlock(&b->lock);   	
}

// 从缓冲区中读出一个整数
int get(struct circleBuff* b)
{       int data = -1;
        //拿到锁	
	pthread_mutex_lock(&b->lock);

        //等待缓冲区非空
	while((b->writepos) == (b->readpos))
	{		
                //把锁放掉，下来，到wait队列里，直到有notempty信号把它唤醒，重新把锁拿到
		printf("Buffer is empty.Wait for not empty\n");
		pthread_cond_wait(&b->notempty,&b->lock);
	}
        //读出数据并将读指针前移
	data = b->buffer[b->readpos];
        b->readpos = (b->readpos + 1)  % BUFFER_SIZE;

	//发出非满信号
        pthread_cond_signal(&b->notfull);

        //放掉锁
        pthread_mutex_unlock(&b->lock);
	return data;
}

#define OVER (-1)
struct circleBuff buffer;

void* producer(void* data){
	int n;
        for(n = 0; n < 100; n++)
	{
		put(&buffer, n);
        	printf("producer: put %d\n",n);
	}

        put(&buffer, OVER);
	printf("producer: finished my job!\n");
	return NULL;
}


void* consumer(void* data)
{   
	int dataGot;
	while(1)
        {	
		dataGot = get(&buffer);
		if(dataGot == OVER)
		{
			break;
		}	
		printf("consumer: get %d\n",dataGot);
	}

	printf("consumer: all got!\n");
	
	return NULL;
} 


int main()
{
	pthread_t prod_t, cons_t;
	void* retval;
	init(&buffer);
	pthread_create(&prod_t, NULL, producer, 0);
	pthread_create(&cons_t, NULL, consumer, 0);

	pthread_join(prod_t, &retval );
	pthread_join(cons_t, &retval );
        //代码中如果没有pthread_join主线程会很快结束从而使整个进程结束
	//从而使创建的线程没有机会开始执行就结束了。加入pthread_join后，
	//主线程会一直等待直到等待的线程结束自己才结束，
	//使创建的线程有机会执行。	
	return 0;
}
