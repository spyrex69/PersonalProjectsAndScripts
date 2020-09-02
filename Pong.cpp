// Pong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<time.h>
#include<conio.h>
#include <Windows.h>
using namespace std;
enum Dir{STOP=0,LEFT=1,UPLEFT=2,DOWNLEFT=3,RIGHT=4,UPRIGHT=5,DOWNRIGHT=6};
class cBall {
private:
	int x, y;
	int originalX, originalY;
	Dir direction;
public:
	cBall(int posX, int posY) {
		originalX = posX;
		originalY = posY;
		x=posX; y= posY;
		direction = STOP;
	}
	void Reset() {
		x = originalX; y = originalY;
		direction = STOP;

	}
	void ChangeDirection(Dir D) {
		direction = D;
	}
	void RandomDirection() {
		direction = (Dir)((rand() % 6) + 1);
	}
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline Dir getDirection() { return direction; }
	void Move() {
		switch (direction) {
		case STOP:
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UPLEFT:
			x--; y--;
			break;
		case UPRIGHT:
			x++; y--;
			break;
		case DOWNLEFT:
			x--; y++;
			break;
		case DOWNRIGHT:
			x++; y++;
			break;
		default:
			break;
	}
	}
	friend ostream & operator<<(ostream & o, cBall c) {
		o << "Ball[" << c.x << "," << c.y << "]" << "[" << c.direction << "]";
		return o;
	}
};
class cPaddle {
private:
	int x, y;
	int originalX, originalY;
public:
	cPaddle() {
		x = 0; y = 0;
	}
	cPaddle(int posX, int posY) :cPaddle() {
		originalX = posX;
		originalY = posY;
		x = posX; y = posY;
	}
	void Reset() { x = originalX; y = originalY; }
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline void moveUp() { y-=4; }
	inline void moveDown() { y+=4;	}
	friend ostream& operator<<(ostream& o, cPaddle c) {
		o << "Player[" << c.x << "," << c.y <<"]";
		return o;
	}
};
class GameManager {
private:
	int width, height;
	int score1, score2;
	char up1, up2, down1, down2;
	bool quit;
	cBall* ball;
	cPaddle* player1;
	cPaddle* player2;
public:
	GameManager(int w, int h) {
		srand(time(NULL));
		width = w; height = h;
		up1 = 'w'; up2 = 'i'; down1 = 's'; down2 = 'k';
		quit = false;
		score1 = 0; score2 = 0;
		ball = new cBall(w/2, h/2);
		player1 = new cPaddle(2, h/2 - 3);
		player2 = new cPaddle(w - 3, h / 2);
	}
	~GameManager() {
		delete ball, player1, player2;
	}
	void ScoreUp(cPaddle* player) {
		if (player == player1)
			score1++;
		else if (player == player2)
			score2++;
		ball->Reset();
		player1->Reset();
		player2->Reset();
	}
	void Draw() {
		COORD coord;
		coord.Y = 0;
		coord.X = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		for (int i = 0; i < width; i++)
			cout << "\xB2";
		cout << endl;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int ballx = ball->getX();
			    int bally = ball->getY();
				int player1x = player1->getX();
				int player1y = player1->getY();
				int player2x = player2->getX();
				int player2y = player2->getY();
				if (j == 0)
					cout << "\xB2";
				else if (j == width - 1)
					cout << "\xB2";
				else if (ballx == j && bally == i)
					cout << "O";//BALL
				else if (player1x == j && player1y == i)
					cout << "\xDB";//PLAYER1 first segment
				else if (player2x == j && player2y == i)
					cout << "\xDB";//PLAYER2 first segment

				else if (player1x == j && player1y+1 == i)
					cout << "\xDB";//PLAYER1 second segment
				else if (player1x == j && player1y+2 == i)
					cout << "\xDB";//PLAYER1 third segment
				else if (player1x == j && player1y+3 == i)
					cout << "\xDB";//PLAYER1 fourth segment

				else if (player2x == j && player2y+1 == i)
					cout << "\xDB";//PLAYER2 second segment
				else if (player2x == j && player2y+2 == i)
					cout << "\xDB";//PLAYER2 third segment
				else if (player2x == j && player2y+3 == i)
					cout << "\xDB";//PLAYER2  fourth segment
				else
					cout << " ";
			}
			cout << endl;
		}
		for (int i = 0; i < width; i++)
			cout << "\xB2";
		cout << endl;

	}
	void Input() {

		ball->Move();
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();
		if (_kbhit())
		{
			char current = _getch();
			if (current == up1)
				if (player1y > 0)
					player1->moveUp();
			if (current == up2)
				if (player2y > 0)
					player2->moveUp();
			if (current == down1)
				if (player1y + 4 < height)
					player1->moveDown();
			if (current == down2)
				if (player2y + 4 < height)
					player2->moveDown();
			if (ball->getDirection() == STOP)
				ball->RandomDirection();
			if (current == 'q')
				quit = true;

		}
	}
	void Logic() {
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();

		for (int i = 0; i < 4; i++) {
			if (ballx == player1x + 1)
				if (bally == player1y + i)
					ball->ChangeDirection((Dir)((rand() % 3) + 4));
		}
		for (int i = 0; i < 4; i++) {
				if (ballx == player2x - 1)
					if (bally == player2y + i)
						ball->ChangeDirection((Dir)((rand() % 3) + 1));
		}
		//Bottom wall
		if (bally == height - 1)
			ball->ChangeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
		//top wall
		if (bally == 0)
			ball->ChangeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
		//right wall
		if (ballx == width - 1)
			ScoreUp(player1);
		//left wall
		if (ballx == 0)
			ScoreUp(player2);
	}
	void Run() {
		while (!quit) {
			Draw();
			Input();
			Logic();
		}
	}
};
int main()
{
	GameManager c(40, 20);
	c.Run();
	return 0;
	 
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
