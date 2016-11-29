#include<iostream>
#include <stdlib.h>
#include<iomanip>
#include<time.h>
#include<string>
#include <conio.h>
#include<Windows.h>
#include "DBdata.h"
#include <mysql.h>
#pragma comment(lib,"libmysql.lib")
#pragma warning (disable:4996)
using namespace std;

#define TABLE_NAME_SIZE				100
#define TABLE_COLUMNS_MAX_SIZE		100
#define TABLE_COLUMN_SIZE			20
#define TABLE_SEAT_SIZE 28

#define SXmax 31
#define SYmax 7
#define EXmax 37
#define EYmax 16

const char *host = (char*) "localhost";
const char *user = (char*) "mirim";
const char *pw = (char*)  "mirim";
const char *db = (char*) "mirim";
MYSQL *connection;      // the connection
MYSQL_RES *sql_result;  // the results
MYSQL_ROW sql_row;      // the results row (line by line)


class choice{
public:
	int placeC=1;
	int dateC = 1;
	int gradeC = 1;
	int timeC = 1;
	int seatNum = 1;
};

class cancelChoice{
public:
	int placeC = 1;
	int dateC = 1;
	int timeC = 1;
	int seatNum = 1;
};

choice reChoice;  //�����ϱ�
choice seatC;     //�¼� ����

void firstDate(int *, int *, int *);
void secondDate(int *, int *, int *);
void thirdDate(int *, int *, int *);
int flag();

struct Seat{
	int dx = 0;
	int dy = 0;
	int flag = 0;
}s[29];


	void changeDate(){
		int year = 0, month = 0, date = 0;
		switch (reChoice.dateC){
		case 1: firstDate(&year, &month, &date);
			cout << year << " " << month << " " << date; break;
		case 2: secondDate(&year, &month, &date);
			cout <<year << " " << month << " " << date; break;
		case 3: thirdDate(&year, &month, &date);
			cout <<year << " " << month << " " << date; break;
		}
	}
	void changeTime(){
		switch (reChoice.timeC){
		case 1:
			cout << " 13:00"; break;
		case 2:
			cout << " 15:00"; break;
		case 3:
			cout << " 17:00"; break;
		}
	}
	void changeMovement(){
		switch (reChoice.placeC){
		case 1:
			cout << "���� [ ���� ��> ���� ]"; break;
		case 2:
			cout << "���� [ �λ� ��> ���� ]"; break;
		case 3:
			cout << "���� [ ���� ��> ������ ]"; break;
		}
	}


int connect()
{
	connection = mysql_init(NULL);
	if (mysql_real_connect(connection, host, user, pw, db, 3306, NULL, 0) == NULL)
	{
		printf("���� : %d, %s\n", mysql_errno(connection), mysql_error(connection));
		return 1;
	}
	else
	{
		mysql_query(connection, "set session character_set_connection=euckr;");
		mysql_query(connection, "set session character_set_results=euckr;");
		mysql_query(connection, "set session character_set_client=euckr;");

		if (mysql_select_db(connection, db)) // �����ͺ��̽� ����
		{
			printf("���� : %d, %s\n", mysql_errno(connection), mysql_error(connection));
			return 1;
		}
		
	}

	return 0;
}
string retime(int n){
	switch (n){
	case 1:
		return " '13:00'"; break;
	case 2:
		return " '15:00'"; break;
	case 3:
		return " '17:00'"; break;
	}
	return 0;
}

int gradeChoice(int time){
	connect();
	int n;
	string query = "select grade ";
	query += "from ticket where date=";
	query += to_string(reChoice.dateC) + "&&time=";
	query += retime(time);
	mysql_query(connection, query.c_str());
	sql_result = mysql_use_result(connection);
	sql_row = mysql_fetch_row(sql_result);
	if (strcmp(sql_row[0], "�Ϲ�"))
		 n=2;
	else if (strcmp(sql_row[0], "���"))
		 n=3;
	return n;
}

