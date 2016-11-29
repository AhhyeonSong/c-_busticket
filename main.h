#include <iostream>
#include <cstring>
#include <iomanip>
#include <conio.h>
using namespace std;

class first{
	int choice;
public:
	int menu();
	int reservation();
	void setChoice(int);
	void gotoxy(int x, int y);
	int getChoice();
};

/*class reser{
	int choice;
public:
	
	void setChoice(int);
	int getChoice();
};*/