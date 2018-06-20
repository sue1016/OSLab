#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    //在window操作系统下要屏蔽此条指令
#include <string.h>
#ifndef _UNISTD_H
#define _UNISTD_H
#endif
#define TRUE 1
#define FALSE 0
#define INVALID -1
#define  total_instruction  320     //指令流长
#define  total_vp  32               //虚页长
#define  clear_period  50           //清周期

typedef struct                      //页面结构
{
    int pn,							//页面序号
		pfn,						//页面所在内存区的帧号
		counter,					//单位时间内访问次数
		time;						//上次访问的时间
}pl_type;
pl_type pl[total_vp];               //页面结构数组

struct pfc_struct{                  //页面控制结构
     int pn,						//页面号
		 pfn;						//内存区页面的帧号
     struct pfc_struct *next;		//页面指针，用于维护内存缓冲区的链式结构
};
typedef struct pfc_struct pfc_type;  //主存区页面控制结构别名
pfc_type pfc[total_vp],				 //主存区页面控制结构数组
*freepf_head,						 //主存区页面控制结构的空闲页面头指针
*busypf_head,						 //主存区页面控制结构的忙页面头指针
*busypf_tail;						 //主存区页面控制结构的忙页面尾指针
int diseffect;						 //页错误计数器，初次把页面载入主存时也当做页错误
int a[total_instruction];			 //随即指令流数组
int page[total_instruction];		 //指令对应的页面号
int offset[total_instruction];		 //指令所在页面中的偏移量

int  initialize(int);				//初始化页面结构数组和页面控制结构数组
int  FIFO(int);						//先进先出算法
int  LRU(int);						//最近最久未使用算法
int  OPT(int);						//最佳置换算法
int  CLOCK(int);					//简单时钟(钟表)算法
int  LFR(int);                       //最少使用（LFR）页面置换算法

int main( )
{
    int s;		//随机数
	int	i;
    srand(10*getpid()); /*每次运行时进程号不同，用来作为初始化随机数队列的"种子"*/

	printf("\n------------通过随机数产生一个指令序列，共 320 条指令------------\n");
    for (i=0; i<total_instruction; i+=4) //产生指令队列
    {
        s = (int)((float)(total_instruction-1)*(rand()/(RAND_MAX+1.0)));
        a[i]=s+1; //任选一指令访问点m,顺序执行一条指令
        a[i+1]=(int)((float)(s+1)*(rand()/(RAND_MAX+1.0))); //执行前地址指令m'
        a[i+2]=a[i+1]+1; //顺序执行一条指令
        a[i+3]=a[i+2] + 1 + (int)((float)(total_instruction-1-(a[i+2]+1))*(rand()/(RAND_MAX+1.0)));
        printf("%6d%6d%6d%6d\n", a[i],a[i+1],a[i+2],a[i+3]);
        
    }
	printf("-----------2.指令序列变换成页地址流-------\n");
	for (i=0;i<total_instruction;i++) //将指令序列变换成页地址流
    {
        page[i]=a[i]/10;
        offset[i]=a[i]%10;
        printf("%d-",page[i]);
    }
	printf("\n----------3. 计算并输出下述各种算法在不同内存容量下的命中率--------\n");
    printf("Page\t FIFO\t LRU\t OPT\t LFR\n");
    for(i=4;i<=32;i++)   //用户内存工作区从个页面到个页面
    {
        printf(" %2d \t",i);
        FIFO(i);
        LRU(i);
	    OPT(i);
        LFR(i);
        printf("\n");
    }
return 0;
}

//初始化页面结构数组和页面控制结构数组
//total_pf;  用户进程的内存页面数
int initialize(int total_pf)
{
    int i;
    diseffect=0;
    for(i=0;i<total_vp;i++)
	{
		pl[i].pn=i;
		pl[i].pfn=INVALID;          //置页面所在主存区的帧号为-1.表示该页不在主存中
		pl[i].counter=0;			//置页面结构中的访问次数为
		pl[i].time=-1;				//置页面结构中的上次访问的时间为-1
	}
	for(i=0;i<total_pf-1;i++)
	{
		pfc[i].next=&pfc[i+1];		  //建立pfc[i-1]和pfc[i]之间的链接
		pfc[i].pfn=i;				  //初始化主存区页面的帧号
	}
	pfc[total_pf-1].next=NULL;
	pfc[total_pf-1].pfn=total_pf-1;
	freepf_head=&pfc[0];			//主存区页面控制结构的空闲页面头指针指向pfc[0]
	return 0;
}



