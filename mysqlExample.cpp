//具体可以参考mysql用户手册25.2中 C API库使用的说明
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h> 
#include <iostream>
using namespace std;
//与MySQL交互时，应用程序应使用该一般性原则：
//
//1.    通过调用mysql_library_init()，初始化MySQL库。
//
//2.    通过调用mysql_init()初始化连接处理程序，并通过调用mysql_real_connect()连接到服务器。
//
//3.    发出SQL语句并处理其结果。（在下面的讨论中，详细介绍了使用它的方法）。
//
//4.    通过调用mysql_close()，关闭与MySQL服务器的连接。
//
//5.    通过调用mysql_library_end()，结束MySQL库的使用。

#if 1
int main()
{
    const char user[] = "root";         //username
    const char pswd[] = "******";         //password
    const char host[] = "localhost";    //or"127.0.0.1"
    const char table[] = "test";        //database
    unsigned int port = 3306;           //server port        
    MYSQL mysql;//struct MYSQL数据库连接的句柄
    MYSQL_RES *result;//struct MYSQL_RES 返回查询结果（SELECT, SHOW, DESCRIBE, EXPLAIN）
    MYSQL_ROW sql_row;//指向表格某行数据的指针的指针
    MYSQL_FIELD *fd;//struct MYSQL_FIELD描述了字段的属性如字段名、类型和大小，但不包括值value。通过重复调用mysql_fetch_field()，可为每个字段获得MYSQL_FIELD结构
    char column[32][32];
    int res;
    mysql_init(&mysql);//可省略对mysql_library_init()的调用，因为必要时，mysql_init()会自动调用它
    if(mysql_real_connect(&mysql,host,user,pswd,table,port,NULL,0))
    {
        cout<<"connect succeed!"<<endl;
        mysql_query(&mysql, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
        res=mysql_query(&mysql,"select * from person");
		//查询当连接处于活动状态时，客户端或许会使用mysql_query()或mysql_real_query()向服务器发出SQL查询。两者的差别在于，mysql_query()预期的查询为指定的、由Null终结的字符串，而mysql_real_query()预期的是计数字符串。如果字符串包含二进制数据（其中可能包含Null字节），就必须使用mysql_real_query()。
		if(!res)
        {
			/*客户端处理结果集的方式有两种。
			一种方式是，通过调用mysql_store_result()，一次性地检索整个结果集。
			该函数能从服务器获得查询返回的所有行，并将它们保存在客户端。
			第二种方式是针对客户端的，通过调用mysql_use_result()，对“按行”结果集检索进行初始化处理。
			该函数能初始化检索结果，但不能从服务器获得任何实际行。*/			
            result=mysql_store_result(&mysql);//保存查询到的数据到result
            if(result)
            {
                int i,j;
				//mysql_num_fields(MYSQL_RES) 返回结果集中的列数。
				//mysql_num_rows(MYSQL_RES) 返回结果集中的行数。
                cout<<"number of result: "<<(unsigned long)mysql_num_rows(result)<<endl;
                for(i=0;fd=mysql_fetch_field(result);i++)//获取列名
                {
                    strcpy(column[i],fd->name);
                }
                j=mysql_num_fields(result);
                for(i=0;i<j;i++)
                {
                    printf("%s\t",column[i]);
                }
                printf("\n");
				/*mysql_fetch_field() 返回下一个表字段的类型。
				  mysql_fetch_field_direct() 给定字段编号，返回表字段的类型。
				  mysql_fetch_fields() 返回所有字段结构的数组。
				  mysql_fetch_lengths() 返回当前行中所有列的长度。
				  mysql_fetch_row() 从结果集中获取下一行*/
 

                while(sql_row=mysql_fetch_row(result))//获取具体的数据
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
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&mysql);//断开连接
    return 0;
}
#endif