int restSeat(int time){
	connect();
	int count = 0;
	string query = "select ";

	for (int i = 1; i <= 27; i++){
		string seatN = to_string(i);
		query += "seat" + seatN + ",";
	}
	query += "seat28 ";
	query += "time from ticket where date=";
	query += to_string(reChoice.dateC) + "&&time=";
	query += retime(time);
	query += " && (grade =";
	//cyquery = query;
	switch (reChoice.gradeC){
	case 1:
		query += " '�Ϲ�' or grade='���')"; break;
	case 2:
		query += " '�Ϲ�')"; break;
	case 3:
		query += " '���')"; break;
	}
	mysql_query(connection, query.c_str());
	sql_result = mysql_use_result(connection);
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL){
		for (int i = 0; i < 28; i++){
			if (strcmp(sql_row[i], "0")){
				count++; //���� �¼��� üũ
			}
		}
	}
	return 28 - count;
}

int *totalFalg(){
	string query = "select ";
	int *total = new int[28];
	for (int i = 1; i <= 27; i++){
		string seatN = to_string(i);
		query += "seat" + seatN + ",";
	}
	query += "seat28 ";
	query += "from ticket where date =";
	query += to_string(reChoice.dateC) + " && time =";
	query += retime(reChoice.timeC);
	mysql_query(connection, query.c_str());
	sql_result = mysql_use_result(connection);
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL){
		for (int i = 0; i <28; i++){
			if (strcmp(sql_row[i], "0")){
				total[i] = 1;
			}
			else if (strcmp(sql_row[i], "1")){
				total[i] = 0;
			}
		}
	}
	return total;
}

int InfoCount(){
	string query = "select * from customer";
	string *Info=NULL;
	int count=0;
	mysql_query(connection, query.c_str());
	sql_result = mysql_use_result(connection);
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL){
		count++;
	}
	return count+1;
}

void totalInfo(){  //customer�� ����� ��� ���� ����
	int count = InfoCount();
	int select = 0;
	string query = "select * from customer";
	int year = 0, month = 0, date = 0;
	mysql_query(connection, query.c_str());
	sql_result = mysql_use_result(connection);
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL){
		select++;
		for (int i = 0; i < count; i++){
			if (i == 0){
				if (strcmp(sql_row[0], "1")){
					firstDate(&year, &month, &date);
				}
				else if (strcmp(sql_row[0], "2")){
					secondDate(&year, &month, &date);
				}
				else if (strcmp(sql_row[0], "3")){
					thirdDate(&year, &month, &date);
				}
				cout <<select<<"."<< year << " " << month << " " << date;
			}
			else if(i==1){
				cout <<" | " << sql_row[i] ;
			}
			else if (i == 2){
				cout << " | " << sql_row[i] << "�� �¼�" << endl;
			}
	//		item[i] = sql_row[i];
		}
	}
//	return item;
}


int updateSeat(){
	connect();
	string query = "update ticket set seat"; 
	query += to_string(seatC.seatNum);
	query += "=1 where date=";
	query += to_string(reChoice.dateC) + " && time =";
	query += retime(reChoice.timeC);
	mysql_query(connection, query.c_str());
	//sql_result = mysql_use_result(connection);
	//sql_row = mysql_fetch_row(sql_result);
	return 0;
}

void insertInfo(){
	connect();
	string query = "INSERT INTO customer VALUES(";
	query += to_string(reChoice.dateC) + ",";
	query += retime(reChoice.timeC)+",'";
	query += to_string(seatC.seatNum) + "')";
	mysql_query(connection, query.c_str());
}

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void move_arrow_key(char key, int *x, int *y, int x_a, int y_a, int x_b, int y_b){
	switch (key){
	case 72:// ����Ű �ƽ�Ű �ڵ�(UP)
		*y = *y - 1;
		if (*y<y_a) *y = x_a;
		break;
	case 75: //LEFT
		*x = *x - 2;
		if (*x<x_a) *x = x_a;
		break;
	case 77: //RIGHT
		(*x) += 2;
		if (*x>x_b) *x = x_b;
		break;
	case 80: //DOWN
		(*y)++;
		if (*y>y_b) *y = y_b;
		break;
	default:
		return;
	}

}

