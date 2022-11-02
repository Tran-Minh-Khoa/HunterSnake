#ifndef _ENTITY_
#define _ENTITY_
#pragma once
#include "lib.h"
using namespace std;
using namespace std::chrono;


/* utility */
void print(string s, const short& sleepTime = 20);
void HorizontalDraw(const short& x, const short& y, short* ltr);
void CheckTimeOver();
bool CheckTwopoint_1sOverlap(const point_1& p1, const point_1& p2);

struct snake {
	point_1 pos; // toa do cua ran
	char appearance;// hinh anh cua ran
};
typedef vector<snake> Snake;
struct fruit {
	point_1 pos;
	short shape;
};
class Data_1 {
private:
	enum ltr :char {
		TOP_LEFT = char(214),
		TOP_RIGHT = char(183),
		BOT_RIGHT = char(189),
		BOT_LEFT = char(211),
		VERTICAL_BAR = char(186),
		CROSSBAR = char(196),
	};
	void SetupTime(const short& time) {
		WordColor(Word::GREEN);

		string s = "Time: ";
		gotoXY((posOfTime.x - (short)s.length()), posOfTime.y);

		if (time > 0) {
			cout << s << time;
		}
		else {
			cout << s << INF;
		}
	}
	void SetupScore(const short& score) {
		WordColor(Word::LIGHT_BLUE);

		string s = "Score: ";
		gotoXY((posOfScore.x - (short)s.length()), posOfScore.y);

		cout << s << score;
	}
	short width = GetWidth(pos::START_X, pos::END_X);
	point_1 posOfTime{ START_X + width / 2,START_Y + 2 };
	point_1 posOfScore{ posOfTime.x, posOfTime.y + 2 };
protected:
	enum pos :short {
		START_X = 6,
		END_X = 30,
		START_Y = (short)Console::HEIGHT - 7,
		END_Y = (short)Console::HEIGHT - 1,
	};
public:
	virtual void DrawFrame() {
		WordColor(Word::BLACK);
		short i;
		for (i = START_Y; i <= END_Y; i++) {
			gotoXY(START_X, i);

			if (i == START_Y) {
				PrintLine(TOP_LEFT, CROSSBAR, TOP_RIGHT, width);
			}
			else if (i == END_Y) {
				PrintLine(BOT_LEFT, CROSSBAR, BOT_RIGHT, width);
			}
			else {
				PrintChar(START_X, i, VERTICAL_BAR);
				PrintChar(END_X, i, VERTICAL_BAR);
			}
		}
	}
	virtual void SetupData_1(const short& time = -1, const short& score = INITIAL_SCORE) {
		SetupTime(time);
		SetupScore(score);
	}

	friend void ShowTime(Data_1* dt);
	friend void ShowScore(Data_1* dt);
};
class Announce : public Data_1 {
private:
	enum ltr : char {
		TOP_LEFT = char(213),
		TOP_RIGHT = char(184),
		BOT_RIGHT = char(190),
		BOT_LEFT = char(212),
		VERTICAL_BAR = char(179),
		CROSSBAR = char(205),
	};
	short width = GetWidth(pos::START_X, pos::END_X);
	point_1 posOfAnnounce{ START_X + 2,START_Y + 1 };

	// Cac dong thong bao xuat ra console screen
	string play{ "Playing..." };
	string pause{ "Pausing..." };
	string caution[3]{
		"Avoid hitting the wall and your body.",
		"Be careful! Many walls have appeared.",
		"" };
	string levelInfo[3]{
		"Challenge 1: Eat 4 fruits in 20 seconds.",
		"Challenge 2: Eat 6 fruits in 60 seconds.",
		"" };

	void EraseFrame() {
		short i;
		for (i = START_Y + 1; i <= END_Y - 1; i++) {
			// xoa cac ky tu o giua (ngoai tru frame)
			BackSpace(START_X + 1, i, width - 2);
		}
	}
protected:
	enum pos :short {
		START_X = Data_1::END_X + GAP,
		END_X = (short)Console::WIDTH - Data_1::START_X,
		START_Y = Data_1::START_Y,
		END_Y = Data_1::END_Y,
	};
public:
	virtual void DrawFrame() {
		WordColor(Word::GRAY);
		short i;
		for (i = START_Y; i <= END_Y; i++) {
			gotoXY(START_X, i);

			if (i == START_Y) {
				PrintLine(TOP_LEFT, CROSSBAR, TOP_RIGHT, width);
			}
			else if (i == END_Y) {
				PrintLine(BOT_LEFT, CROSSBAR, BOT_RIGHT, width);
			}
			else {
				PrintChar(START_X, i, VERTICAL_BAR);
				PrintChar(END_X, i, VERTICAL_BAR);
			}
		}
	}

