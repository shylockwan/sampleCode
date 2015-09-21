#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using namespace std;
int main()
{
	int pid;
	int value;
	if(pid=fork()==0)
	{
		value+=2;
		cout<<"child process:"<<value<<endl;
	}
	else
	{
		value+=10;
		cout<<"father process"<<value<<endl;
	}
	return 0;
}

