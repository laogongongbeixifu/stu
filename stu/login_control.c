#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "cgic.h"


int cgiMain(){


  fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
/*	fprintf(cgiOut, "<head><meta charset=\"utf-8\"/><title>查询结果</title>\
			<style>table {width:400px; margin: 50px auto; border: 1px solid gray; border-collapse: collapse; border-spacing: none; text-align:center;}\
			tr,td,th{border: 1px solid gray;}\
			</style>\
			</head>");*/

	fprintf(cgiOut, "<head><meta charset=\"utf-8\"><title>查询结果</title>\
		    <link rel=\"stylesheet\" href=\"/stu/public/css/bootstrap.min.css\">\
		</head>");

    char id[16] = "\0";
    char pwd[16] = "\0";
    int status = 0;

    status = cgiFormString("id",  id, 16);
  	if (status != cgiFormSuccess)
  	{
  		fprintf(cgiOut, "get id error!\n");
  		return 1;
  	}

    status = cgiFormString("pwd", pwd, 16);
  	if (status != cgiFormSuccess)
  	{
  		fprintf(cgiOut, "get pwd error!\n");
  		return 1;
  	}

    int ret;
  	MYSQL *db;
  	char sql[128] = "\0";

    db = mysql_init(NULL);
  	if (db == NULL)
  	{
  		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
  		return -1;
  	}

    db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
  	if (db == NULL)
  	{
  		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
  		mysql_close(db);
  		return -1;
  	}

    sprintf(sql, "select * from teacher where id = %d and pwd ='%s'",atoi(id),pwd);

    if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
  	{
  		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
  		mysql_close(db);
  		return -1;
  	}

    MYSQL_RES *res;
  	res = mysql_store_result(db);
  	if (res == NULL)
  	{
      printf("<html>\n");
      printf("<head><title>login error</title></head>\n");
      printf("<body><br>\n");
      printf("<h2> 登录失败！！</h2>\n");
      printf("<hr><p>\n");
      printf("<a href=/login.html>重新登陆！！</a>\n");
      printf("</body>\n");
      printf("</html>\n");
  	}
    else
    {
      printf("<html>\n");
      printf("<head><title>login success</title></head>\n");
      printf("<body><br>\n");
      printf("<h2> 登陆成功！！\n");
      printf("<hr><p>\n");
      printf("<a href=/>学生信息管理系统</a>\n");
      printf("</body>\n");
      printf("</html>\n");
    }

    return 0;

}
