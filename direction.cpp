#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define Xmax 79
#define Ymax 24
void move_arrow_key(char key, int *x, int *y, int x_b, int y_b){
	switch (key){
	case 72:
		*y = *y - 1;
		if (*y<1) *y = 1;
		break;
	case 75:
		*x = *x - 1;
		if (*x<1) *x = 1;
		break;
	case 77:
		(*x)++;
		if (*x>x_b) *x = x_b;
		break;
	case 80:
		(*y)++;
		if (*y>y_b) *y = y_b;
		break;
	default:
		return;
	}

}



void gotoxy(int x, int y){
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


int main(){
	char key;
	int x = 10, y = 5;
	do{
		gotoxy(x, y);
		printf("*");
		key = _getch();
		move_arrow_key(key, &x, &y, Xmax, Ymax);
	} while (key != 27);
}
