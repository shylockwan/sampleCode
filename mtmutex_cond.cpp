#include <iostream>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
static char* data;
sem_t w_sem,r_sem;
pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mycond=PTHREAD_COND_INITIALIZER;
using namespace std;

void *t1func(void* arg)
{
	
	int a=*(int*)arg;
	
	while(1)
	{
		if(pthread_mutex_lock(&mymutex)>=0)
		{
			cout<<"thread_"<<a<<"write :"<<endl<<"<<";
			if(cin.getline(data,256)<0)
				cout<<"fail to input"<<endl;
			pthread_cond_signal(&mycond);
			pthread_mutex_unlock(&mymutex);
			
		}	
		usleep(500);		
	}

}
void *t2func(void* arg)
{
	int a=*(int*)arg;
	
	while(1)
	{
		if(pthread_mutex_lock(&mymutex)>=0)
		{
			
			while(strlen(data)<=0)
			{
				pthread_cond_wait(&mycond,&mymutex);			
			}
			int sz=strlen(data);
			cout<<"thread_"<<a<<"read :";
			for(int i=0;i<sz;i++)
				cout<<data[i];
			cout<<endl;
			pthread_mutex_unlock(&mymutex);
		}
		
		usleep(500);		
	}
}
int main()
{
	data=new char[256];
	memset(data,0,256);
	pthread_t tid1,tid2,tid3;
	if(sem_init(&r_sem,0,0)<0)
	{
		cout<<"fail to init Rsemaphore"<<endl;
	}
	if(sem_init(&w_sem,0,1)<0)
	{
		cout<<"fail to init Wsemaphore"<<endl;
	}
	
	int i1=1,i2=2,i3=3;
	if((pthread_create(&tid1,NULL,t1func,(void*) &i1))<0)
	{
		cout<<"error when create thread1"<<endl;
		return -1;
	}
	if((pthread_create(&tid2,NULL,t2func,(void*) &i2))<0)
	{
		cout<<"error when create thread1"<<endl;
		return -1;
	}
	pthread_join(tid1,NULL);
	
	
	return 0;
}
