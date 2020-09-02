// Pong2.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>
using namespace std;
enum dir{STOP=0,UPLEFT=1, UPRIGHT = 2, DOWNLEFT =3,DOWNRIGHT=4};//For direction
class cBall {
private:
	int x, y;
	int originalX, originalY;
	dir Direction;
public:
	cBall(int posX, int posY) {
		originalX = posX; originalY = posY;
		x = posX; y=posY;
		Direction = STOP;
	}
	void Reset() {
		x = originalX; y = originalY;
		Direction = STOP;
	}
	void ChangeDirection(dir D) {
		Direction = D;
	}
	//This function will randomize direction on starting point and the plus 1 is for avoiding the STOP condition
	void RandomizeDirection() {
		Direction = (dir)((rand() % 4) + 1);
	}
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline dir getDirection() { return Direction; }
	void Move() {
		switch (Direction) {
		case STOP:
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
	friend ostream& operator<<(ostream& o, cBall c) {
		o << "Ball[" << c.x << "," << c.y << "]" << "[" << c.Direction << "]";
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
		originalX = posX; originalY = posY;
		x = posX; y = posY;
	}
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline void moveLeft() { x=x-6; }
	inline void moveRight() { x=x+6; }
	void Reset() {
		x = originalX; y = originalY;
	}
	friend ostream& operator<<(ostream& o, cPaddle player) {
		o << "Palyer[" << player.x << "," << player.y << "]";
		return o;
	}
};
class GameManager {
private:
	int height, width;
	int score;
	char left, right;
	bool quite;
	cBall* ball;
	cPaddle* player;
public:
	GameManager(int w, int h) {
		srand(time(NULL));
		height = h;
		width = w;
		score = 10;
		left = 'a'; right = 'd';	
		quite = false;
	    ball = new cBall(w / 2,h/2);
		player = new cPaddle(w / 2, h - 2);
	}
	~GameManager() {
		delete ball, player;
	}
	void scoreDown() {
		score--;
		ball->Reset();
		player->Reset();
	}
	void Draw() {
		COORD coord;
		coord.Y = 0;
		coord.X = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		for (int i = 0; i <=width+1; i++) {
			if (i == width + 1) {
				cout << "Lives :" << score; continue;
			}
			cout << "\xB2";
		}
		cout << endl;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int ballx = ball->getX();
				int bally = ball->getY();
				int playerx = player->getX();
				int playery = player->getY();
				if (j == 0)
					cout << "\xB2";
				else if (j == width-1)
					cout << "\xB2";
				else if (ballx == j && bally == i)
					cout << "0";
				else if (playerx + 1 == j && playery == i)
					cout << "\xDC";
				else if (playerx + 2 == j && playery == i)
					cout << "\xDC";
				else if (playerx + 3 == j && playery == i)
					cout << "\xDC";
				else if (playerx + 4 == j && playery == i)
					cout << "\xDC";
				else
					cout << " ";
			}
			cout << endl;
		}
		for (int i = 0; i < width; i++)
			cout << "\xB2";
		cout << endl;
	}
	void input() {
		//Move function is here because whenever we give input it will execute the switch in move and perform one case depending updon the input
		//in the ball pointer will have Direction value and we are defferencing with '->'
		ball->Move();
		int ballx = ball->getX();
		int bally = ball->getY();
		int playerx = player->getX();
		int playery = player->getY();
		if (_kbhit()) {
			char current = _getch();
			//for avoiding player going into the left wall
			if (current == left)
				if (playerx> 0)
					player->moveLeft();
			//for avoiding player going into the right wall
			if (current == right)
				if (playerx + 4 < width-1)
					player->moveRight();
			if (ball->getDirection() == STOP)//On starting the ball will be STOP but when we press the key 
				ball->RandomizeDirection();// we will call the randomize fucntion
			if (current == 'q')
				quite=true;
		}
	}
	void Logic() {
		int ballx = ball->getX();
		int bally = ball->getY();
		int playerx = player->getX();
		int playery = player->getY();
		//player and ball colison logic. Limit is 4 because there are 4 segments of the player so it will handle cases
		//when ball colides with any of them
		for(int i=0;i<4;i++){ 
			if(bally==playery+1)
				if(ballx==playerx+i)
					ball->ChangeDirection((dir)((rand() % 2) + 1));
		}
		//left wall colision logic
		if (ballx == 1)
			ball->ChangeDirection(ball->getDirection() == UPLEFT ? UPRIGHT : DOWNRIGHT);
		//right wall colision logic
		if (ballx == width - 1)
			ball->ChangeDirection(ball->getDirection() == UPRIGHT ? UPLEFT : DOWNLEFT);
		//top wall colision logic
		if (bally == 0)
			ball->ChangeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
		//Bottom wall colision logic
		if (bally == height)
			scoreDown();
		if (score == 0)
			quite = true;
	}
	void Run() {

		while (!quite) {
			Draw();
			input();
			Logic();
		}
	}
};
int main()
{
	GameManager c(40, 20);
	c.Run();
	return 0;
	/*cBall ball(2,4);
	cPaddle player(5, 7);
	cout << ball << endl;
	cout << player << endl;
	ball.RandomizeDirection();
	ball.Move();
	player.moveLeft();
	cout << ball << endl;
	cout << player << endl;
	player.Reset();
	ball.Reset();
	ball.Move();
	cout << ball << endl;;
	cout << player << endl;*/
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