void gotoXY(int x, int y){
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int menu()
{
	int ch;
	gotoxy(20, 2); cout << "  ------------------------------------";
	gotoxy(20, 3); cout << "/         --    --    --    --    --  |";
	gotoxy(20, 4); cout << "|   ---  |  |  |  |  |  |  |  |  |  | |";
	gotoxy(20, 5); cout << "|  |   |  --    --    --    --    --  |";
	gotoxy(20, 6); cout << "|��|o  | �ѤѤѤѤѤѤѤѤѤѤѤѤѤ� |";
	gotoxy(20, 7); cout << "|��|   ���                   ���    |�� �� ��";
	gotoxy(20, 8); cout << "----- ��  ��---------------- ��  ��---";
	gotoxy(20, 9); cout << "       ���                   ��� ";
//	gotoxy(35, 10); cout << "";
	gotoxy(35, 11); cout << "1. �����ϱ�" << endl;
	gotoxy(35, 12); cout << "2. ����Ȯ��" << endl;
	gotoxy(35, 13); cout << "0. �����ϱ�" << endl;
	gotoxy(35, 14); cout << "���� : ";
	gotoxy(42, 14); cin >> ch;
	return ch;
}

int reservation()
{
	
	//choice reChoice;
	string leave, arrive;
	int year = 0, month = 0, date = 0;
	int *t = totalFalg();
	cout << t[0];
	gotoxy(10, 5); cout << "�ޡ������������������������������";
	gotoxy(10, 6); cout << "��                                                          ��";
	gotoxy(10, 7); cout << "��                    ���డ�� ����                         ��";
	gotoxy(10, 8); cout << "��     1.���� �� ���� | 2.�λ� �� ���� | 3.���� �� ������   ��";
	gotoxy(10, 9); cout << "��                                                          ��";
	gotoxy(10, 10); cout <<"��                    ����� :                              ��"; 
	gotoxy(10, 11);cout << "��    ���� :            |                                   ��";
	gotoxy(10, 12);cout << "��                    ������ :                              ��"; 
	gotoxy(10, 13);cout << "��                                                          ��";
	gotoxy(10, 14); cout <<"��     ��¥-------------------    �ð�-------------------   ��" << endl;
	firstDate(&year, &month, &date);
	gotoxy(10, 15); cout <<"��     |1." << year << " " << month << " " << date <<"          |    | 1.13:00              |  ��";
	secondDate(&year, &month, &date);
	gotoxy(10, 16); cout <<"��     |2." << year << " " << month << " " << date <<"          |    | 2.15:00              |  ��";
	thirdDate(&year, &month, &date);
	gotoxy(10, 17); cout <<"��     |3." << year << " " << month << " " << date << "          |    | 3.17:00              |  ��";
	gotoxy(10, 18); cout <<"��      ----------------------      ----------------------  ��";
	gotoxy(10, 19); cout <<"��     ���� :                                               ��";
	gotoxy(10, 20); cout << "��                                                          ��";
	gotoxy(10, 21); cout << "��     ���-------------------                              ��";
	gotoxy(10, 22); cout << "��     |1. ��ü               |                             ��";
	gotoxy(10, 23); cout << "��     |2. �Ϲ�               |                             ��";
	gotoxy(10, 24); cout << "��     |3. ���               |                             ��";
	gotoxy(10, 25); cout << "��      ----------------------                              ��";
	gotoxy(10, 26); cout << "��     ���� :                                               ��";
	gotoxy(10, 27); cout << "��                                                          ��";
	gotoxy(10, 28); cout <<"�ޡ������������������������������";
	gotoxy(43, 19); cout << " ����: ";

	while (1){
		gotoxy(23, 11); cin >> reChoice.placeC;
		if (reChoice.placeC == 1 || reChoice.placeC == 2 || reChoice.placeC == 3) break;
	}
	if (reChoice.placeC == 1){ leave = "����";	arrive = "����"; }
	else if (reChoice.placeC == 2){ leave = "�λ�";	arrive = "����"; }
	else if (reChoice.placeC == 3){ leave = "����";	arrive = "������"; }
	gotoxy(41, 10); cout << leave;
	gotoxy(41, 12); cout << arrive;
	while (1){
		gotoxy(26, 19); cin >> reChoice.dateC;
		if (reChoice.dateC == 1 || reChoice.dateC == 2 || reChoice.dateC == 3) break;
	}
	while(1){
		gotoxy(23, 26); cin >> reChoice.gradeC;
		if (reChoice.gradeC == 1 || reChoice.gradeC == 2 || reChoice.gradeC == 3) break;
	}
	
	int count;
	//n3 = gradeChoice3();//cout << gradeChoice(1);
	if (reChoice.gradeC == 1){
		gotoxy(55, 15); cout << "�����¼�: " << restSeat(1);
		gotoxy(55, 16); cout << "�����¼�: " << restSeat(2);
		gotoxy(55, 17); cout << "�����¼�: " << restSeat(3);
	}
	else if (reChoice.gradeC == 2){
		gotoxy(55, 15); cout << "�����¼�: " << restSeat(1);	if (gradeChoice(1) == 2) cout << "(X)";
		gotoxy(55, 16); cout << "�����¼�: " << restSeat(2);	if (gradeChoice(2) == 2); cout << "(X)";
		gotoxy(55, 17); cout << "�����¼�: " << restSeat(3);	//if (gradeChoice(3) == 2); cout << "(X)";
	}
	else if (reChoice.gradeC == 3){
		gotoxy(55, 15); cout << "�����¼�: " << restSeat(1);	if (gradeChoice(1) == 3) cout << "(X)";
		gotoxy(55, 16); cout << "�����¼�: " << restSeat(2);	if (gradeChoice(2) == 3) cout << "(X)";
		gotoxy(55, 17); cout << "�����¼�: " << restSeat(3);	//if (gradeChoice(3) == 3) cout << "(X)";
	}

	while (1){
		gotoxy(53, 19); cin >> reChoice.timeC;
		if (reChoice.timeC == 1 || reChoice.timeC == 2 || reChoice.timeC == 3) break;
	}
	
	return 0;
}

void seat(){
	char check = '��';
	int flag = 0, count;
	int *t = totalFalg();
	for (int i = 0; i < 24; i++){
		if ((i + 1) % 3 != 0){
			count = 6;
			for (int i = 1; i <= 25; i += 3){
				gotoxy(30, ++count);	s[i].flag = t[i-1];
				if (s[i].flag == 0){
					cout << "��";
				}
				else if (s[i].flag == 1){
					cout << "��";
				}
				s[i].dx = 31; s[i].dy = count + 1; //s[i].flag =0;
			}
			count = 6;
			for (int i = 2; i <= 26; i += 3){
				gotoxy(32, ++count);	s[i].flag = t[i-1];
				if (s[i].flag == 0){
					cout << "��";
				}
				else if (s[i].flag == 1){
					cout << "��";
				}
				s[i].dx = 33; s[i].dy = count + 1;  //s[i].flag=0;
			}
		}
		count = 6;
		if ((i + 1) % 3 == 0){
			for (int i = 3; i <= 28; i += 3){
				gotoxy(36, ++count); s[i].flag = t[i-1];
				if (s[i].flag == 0){
					cout << "��";
				}
				else if (s[i].flag == 1){
					cout << "��";
				}
				s[i].dx = 37; s[i].dy = count + 1;  //s[i].flag = 0;
				
			}
		}
	}
	count = 28;
	for (int i = 25; i < 29; i++){
		gotoxy(count += 2, 15); s[i].flag = t[i-1];
		if (s[i].flag == 0){
			cout << "��";
		}
		else if (s[i].flag == 1){
			cout << "��";
		}
		s[i].dx = count + 1; s[i].dy = 16;  s[i].flag = 0;
	}

}

int seatChoice(){
	//choice seatC;
	int mySeat;
	int *t = totalFalg();
	int flag=0;// ���� ������ �ڸ�����
	gotoxy(25, 6); cout << "--------�¼������ϱ�--------" << endl;
	seat();
	char key;
	int x = 31, y = 8;
	do{
		gotoXY(x, y);
		printf("��");// �����̴� ����
		if (getch() == '\r'){
			for (int i = 1; i < 29; i++){
				if (x == s[i].dx){
					if (y == s[i].dy){
						if (t[i - 1] == 0){
							flag = 1;
							break; 
						}
						else if (t[i - 1] == 1){
							gotoxy(25, 18); cout << "�̹� ����� �ڸ� �Դϴ�(ENTER)" << endl;
						}
					}
				}
			}
		}
		if (flag == 1) break;
		else  key = getch();
		gotoXY(x, y);
		for (int i = 1; i < 29; i++){
			if (x == s[i].dx){
				if (y == s[i].dy){
					if (t[i-1] == 0)	printf("��"); 
					else if (t[i-1] == 1)	printf("��");
				}
			}
		}// ������ ������ ���� �ٽ� ���� �����
		move_arrow_key(key, &x, &y, SXmax, SYmax, EXmax, EYmax);

	} while (key != 27);
	
	for (int i = 1; i < 29; i++){
		if (x == s[i].dx){
			if (y == s[i].dy){
				seatC.seatNum = i;
			}
		}
	}
	return 0;
}

int settle(){
	//choice se;
	char settleCheck;
	char w;
	int year = 0, month = 0, date = 0;
	gotoxy(15, 3); cout << "o------------����â------------o";
	gotoxy(15, 4); cout << "|   " << seatC.seatNum << "�� �¼�                  |";
	gotoxy(15, 5);
	cout << "|     ���೯¥ : "; changeDate(); cout<< "    |";
	gotoxy(15, 6);
	cout << "|     ����ð� :"; changeTime(); cout<<"        |";
	gotoxy(15, 7);
	cout << "|    "; changeMovement(); cout<<"   | ";
	gotoxy(15, 8); cout << "o-----------------------------o";
	gotoxy(15, 10); cout << " �� �� �� �� �� �� �� �� ?(y/n)";
	cin >> settleCheck;
	if (settleCheck == 'y'){
		updateSeat();
		insertInfo();
		gotoxy(15, 11); cout << "������ �Ϸ��߽��ϴ�(ENTER)" << endl;
		w = getch();
		system("cls");
		return 0;
	}
	else if (settleCheck == 'n'){
		return 1;
	}
	return 0;
}

//�̰Ÿ��� �ϱ�!!! DB�� �̰� ���ϰ� �ϱ�

void firstDate(int *year, int *month, int *date){
	time_t timer; 
	struct tm *t;


	timer = time(NULL);
	t = localtime(&timer);
	*year = t->tm_year + 1900;
	*month = t->tm_mon + 1;
	*date = t->tm_mday;
	
}

void secondDate(int *year, int *month, int *date){
	time_t timer;
	struct tm *t;

	timer = time(NULL) + (24 * 60 * 60);
	t = localtime(&timer);
	*year = t->tm_year + 1900;
	*month = t->tm_mon + 1;
	*date = t->tm_mday;
}

void thirdDate(int *year, int *month, int *date){
	time_t timer;
	struct tm *t;


	timer = time(NULL) + (24 * 60 * 60) + (24 * 60 * 60);
	t = localtime(&timer);
	*year = t->tm_year + 1900;
	*month = t->tm_mon + 1;
	*date = t->tm_mday;
}


int main(){
	connect();
	while (1){
		if (menu() == 1){
			system("cls");
			reservation();
			system("cls");
			seatChoice();
			system("cls");
			settle();
			system("cls");
		}
		else if (menu() == 2){
			char w;
			system("cls");
			gotoxy(0, 3); cout << "------------��������-----------";
			gotoxy(0, 4); totalInfo();
			cout << endl << endl;
			cout << "Ű���带 ������ �������� �̵��մϴ�" << endl;
			w = getch();
			system("cls");
		}
		else if (menu() == 0){
			system("cls");
			break;
		}
		else{
			char w;
			gotoxy(27, 20); cout << "�߸��Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���" << endl;
			w = getch();
			system("cls");
		}
	}
	gotoxy(27, 10); cout << "���α׷��� �����߽��ϴ�" << endl;
}