#include <iostream>
#include <cstring>
#include <iomanip>
#include <conio.h>
#include <mysql.h>
using namespace std;


class data{
public:
	MYSQL_RES *sql_result;  // the results
	MYSQL_ROW sql_row;      // the results row (line by line)
	void selectTicket(int);
	int connect();
};
