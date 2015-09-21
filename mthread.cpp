#include <iostream>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
static char* data;
sem_t w_sem,r_sem;
using namespace std;

void *t1func(void* arg)
{
	
	int a=*(int*)arg;
	
	while(1)
	{
		sem_wait(&w_sem);
		cout<<"thread_"<<a<<"write :"<<endl<<"<<";
		if(cin.getline(data,256)<0)
			cout<<"fail to input"<<endl;
		else
			sem_post(&r_sem);
		sleep(1);		
	}

}
void *t2func(void* arg)
{
	int a=*(int*)arg;
	
	while(1)
	{
		sem_wait(&r_sem);
		int sz=strlen(data);
		cout<<"thread_"<<a<<"read :";
		for(int i=0;i<sz;i++)
			cout<<data[i];
		cout<<endl;
		sem_post(&w_sem);
		sleep(2);		
	}
}
int main()
{
	data=new char[256];
	memset(data,0,256);
	pthread_t tid1,tid2,tid3;
	if(sem_init(&r_sem,0,0)<0)
	{
		cout<<"fail to init semaphore"<<endl;
	}
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
	if((pthread_create(&tid3,NULL,t2func,(void*) &i3))<0)
	{
		cout<<"error when create thread1"<<endl;
		return -1;
	}
	
	
	int counts=0;
	void* value_ptr;
	while(1)
	{	
		
			if(pthread_join(tid1,&value_ptr)==0)
				break;
			else
			{
				cout<<"tid1 exit error"<<endl;
				return -1;
			}

	}
	
	return 0;
}
