// SnakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
bool Gameover;
const int width = 60;
const int height = 30;
int x, y, fruiteX, fruiteY, score;
int tailX[100]; int tailY[100];
int ntail;
enum Direction {STOP=0,LEFT,RIGHT,UP,DOWN};
Direction dir;
void Setup() {
	Gameover = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruiteX = rand() % width;
	fruiteY = rand() % height;
	score = 0;
}
void Draw() {
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "score:" << score << endl;
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "@";
			else if (i == fruiteY && j == fruiteX)
				printf("\x94");
			else {
				bool print = false;
				for (int k = 0; k < ntail; k++)
				{
					if (tailX[k] == j && tailY[k] == i) {
						cout << "O";
						print = true;
					}
				}
				if(!print)
				  cout << " ";
			}
				if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;

}
void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			Gameover = true;
			break;
		}
	}
}
void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i=1; i < ntail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > width || x<0 || y > height || y < 0) {
		Gameover =true;
	}
	for (int i = 0; i < ntail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			Gameover = true;
		}
	}

	if (x == fruiteX && y == fruiteY) {
		score += 10;
		fruiteX = rand() % width;
		fruiteY = rand() % height;
		ntail++;
	}
}
int main()
{
	Setup();
	while (!Gameover) {
		Draw();
		Input();
		Logic();
		//Sleep(0.00000000000001);
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
