//题目 给定无空格字符串，以及一个字典，根据字典查阅，将字符串用空格分成多个单词
//本题我的主要思路是回溯剪枝法，以输入的无空格字符串size为N，令N从0~size-1，
//枚举对比字符串和字典，一旦有问题，则剪枝，回溯，再枚举
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;
vector<string> dict;
string str;
int cmpStr(char* src,int n,string dst)
{
	if(src==NULL||n==0)
		return 1;
	string temp(src);
	temp[n]='\0';
	return strcmp(temp.c_str(),dst.c_str());
}

int main(int argc,char** argv)
{
	int sz=dict.size();
	stack<int> step;
	char* ptr=&(str[0]);
	int n=1;
	while(*ptr!='\0')//遍历原始字符串
	{
		bool flag=0;
		for(;;n++)//遍历字符串长度
		{
			if(ptr[n]=='\0')
				break;
			bool dict_find=0;
			for(int j=0;j<sz;j++) //查阅字典
			{
				if(cmpStr(ptr,n,dict[j])==0)
				{
					
					dict_find=1;
					break;
				}
			}
			if(dict_find)
			{
				step.push(n);
				flag=1;
				break;
			}
				
		}
		if(step.empty())
			break;
		if(flag==0)
		{
			n=step.top();
			step.pop();
			ptr-=n;
		}
		else
		{
			n=1;
			ptr+=step.top();
		}	
		
	}
	//最后根据step输出字符串空格
  return 0;
}