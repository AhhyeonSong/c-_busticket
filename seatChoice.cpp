#include<iostream>
#include<string.h>
#include <windows.h>
#include <conio.h>
#pragma warning(disable:4996)
using namespace std;

#define SXmax 31
#define SYmax 7
#define EXmax 37
#define EYmax 16

struct Seat{
	int dx=0;
	int dy=0;
	int flag=0;
}s[29];

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
		(*x)+=2;
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
	COORD Pos = { x-1 , y-1  };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


void seat(){
	char check = '��';
	int flag = 0, count ;
	for (int i = 0; i < 24; i++){
		if ((i + 1) % 3 != 0){
			count = 6;
			for (int i = 1; i <= 25; i += 3){
					gotoxy(30, ++count); cout << "��";
					s[i].dx = 31; s[i].dy = count+1; s[i].flag = 0;
			}
			count = 6;
			for (int i = 2; i <= 26; i += 3){
					gotoxy(32, ++count); cout << "�� ";
					s[i].dx = 33; s[i].dy = count+1; s[i].flag = 0;
			}
		}
		count = 6;
		if ((i + 1) % 3 == 0){
			for (int i = 3; i <= 28; i += 3){
				gotoxy(36, ++count); cout << "��";
				s[i].dx = 37; s[i].dy = count+1; s[i].flag = 0;
			}
		}
	}
	count = 28;
	for (int i = 25; i < 29; i++){
			gotoxy(count+=2, 15); cout << "��";
			s[i].dx = count+1; s[i].dy = 16; s[i].flag = 0;
	}
	
}



int seatChoice(){
	gotoxy(25, 6); cout << "--------�¼������ϱ�--------" << endl;
	seat();
	char key;
	int x = 31, y = 8;
	do{
		
		gotoXY(x, y);
		printf("��");
		if (getch() == '\r'){
			break;
		}
		else key = getch();
		gotoXY(x, y);
		printf("��");
		move_arrow_key(key, &x, &y, SXmax, SYmax, EXmax, EYmax);

	} while (key != 27);
	for (int i = 1; i < 29; i++){
		if (x==s[i].dx){
			if (y==s[i].dy){
				gotoxy(40, 20); cout << i << "�� �¼�";
			}
		}
	}
	/*	if (flag = 1){
	cout << "";
	}
	else if (flag = 0){
	cout << "��";
	}*/return x;

}

//�ȵǴ°�
//1. ����Ű�� ������ �ڸ��� ������ �೪ �޸� ǥ���Ѵ�
//2. enter�� ������ ��� �ް� �ٲ�� ---------->�ذ�
//3. �ڸ����� ���ڸ� �ο��ؾ� �Ѵ�  ------------->�ذ�(����ü�� x�� y ��ǥ���� ��)
//4. �¼������� �Ϸ�Ǹ� ���� �������� �Ѿ�� �Ѵ�.
//5. ���� �κп� �డ ����Ǽ��� �ȵȴ�.