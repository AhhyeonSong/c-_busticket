#include<iostream>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
using namespace std;

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int main(){
	//showBoard();
	int y, m, d, h, mi, sn;
	gotoxy(15,3);
	gotoxy(15, 3); cout << "o----------------------����ϱ�----------------------o" ;
	gotoxy(15, 4); cout << "|                                                    |";
	gotoxy(15, 5); cout << "|    ��¥�Է�(yyyy�� mm�� dd��) :                    |" ;
	gotoxy(15, 6); cout << "|           �ð��Է�(hh�� mm��) :                    |" ;
	gotoxy(15, 7); cout << "|                  �¼���ȣ�Է� :                    |";
	gotoxy(15, 8); cout << "|                                                    |";
	gotoxy(15, 9); cout << "o----------------------------------------------------o";
	gotoxy(49, 5); cin >> y >> m >> d;
	gotoxy(49, 6); cin >>h  >> mi;
	gotoxy(49, 7); cin >> sn;	

}