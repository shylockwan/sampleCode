//������Բο�mysql�û��ֲ�25.2�� C API��ʹ�õ�˵��
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h> 
#include <iostream>
using namespace std;
//��MySQL����ʱ��Ӧ�ó���Ӧʹ�ø�һ����ԭ��
//
//1.    ͨ������mysql_library_init()����ʼ��MySQL�⡣
//
//2.    ͨ������mysql_init()��ʼ�����Ӵ�����򣬲�ͨ������mysql_real_connect()���ӵ���������
//
//3.    ����SQL��䲢������������������������У���ϸ������ʹ�����ķ�������
//
//4.    ͨ������mysql_close()���ر���MySQL�����������ӡ�
//
//5.    ͨ������mysql_library_end()������MySQL���ʹ�á�

#if 1
int main()
{
    const char user[] = "root";         //username
    const char pswd[] = "******";         //password
    const char host[] = "localhost";    //or"127.0.0.1"
    const char table[] = "test";        //database
    unsigned int port = 3306;           //server port        
    MYSQL mysql;//struct MYSQL���ݿ����ӵľ��
    MYSQL_RES *result;//struct MYSQL_RES ���ز�ѯ�����SELECT, SHOW, DESCRIBE, EXPLAIN��
    MYSQL_ROW sql_row;//ָ����ĳ�����ݵ�ָ���ָ��
    MYSQL_FIELD *fd;//struct MYSQL_FIELD�������ֶε��������ֶ��������ͺʹ�С����������ֵvalue��ͨ���ظ�����mysql_fetch_field()����Ϊÿ���ֶλ��MYSQL_FIELD�ṹ
    char column[32][32];
    int res;
    mysql_init(&mysql);//��ʡ�Զ�mysql_library_init()�ĵ��ã���Ϊ��Ҫʱ��mysql_init()���Զ�������
    if(mysql_real_connect(&mysql,host,user,pswd,table,port,NULL,0))
    {
        cout<<"connect succeed!"<<endl;
        mysql_query(&mysql, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
        res=mysql_query(&mysql,"select * from person");
		//��ѯ�����Ӵ��ڻ״̬ʱ���ͻ��˻����ʹ��mysql_query()��mysql_real_query()�����������SQL��ѯ�����ߵĲ�����ڣ�mysql_query()Ԥ�ڵĲ�ѯΪָ���ġ���Null�ս���ַ�������mysql_real_query()Ԥ�ڵ��Ǽ����ַ���������ַ����������������ݣ����п��ܰ���Null�ֽڣ����ͱ���ʹ��mysql_real_query()��
		if(!res)
        {
			/*�ͻ��˴��������ķ�ʽ�����֡�
			һ�ַ�ʽ�ǣ�ͨ������mysql_store_result()��һ���Եؼ��������������
			�ú����ܴӷ�������ò�ѯ���ص������У��������Ǳ����ڿͻ��ˡ�
			�ڶ��ַ�ʽ����Կͻ��˵ģ�ͨ������mysql_use_result()���ԡ����С�������������г�ʼ������
			�ú����ܳ�ʼ����������������ܴӷ���������κ�ʵ���С�*/			
            result=mysql_store_result(&mysql);//�����ѯ�������ݵ�result
            if(result)
            {
                int i,j;
				//mysql_num_fields(MYSQL_RES) ���ؽ�����е�������
				//mysql_num_rows(MYSQL_RES) ���ؽ�����е�������
                cout<<"number of result: "<<(unsigned long)mysql_num_rows(result)<<endl;
                for(i=0;fd=mysql_fetch_field(result);i++)//��ȡ����
                {
                    strcpy(column[i],fd->name);
                }
                j=mysql_num_fields(result);
                for(i=0;i<j;i++)
                {
                    printf("%s\t",column[i]);
                }
                printf("\n");
				/*mysql_fetch_field() ������һ�����ֶε����͡�
				  mysql_fetch_field_direct() �����ֶα�ţ����ر��ֶε����͡�
				  mysql_fetch_fields() ���������ֶνṹ�����顣
				  mysql_fetch_lengths() ���ص�ǰ���������еĳ��ȡ�
				  mysql_fetch_row() �ӽ�����л�ȡ��һ��*/
 

                while(sql_row=mysql_fetch_row(result))//��ȡ���������
                {
                    for(i=0;i<j;i++)
                    {
                        printf("%s\n",sql_row[i]);
                    }
                    printf("\n");
                }
            }
        }
        else
        {
            cout<<"query sql failed!"<<endl;
        }
    }
    else
    {
        cout<<"connect failed!"<<endl;
    }
    if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
    mysql_close(&mysql);//�Ͽ�����
    return 0;
}
#endif