	void Play() {
		// Xoa du lieu cu
		EraseFrame();

		// Xuat du lieu moi
		gotoXY(posOfAnnounce);
		print(play,15);
	}
	void Pause() {
		// Xoa du lieu cu
		EraseFrame();

		// Xuat du lieu moi
		gotoXY(posOfAnnounce);
		print(pause);
	}
	void LevelInfo(const short& level) {
		if (level < MAX_LEVEL) {
			PlaySound(L"typing_1.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
			EraseFrame();

			// Xuat thong bao
			gotoXY(posOfAnnounce);
			print(caution[level - 1], 15);

			// Xuat thong tin man choi
			Sleep(240);
			gotoXY(posOfAnnounce.x, posOfAnnounce.y + 1);
			print(levelInfo[level - 1], 19);

			Sleep(610);
			Play();
		}
	}
	void NextLevel() {
		PlaySound(L"typing_1.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
		// Xoa du lieu cu
		EraseFrame();

		this_thread::sleep_for(microseconds(1));
		// Xuat du lieu moi
		gotoXY(posOfAnnounce);
		print("Well done!");

		Sleep(400);
		gotoXY(posOfAnnounce.x, posOfAnnounce.y + 1);
		print("The gate is open! Now come to the next level.");

		Sleep(390);
		Play();
	}
	void FinishChal() {
		PlaySound(L"typing_1.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
		// Xoa du lieu cu
		EraseFrame();

		Sleep(210);
		// Xuat du lieu moi
		gotoXY(posOfAnnounce);
		print("Congratulations! You did great.",19);

		Sleep(500);
		gotoXY(posOfAnnounce.x, posOfAnnounce.y + 1);
		print("Now finish this mini chanllenge.",19);
		Sleep(920);
	}
};
class PlayFrame: public Announce {
private:
	enum ltr : char {
		BOT = char(223),
		TOP = char(220),
		VERTICAL_BAR = char(219),
	};
	short height = GetWidth(pos::START_Y, pos::END_Y);
	short width = GetWidth(pos::START_X, pos::END_X);
	void DrawAtBasicLevel() {
		WordColor(Word::GRAY);
		short i;
		for (i = START_Y; i <= END_Y; i++) {
			gotoXY(START_X, i);

			if (i == START_Y) {
				PrintLine(TOP, width);
			}
			else if (i == END_Y) {
				PrintLine(BOT, width);
			}
			else {
				PrintChar(START_X, i, VERTICAL_BAR);
				PrintChar(END_X, i, VERTICAL_BAR);
			}
		}
	}
	void DrawAtLevel_2() {
		short i(-1), x(-1), y(-1);
		/* Goc trai */
		/************************************
				 (16,5)*****(29,5)
						*****
					 (28,7)**
						  **(29,12)
		************************************/
		{
			WordColor(Word::LIGHT_PURPLE);
			// 2 dong dau
			x = 16, y = 5;
			gotoXY(x, y); PrintLine(TOP, 14);

			y++;
			gotoXY(x, y); PrintLine(VERTICAL_BAR, 14);

			// cac dong giua
			x += 12, y++;
			for (i = 0; i < 5; i++) {
				gotoXY(x, y + i);
				PrintLine(VERTICAL_BAR, 2);
			}

			// dong cuoi
			gotoXY(x, y + i); PrintLine(BOT, 2);
		}

		/************************************

				 (16,23)**
						**(17,28)
						******
						******(29,30)
		************************************/
		{
			WordColor(Word::LIGHT_PURPLE);
			// Dong dau
			x = 16, y = 23;
			gotoXY(x, y); PrintLine(TOP, 2);

			// cac dong giua
			y++;
			for (i = 0; i < 5; i++) {
				gotoXY(x, y + i);
				PrintLine(VERTICAL_BAR, 2);
			}

			// 2 dong cuoi
			y = 29;
			gotoXY(x, y); PrintLine(VERTICAL_BAR, 14);
			gotoXY(x, y + 1); PrintLine(BOT, 14);
		}

		/* Goc giua */
		/**************************************************
				 (71,7)*******	 density/tur: 2, width: 34, height: 32/2 = 16
					 * * * *	 total width = 34 + 34 / 2 = 51
					 * * * *	 thanh ngang: 34-2*2 = 30 => 14 khoang trang
			 (55,28)*******
		***************************************************/
		{
			WordColor(Word::LIGHT_RED);
			// dong tren cung
			x = 71, y = 7;
			gotoXY(x, y); PrintLine(VERTICAL_BAR, 34);

			// cot 2,4
			y++;
			for (i = 0; i < 15; i++) {
				gotoXY(x, y + i); PrintLine(VERTICAL_BAR, 2);
				gotoXY(x + 32, y + i); PrintLine(VERTICAL_BAR, 2);
			}

			WordColor(Word::LIGHT_BLUE);
			// dong duoi cung
			x = 55, y = 28;
			gotoXY(x, y); PrintLine(VERTICAL_BAR, 34);
			// cot 1,3
			y--;
			for (i = 0; i < 15; i++) {
				gotoXY(x, y - i); PrintLine(VERTICAL_BAR, 2);
				gotoXY(x + 32, y - i); PrintLine(VERTICAL_BAR, 2);
			}
		}

		/* Goc phai */
		/**************************************************
			Goc phai	*		  *
						*		  *
						*		  *
		width = 36		*		  *
						*		  *
								  *
								  *
							 *  *
							 *
							 *		  *
							 *		  *
							 *		  *
							 *		  *
							 *		  *
		***************************************************/
		{
			WordColor(Word::GREEN);
			x = PlayFrame::END_X - 36;
			y = PlayFrame::START_Y + 1;
			// Cot 1
			for (i = 0; i < (height * 2 / 3) - 2; i++) {
				gotoXY(x, y + i);
				cout << VERTICAL_BAR;
			}
			// Cot 3
			x += 18;//36/2
			for (i = 0; i < (height * 3 / 4) - 2; i++) {
				gotoXY(x, y + i);
				cout << VERTICAL_BAR;
			}
			// Cot 2
			x = PlayFrame::END_X - 27;//36*3/4
			y = PlayFrame::END_Y - 1;
			for (i = 0; i < (height * 3 / 4) - 1; i++) {
				gotoXY(x, y - i);
				cout << VERTICAL_BAR;
			}
			// Cot 4
			x += 18;
			for (i = 0; i < (height * 2 / 3) - 1; i++) {
				gotoXY(x, y - i);
				cout << VERTICAL_BAR;
			}
		}
	}
protected:
	enum pos : short {
		START_X = Data_1::START_X,
		END_X = Announce::END_X,
		START_Y = 2,
		END_Y = (short)Console::HEIGHT - (Data_1::END_Y - Data_1::START_Y) - GAP,
	};
public:
	virtual void DrawFrame(const short& LEVEL) {
		// Ve vien mac dinh
		DrawAtBasicLevel();

		/* Ve them chuong ngai vat */
		if (LEVEL > 1) {
			switch (LEVEL)
			{
			case 2: {
				DrawAtLevel_2();
			} break;

			}
		}
	}
};
class WALL : protected PlayFrame {
public:
	point_1 startCoord{ PlayFrame::START_X,PlayFrame::START_Y };
	point_1 endCoord{ PlayFrame::END_X + 1,PlayFrame::END_Y + 1 };
	point_1 center = Centerpoint_1(startCoord, endCoord);
	bool** frame = NULL;
};

/* Nhom ham xu ly ran */
void HandleMovingSnakeInput(const Direction& dir, Moving& check);
void HandleSnake(Snake& snake, fruit& fr, WALL& wall);
void FindHeadPos(const Moving& check);
bool CheckGameOver(const Snake& snake, WALL& wall);

/* tinh nang game */
void PauseThread(Direction&);
void LevelUp(Snake& snake, WALL& wall, fruit& fr);
void EndGame(WALL& wall, Snake& snake, fruit& fr);
void WinGame(WALL& wall);
void init(WALL& wall, Snake& snake, fruit& fr);//
void OpenGate(WALL& wall);

/* Nhom ham xu ly hau thuc thi */
void ResetData_1(WALL& wall, Snake& snk);

int MiniGame();

#endif // !_ENTITY_