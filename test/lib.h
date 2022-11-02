#ifndef _LIB_
#define _LIB_

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <cmath>
#include <conio.h>
#include <iomanip>
#include <ctime>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <deque>
#include <algorithm>
#include <MLOperatorAuthor.h>
#include <list>
#include <fstream>
#define UNDEFINED -1
#define ORIGINAL_SIZE 10
#define MAX_LENGTH_SNAKE 64
#define SLEEP_TIME 5000
#define SCORE_AT_LEVEL_1 4
#define SCORE_AT_LEVEL_2 6
#define TIME_AT_LEVEL_1 20
#define TIME_AT_LEVEL_2 60
#define SPD_AT_LEVEL_1 200
#define SPD_AT_LEVEL_2 100
#define TERMINAL_SPD 200
#define INITIAL_TIME_LEFT 60
#define INITIAL_SCORE 0
#define INITIAL_LEVEL 1
#define MAX_LEVEL 3
#define SPACE ' '
#define GAP 3
#define INF char(236)
#define UP_LEVEL 1
enum class Moving : WORD {
	DOWN = 0,
	UP,
	RIGHT,
	LEFT,
};
enum class Direction :char {
	DOWN = 'S',
	UP = 'W',
	RIGHT = 'D',
	LEFT = 'A',
	PAUSE = 'P',
	LOAD = 'T',
};
enum class Background : WORD {
	BLACK = 0,
	BLUE = 16,
	GREEN = 32,
	AQUA = 48,
	RED = 64,
	PURPLE = 80,
	YELLOW = 96,
	WHITE = 112,
	GRAY = 128,
	LIGHT_BLUE = 144,
	LIGHT_GREEN = 160,
	LIGHT_AQUA = 176,
	LIGHT_RED = 192,
	LIGHT_PURPLE = 208,
	LIGHT_YELLOW = 224,
	BRIGHT_WHITE = 240,
};
enum class Word : WORD {
	BLACK = 0,
	BLUE,
	GREEN,
	AQUA,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_AQUA,
	LIGHT_RED,
	LIGHT_PURPLE,
	LIGHT_YELLOW,
	BRIGHT_WHITE,
};
enum class Console : WORD {
	WIDTH = 171, // from (0,y) to (171,y)
	HEIGHT = 42, // from (x,0) to (x,42)
};
struct point_1 {
	short x;// hoanh do
	short y;// tung do

	// copy assignment
	point_1& operator =(const point_1& other) {
		// Guard self assignment
		if (this == &other) {
			return *this;
		}
		// assign value of other to *this
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	point_1& operator +(const short& n) {
		this->x += n;
		this->y += n;
		return *this;
	}

	point_1& operator +(const point_1& other) {
		this->x += other.x;
		this->y += other.y;
		return *this;
	}
};

//======= lấy tọa độ x của con trỏ hiện tại =============
short whereX();
//========= lấy tọa độ y của con trỏ hiện tại =======
short whereY();
//============== dịch con trỏ hiện tại đến điểm có tọa độ (x,y) ==========
void gotoXY(const short& x, const short& y);
void gotoXY(const point_1&);
//============= đặt màu cho chữ =========
void WordColor(Word);
void ResetWordColor();
//============== làm ẩn trỏ chuột ===========
void ShowCur(bool CursorVisibility);
//======= trả về mã phím người dùng bấm =========
short inputKey();
// Chuyen mau nen man hinh console
void BackgroundColor(Background);
void ResetBGColor();
// Thay doi kich thuoc man hinh console
void resizeConsole(const short& width, const short& height);
// Co dinh man hinh console
void FixConsoleWindow();
// Dich chuyen man hinh console den toa do (x,y)
void MoveWindow(const short& posx, const short& posy);
// An thanh cuon chuot 
void HideScrollBar();
// Xoa du lieu cu
void BackSpace(const short& x, const short& y, const short& width = 1);
void BackSpace(const point_1& pos, const short& width = 1);

/* Nhom ham tien ich */
point_1 Centerpoint_1(const point_1& head, const point_1& tail);
short GetWidth(const short& start, const short& end);
void SetupConsoleScreen(); // dieu chinh ty le man hinh console
void PrintLine(const char& leftMostChar, const char& middleChar, const char& rightMostChar, const short& length, const short& width = 1);
void PrintLine(const char& Ch, const short& length, const short& width = 1);
void PrintChar(const short& x, const short& y, const char& Ch);
void readFile(const char* fname, short x, short y);
void ColoringBackGround();
void ClearScreen();	// Xoa man hinh

#endif // !_LIB_