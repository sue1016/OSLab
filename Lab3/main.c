#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"pthread.h"

#define BUFFER_SIZE 16

/* 设置一个整数的圆形缓冲区 */ 
struct prodcons
{  int buffer[BUFFER_SIZE]; /* 缓冲区数组 */
   pthread_mutex_t lock; /* 互斥锁 */ 
   int readpos, writepos; /* 读写的位置*/ 
   pthread_cond_t notempty; /* 缓冲区非空信号 */
   pthread_cond_t notfull; /*缓冲区非满信号 */ };


/*初始化缓冲区*/ 
void init(struct prodcons * b)
{  pthread_mutex_init(&b->lock, NULL);
   pthread_cond_init(&b->notempty, NULL); 
   pthread_cond_init(&b->notfull, NULL); 
   b->readpos = 0;
   b->writepos = 0;
} 


 /* 向缓冲区中写入一个整数*/ 
