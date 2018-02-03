// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//
#include <iostream>
#include <conio.h>
#include <thread>
#include <Windows.h>
#include <vector>
#include <chrono>

class Point {
public:
	int x, y;
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	Point() {

	}
	~Point() {

	}
	void draw(char sign) {
		goToXY();
		std::cout << sign;
	}
	void goToXY() {
		COORD position;
		position.X = x;
		position.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	}
};
class Cursor {
public:
	int x = 0, y = 0;
	char symbol;
	bool trig = true;
	Cursor(int x, int y) {
		symbol = 'x';
		this->x = x;
		this->y = y;
	}
	BOOL setCursorToPosition(int x, int y) {
		COORD c;
		c.X = x;
		c.Y = y;
		return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	}
	bool isVirtualKeyPressed(int virtKey) {
		return GetAsyncKeyState(virtKey);
	}
	void move() {
		while (trig = true) {
			if (isVirtualKeyPressed(VK_LEFT)) --x;
			else if (isVirtualKeyPressed(VK_RIGHT)) ++x;
			else if (isVirtualKeyPressed(VK_UP)) --y;
			else if (isVirtualKeyPressed(VK_DOWN)) ++y;
			else if (isVirtualKeyPressed(VK_ESCAPE)) break;
			else if (isVirtualKeyPressed(VK_SPACE)) changeCursor(); trig = false;

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			setCursorToPosition (x, y);
			std::cout << symbol;
		}
	}


	void erase() {
		while (trig = true) {
			if (isVirtualKeyPressed(VK_LEFT)) --x;
			else if (isVirtualKeyPressed(VK_RIGHT)) ++x;
			else if (isVirtualKeyPressed(VK_UP)) --y;
			else if (isVirtualKeyPressed(VK_DOWN)) ++y;
			else if (isVirtualKeyPressed(VK_ESCAPE)) break;
			else if (isVirtualKeyPressed(VK_SPACE)) changeCursor(); trig = false;

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			setCursorToPosition(x,y);
			std::cout << ' ';
		}
	}

	void changeCursor() {
		char action = '~';
		COORD position = { 35, 0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		std::cout << "If you want to change symbol press 1 to erase press 2 " << std::endl;
		if (_kbhit()) {
			action = _getch();
		}
		switch (action) {
		case 1:
			std::cin >> symbol;
			move();
			break;
		case 2:
			erase();
			break;
		default:
			break;
		}
	}
};
class Wall {
public:
	Point *body;
	Wall() {
		body = new Point[120];
		for (int i = 0; i < 30; i++) {
			body[i] = *(new Point(i, 0));
			body[i + 30] = *(new Point(0, i));
			body[i + 60] = *(new Point(i, 29));
			body[i + 90] = *(new Point(29, i));
		}
	}
	~Wall() {
		delete[] body;
	}
	void draw() {
		for (int i = 0; i < 120; i++) {
			body[i].draw('#');
		}
	}
};

class Application {
public:
	Wall *wall;
	Cursor *cursor;
	Application() {
		wall = new Wall();
		cursor = new Cursor(5, 5);
	}
	~Application() {
		delete wall;
		delete cursor;
	}
	bool checkCursorInWall() {
		for (int i = 0; i < 120; i++) {
			if (cursor->x == wall->body[i].x && cursor->y == wall->body[i].y) {
				exit();
				return false;
			}
		}
		return true;
	}
	void exit() {
		system("cls");
	}
	void play() {
		char k = 'x';
		char e;
		std::cout << "Input R to draw E to erase" << std::endl;
		std::cin >> e;
		system("cls");
		wall->draw();
		switch (e) {
		case 'R':
			cursor->move();
		default:
			break;
		}
		checkCursorInWall();
	}
};
int main()
{
	Application *game = new Application;
	game->play();
	delete game;
	system("pause");
	return 0;
}

