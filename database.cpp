#include "stdio.h"
#include <iostream>;
#include<string.h>
#include "winsock2.h"
#include "mysql.h"
using namespace std;
#pragma comment(lib,"libmysql.lib")
#define TABLE_NAME_SIZE				100
#define TABLE_COLUMNS_MAX_SIZE		100
#define TABLE_COLUMN_SIZE			20
#define TABLE_SEAT_SIZE 28


// /usr/include/mysql/mysql.h
// /usr/lib64/mysql/libmysqlclient.so

const char *host = (char*) "localhost";
const char *user = (char*) "mirim";
const char *pw = (char*)  "mirim";
const char *db = (char*) "mirim";
MYSQL *connection;      // the connection
MYSQL_RES *sql_result;  // the results
MYSQL_ROW sql_row;      // the results row (line by line)

int query_state;

int main()
{
	string query="";
	connection = mysql_init(NULL);
	if (mysql_real_connect(connection, host, user, pw, db, 3306, NULL, 0) == NULL)
	{
		printf("에러 : %d, %s\n", mysql_errno(connection), mysql_error(connection));
		return 1;
	}
	else
	{
		printf("연결 성공\n");
		mysql_query(connection, "set session character_set_connection=euckr;");
		mysql_query(connection, "set session character_set_results=euckr;");
		mysql_query(connection, "set session character_set_client=euckr;");

		if (mysql_select_db(connection, db)) // 데이터베이스 선택
		{
			printf("에러 : %d, %s\n", mysql_errno(connection), mysql_error(connection));
			return 1;
		}
		mysql_query(connection, "SELECT * FROM ticket");
		sql_result = mysql_use_result(connection);
		printf("Returning List of Names : \n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL){
			//printf("%s %s %s %s %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
		}

		mysql_query(connection, "SELECT * TIME Where date like 1 ticket");
		sql_result = mysql_use_result(connection);
		printf("Returning List of Names : \n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			printf("%s %s %s %s %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
		mysql_close(connection);
		mysql_close(connection);
	}

	return 0;
}

/*void selectTicket(string d){
	mysql_query(connection, "set session character_set_connection=euckr;");
	mysql_query(connection, "set session character_set_results=euckr;");
	mysql_query(connection, "set session character_set_client=euckr;");
	connection = mysql_init(NULL);
	mysql_query(connection, "SELECT * TIME Where date like 1 ticket");
	sql_result = mysql_use_result(connection);
	printf("Returning List of Names : \n");
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
		printf("%s %s %s %s %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
	mysql_close(connection);
}*/