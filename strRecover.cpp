//��Ŀ �����޿ո��ַ������Լ�һ���ֵ䣬�����ֵ���ģ����ַ����ÿո�ֳɶ������
//�����ҵ���Ҫ˼·�ǻ��ݼ�֦������������޿ո��ַ���sizeΪN����N��0~size-1��
//ö�ٶԱ��ַ������ֵ䣬һ�������⣬���֦�����ݣ���ö��
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
	while(*ptr!='\0')//����ԭʼ�ַ���
	{
		bool flag=0;
		for(;;n++)//�����ַ�������
		{
			if(ptr[n]=='\0')
				break;
			bool dict_find=0;
			for(int j=0;j<sz;j++) //�����ֵ�
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
	//������step����ַ����ո�
  return 0;
}