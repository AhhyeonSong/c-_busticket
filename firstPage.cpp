#include<iostream>
#include<Windows.h>
#include <stdlib.h>
#include<iomanip>
#include "main.h"
using namespace std;

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
first f;
void first::setChoice(int ch){
	f.choice = ch;
}
int first::getChoice(){
	return f.choice;
}

int first::menu()
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
	gotoxy(35, 10); cout << "";
	gotoxy(35, 11); cout << "1. �����ϱ�" << endl;
	gotoxy(35, 12); cout << "2. ����ϱ�" << endl;
	gotoxy(35, 13); cout << "3. ����Ȯ��" << endl;
	gotoxy(35, 14); cout  << "���� : ";
	cin >> ch;

	setChoice(ch);
	return getChoice();
}