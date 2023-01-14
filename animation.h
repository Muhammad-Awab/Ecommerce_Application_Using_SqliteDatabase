
#include<iostream>
using namespace std;


COORD coord = { 0, 0 };
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
/////////////////////////////////////////////////////////////////////////////////
void animation()
{
	for (int i = 45; i >= 1; i--)
	{

		gotoxy(1, i);
		//clreol();
	}
	for (int i = 1; i <= 20; i++)
	{

		gotoxy(1, i);
	}
}