//最近最久未使用算法
//int total_pf;       用户进程的内存页面数
int LRU (int total_pf)
{
    int MinT;					//最小的访问时间，即很久没被访问过
	int MinPn;					//拥有最小的访问时间的页的页号
	int i,j;
	int CurrentTime;							//系统当前时间
    initialize(total_pf);						//初始化页面结构数组和页面控制结构数组
    CurrentTime=0;
	diseffect=0;
	for(i=0;i<total_instruction;i++)
	{
		if(pl[page[i]].pfn==INVALID)             //页面失效
		{
			diseffect++;							//页错误次数加
            if(freepf_head==NULL)               //无空闲页面
            {
               MinT=100000;
			   for(j=0;j<total_vp;j++){            //找出time的最小值，表明该页很久没被访问过
				   if(MinT>pl[j].time&&pl[j].pfn!=INVALID)
				   {
                       MinT=pl[j].time;
                       MinPn=j;
				   }
			   }
			   freepf_head=&pfc[pl[MinPn].pfn];   //最久没被访问过的页被释放
			   pl[MinPn].pfn=INVALID;			 //最久没被访问过的页被换出主存
			   pl[MinPn].time=-1;				//最久没被访问过的页的访问时间置为无效
			   freepf_head->next=NULL;
			}
            pl[page[i]].pfn=freepf_head->pfn;      //有空闲页面,把相应的页面换入主存，并把pfn改为相应的帧号
            pl[page[i]].time=CurrentTime;			//令访问时间为当前系统时间
            freepf_head=freepf_head->next;        //减少一个空闲页面
		}
		else
			pl[page[i]].time=CurrentTime;        //命中则刷新该单元的访问时间
		CurrentTime++;                           //系统当前时间加
    }
	printf("%6.3f\t",1-(float)diseffect/320);
	return 0;
}



//最佳置换算法
//int total_pf;       用户进程的内存页面数
int OPT(int total_pf)
{
	int i,j;
	int MaxD;						//将来最近一次访问的距离的最大值（以时间单元度量）
	int MaxPn;						//将来最近一次访问的距离的最大值的页号
	int dis;						//距离计数器
	int dist[total_vp];				//距离数组，保存距离上一次访问的时间差距个数
	initialize(total_pf);				//初始化页面结构数组和页面控制结构数组
	diseffect=0;
	for(i=0;i<total_instruction;i++)
	{
		if(pl[page[i]].pfn==INVALID)		//页面失效
		{
			diseffect++;					//页错误次数加
			if(freepf_head==NULL)			//无空闲页面
			{
				for(j=0;j<total_vp;j++)
				{
					if(pl[j].pfn!=INVALID)	//如果该页在主存中
						dist[j]=100000;		// 该页关联的距离值改为最大值
					else
						dist[j]=0;			//如果不在该页主存中，该页关联的距离值改为
				}
				dis=1;						//初始距离值为
				for(j=i+1;j<total_instruction;j++)  //从要替换的指令的下一条算起，
				{
					if(pl[page[j]].pfn!=INVALID &&pl[page[j]].counter==0)	//如果该页在主存中,并且是将要最近访问的页
					//if(pl[page[j]].pfn!=INVALID && dist[page[j]]==100000)  //此条语句原理与上相同
					{	dist[page[j]]=dis;			//距离值改为dis
						pl[page[j]].counter=1;		//使访问次数标志加，区别第一次访问和第二次访问
					}
					dis++;
				}
				MaxD=-1;
				for(j=0;j<total_vp;j++)
				{
					pl[j].counter=0;				//重置访问次数为
					if(MaxD<dist[j])				//查找将来最近一次访问的距离的最大值及其序号
					{
						MaxD=dist[j];
						MaxPn=j;
					}
				}
					freepf_head=&pfc[pl[MaxPn].pfn];  //替换将来一段时间最久访问的页
					freepf_head->next=NULL;
					pl[MaxPn].pfn=INVALID;
			}
			pl[page[i]].pfn=freepf_head->pfn;    //把当前页换入主存中，并且把当前页的pfn改为换入页的帧号，
			freepf_head=freepf_head->next;		 //减少一个空闲页面
		}//if
	}//for
	printf("%6.3f\t",1-(float)diseffect/320);
	return 0;
}

