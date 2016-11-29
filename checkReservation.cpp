#include<iostream>
#include<time.h>
#include<string>
#include<iomanip>
#include"main.h"
#include<Windows.h>
#pragma warning (disable:4996)
using namespace std;

void firstDate(int *, int *, int *);
void secondDate(int *, int *, int *);
void thirdDate(int *, int *, int *);

/*void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
*/
//first f;
/*void first::setChoice(int ch){
	f.choice = ch;
}
int first::getChoice(){
	return f.choice;
}*/

int first::reservation()
{
	string leave, arrive;
	int year=0, month=0, date=0;
	int ch;

	gotoxy(20, 5); cout << "o-------------------------------------------------------o";
	
	gotoxy(20, 6); cout << "운행가능 지역 ";
	gotoxy(20, 7); cout << " 광주 ↔ 서울 | 부산 ↔ 서울 | 강릉 ↔ 의정부";
	gotoxy(20, 8); cout << endl;
	gotoxy(20, 9); cout << "출발지 : ";
	std::getline(cin, leave); cout << "  |  ";
	gotoxy(20, 11); cout << "도착지 : ";
	std::getline(cin, arrive);
	gotoxy(20, 12); cout << endl << endl;

	cout << "날짜================ " << endl;
	firstDate(&year, &month, &date);
	cout <<"|1."<< year << " " << month << " " << date << endl;
	secondDate(&year, &month, &date);
	cout << "|2." << year << " " << month << " " << date << endl;
	thirdDate(&year, &month, &date);
	cout << "|3." << year << " " << month << " " << date << endl;
	cout << "====================" << endl;
	cout << "선택 : ";
	cin >> choice;

	cout << endl;

	cout << "등급선택" << endl;
	cout << "ㅡㅡㅡㅡㅡㅡ" << endl;
	cout << "| 1. 전체  |" << endl;
	cout << "| 2. 일반  |" << endl;
	cout << "| 3. 우등  |" << endl;
	cout << "ㅡㅡㅡㅡㅡㅡ" << endl;
	cout << "선택 : ";
	cin >> choice;

	cout << "o------------------------------------------------------------o" << endl;
	cin >> ch;

	setChoice(ch);
	return getChoice();

}



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


	timer = time(NULL) + (24 * 60 * 60)+ (24 * 60 * 60);
	t = localtime(&timer);
	*year = t->tm_year + 1900;
	*month = t->tm_mon + 1;
	*date = t->tm_mday;
}