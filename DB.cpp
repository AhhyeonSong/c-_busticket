#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <mysql.h>
#include<string>
#include "DBdata.h"
using namespace std;
#pragma warning (disable:4996)
#pragma comment(lib,"libmysql.lib")
#define TABLE_NAME_SIZE				100
#define TABLE_COLUMNS_MAX_SIZE		100
#define TABLE_COLUMN_SIZE			20
#define TABLE_SEAT_SIZE 28

const char *host = (char*) "localhost";
const char *user = (char*) "mirim";
const char *pw = (char*)  "mirim";
const char *db = (char*) "mirim";
MYSQL *connection;      // the connection
MYSQL_RES *sql_result;  // the results
MYSQL_ROW sql_row;      // the results row (line by line)

int flag();

int *totalFalg(){
	string query = "select ";
	int *total = new int[28];
	for (int i = 1; i <= 27; i++){
		string seatN = to_string(i);
		query += "seat" + seatN + ",";
	}
	query += "seat28 ";
	query += "from ticket where date=1&&time='13:00'";
	//query += to_string(1) + " && time =";
/*	switch (1){
	case 1:
		query += " '13:00'"; break;
	case 2:
		query += " '15:00'"; break;
	case 3:
		query += " '17:00'"; break;
	}*/
	mysql_query(connection, query.c_str());
	sql_result = mysql_use_result(connection);
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL){
		for (int i = 0; i <28; i++){
			if (strcmp(sql_row[i], "0")){
				//cout << "1";
				total[i] = 1;
			}
			else if (strcmp(sql_row[i], "1")){
				//cout << "0";
				total[i] = 0;
			}
		}
	}
	return total;
}

int restSeat(int time){
	int count = 2;
	string query = "select ";
	for (int i = 1; i <= 27; i++){
		string seatN = to_string(i);
		query += "seat" + seatN + ",";
	}
	query += "seat28 ";
	query += "from ticket where date=&&time=";
	switch (time){
	case 1:
		query += " '13:00'"; break;
	case 2:
		query += " '15:00'"; break;
	case 3:
		query += " '17:00'"; break;
	}
	cout << query;
	mysql_query(connection, query.c_str());
	sql_result = mysql_use_result(connection);
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL){
		for (int i = 0; i <28; i++){
			if (strcmp(sql_row[i], "0")){
				count++; //남은 좌석수 체크
			}
		}
	}
	return count;
}

int main()
{

	connection = mysql_init(NULL);
	if (mysql_real_connect(connection, host, user, pw, db, 3306, NULL, 0) == NULL)
	{
		printf("에러 : %d, %s\n", mysql_errno(connection), mysql_error(connection));
		return 1;
	}
	else
	{
		mysql_query(connection, "set session character_set_connection=euckr;");
		mysql_query(connection, "set session character_set_results=euckr;");
		mysql_query(connection, "set session character_set_client=euckr;");

		if (mysql_select_db(connection, db)) // 데이터베이스 선택
		{
			printf("에러 : %d, %s\n", mysql_errno(connection), mysql_error(connection));
			return 1;
		}
		int n = 0;
		string query = "select grade ";
		query += "from ticket where date=";
		query += to_string(1) + "&&time='13:00'";
		cout << query;
		mysql_query(connection, query.c_str());
		sql_result = mysql_use_result(connection);
		sql_row = mysql_fetch_row(sql_result);
		if (strcmp(sql_row[0], "일반"))
			n = 2;
		else if (strcmp(sql_row[0], "우등"))
			n = 3;
		cout << n;
	}
	return 0;
}