//最少使用页面置换算法
//int total_pf;       用户进程的内存页面数
int LFR(int total_pf)
{
    int i,j;
    int use[total_vp];
    int MinUse;
    int MinPn;
    for(i=0;i<total_vp;i++)
    {
        use[i] = 0;  //初始访问次数都为0
    }
    initialize(total_pf);
	diseffect=0;
	for(i=0;i<total_instruction;i++)
	{
        use[page[i]]++;  //相应页面访问次数加一
		if(pl[page[i]].pfn==INVALID)             //页面失效
		{
			diseffect++;							//页错误次数加
            if(freepf_head==NULL)               //无空闲页面
            {
                MinUse=100000;
			    for(j=0;j<total_vp;j++){            //找出访问次数的最小值，表明该页很久没被访问
				    if(MinUse>use[j]&&pl[j].pfn!=INVALID)
				    {
                        MinUse=use[j];
                        MinPn=j;
				    }
			    }
			   freepf_head=&pfc[pl[MinPn].pfn];   //最少被访问过的页被释放
			   pl[MinPn].pfn=INVALID;			 //最少被访问过的页被换出主存
			   freepf_head->next=NULL;
			}
            pl[page[i]].pfn=freepf_head->pfn;      //有空闲页面,把相应的页面换入主存，并把pfn改为相应的帧号
            freepf_head=freepf_head->next;        //减少一个空闲页面
		}
		
	 	for(j=0;j<total_vp;j++)
        {
            use[j] /= 2;
        }                                           //Shift the counts right by 1 bit to decay average usage count

    }
	printf("%6.3f\t",1-(float)diseffect/320);
	return 0;

}
//简单时钟算法
//int total_pf;       用户进程的内存页面数
int CLOCK(int total_pf)
{
	int i;
	int use[total_vp];           //使用位
	int swap;
	swap=0;			 //发生替换
	initialize(total_pf);
	pfc_type *pnext;	 //时钟指针
	pfc_type *head;		 //队列头指针
	pnext=freepf_head;
	head=freepf_head;
	for(i=0;i<total_vp;i++){use[i]=0;}      //初始化使用位为
	diseffect=0;
	for(i=0;i<total_instruction;i++)
	{
		if (pl[page[i]].pfn==INVALID)         //页面失效,不在主存中
		{
			diseffect++;						//页错误次数加
			if(freepf_head==NULL)               //无空闲页面
			{

					while(use[pnext->pfn]==1)    //若时钟指针指向的页的使用位为，则改为并跳过
					{
						use[pnext->pfn]=0;
						pnext=pnext->next;
						if(pnext==NULL) pnext=head; //如果时钟指针到达队列尾部，重新返回头部
					}
					//换出被替换的页
					pl[pnext->pn].pfn=INVALID;
					swap=1;
			}
			if(use[pnext->pfn]==0){  //如果使用位为，则换入相应的页
				pl[page[i]].pfn=pnext->pfn;     //页面结构中要标记帧号
				pnext->pn=page[i];              //页面控制结构中要标记页号
				use[pnext->pfn]=1;				//重置使用位为
				pnext=pnext->next;				//时钟指针下移
				if(pnext==NULL) pnext=head;		//如果时钟指针到达队列尾部，重新返回头部
				if(swap==0){ freepf_head=freepf_head->next;	}
			}

		}else{//页面在主存中
			use[pl[page[i]].pfn]=1;       //刷新使用位为
		}

	}
	printf("%6.3f\t",1-(float)diseffect/320);
	return 0;
}


//先进先出算法版本
//int total_pf;       用户进程的内存页面数
//实现细节由CLOCK算法退化而来，与FIFO同效果
int FIFO(int total_pf)
{
	int i;
	int use[total_vp];
	int swap=0;
	initialize(total_pf);
	pfc_type *pnext,*head;
	pnext=freepf_head;
	head=freepf_head;
	for(i=0;i<total_vp;i++){use[i]=0;}
	diseffect=0;
	for(i=0;i<total_instruction;i++)
	{
		if (pl[page[i]].pfn==INVALID)         //页面失效,不在主存中
		{
			diseffect++;
			if(freepf_head==NULL)               //无空闲页面
			{
				while(use[pnext->pfn]==1)
				{
					use[pnext->pfn]=0;
					pnext=pnext->next;
					if(pnext==NULL) pnext=head;
				}
				//换出被替换的页
				pl[pnext->pn].pfn=INVALID;
				swap=1;
			}
			if(use[pnext->pfn]==0){  //如果使用位为，则换入相应的页
				pl[page[i]].pfn=pnext->pfn;     //页面结构中要标记帧号
				pnext->pn=page[i];              //页面控制结构中要标记页号
				use[pnext->pfn]=1;				//重置使用位为
				pnext=pnext->next;
				if(pnext==NULL) pnext=head;
				if(swap==0){ freepf_head=freepf_head->next;	}
			}
		}
	}
	printf("%6.3f\t",1-(float)diseffect/320);
	return 0;
}



