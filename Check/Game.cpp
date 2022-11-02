#include "Game.h"

mutex MTX;
condition_variable CV;
string Level_4="", Dap_an[5] = {"1623","3579","2448","2003","9331"};
Point_b Toado[13] = { {100,18,0},{80,28,0},{71,12,1},{130,14,2},{155,32,3},{79,8,3},{134,7,4},{62,27,4},{88,24,5},{80,13,6},{60,26,7},{115,26,8},{97,30,9} };
int da_chon;

point random(short int character, Kieu Man[5], int soMan)
{
	point c;
	c.character = character;
	srand(time(NULL));
	c.x = rand() % (165 - 52 + 1) + 52;
	c.y = rand() % (38 - 7 + 1) + 7;
	for (int i = 0; i < Man[soMan].size(); ++i)
	{
		int x1 = Man[soMan][i].dau.x;
		int y1 = Man[soMan][i].dau.y;
		int x2 = Man[soMan][i].cuoi.x;
		int y2 = Man[soMan][i].cuoi.y;
		if (c.x >= x1 && c.x <= x2 && c.y >= y1 && c.y <= y2)
		{
			srand(time(NULL));
			c.x = rand() % (165 - 52 + 1) + 52;
			c.y = rand() % (38 - 7 + 1) + 7;
		}
	}
	return c;
}

bool Move(int& snakeLen, point direction, point pos_snake[], string snake, point food, bool Dung, bool Thoat, Kieu Man[5], int Level)
{
	bool eat = false;
	int tocdo = snakeLen - 8;
	if (Dung) return true;
	if (Thoat) return true;
	Sleep(200 - tocdo * 10);
	bool check = true;
	for (int i = 0; i < snakeLen; i++)
	{
		if (i == 0) {
			pos_snake[0].x0 = pos_snake[0].x;
			pos_snake[0].y0 = pos_snake[0].y;
			pos_snake[0].x += direction.x;
			pos_snake[0].y += direction.y;
			if (pos_snake[0].x <= 50 || pos_snake[0].x >= 165)
				check = false;
			if (pos_snake[0].y <= 6 || pos_snake[0].y >= 40)
				check = false;
			for (int j = 0; j < Man[Level].size(); ++j)
			{
				Line Tmp = Man[Level][j];

				if ((pos_snake[0].x >= Tmp.dau.x && pos_snake[0].x <= Tmp.cuoi.x) && (pos_snake[0].y >= Tmp.dau.y && pos_snake[0].y <= Tmp.cuoi.y))
					check = false;
			}
			if ((pos_snake[0].x == 50) && ((pos_snake[0].y == 20) || (pos_snake[0].y == 21)) && ((snakeLen - 8) % 4 == 0) && (snakeLen - 8 != 0))
				return true;
			
			if (Level != 3)
			{
				if (pos_snake[0].x == food.x && pos_snake[0].y == food.y)
				{
					snakeLen++;
					eat = true;
				}
			}
			else
			{
				for (int j = 0; j <= 12; ++j)
				{
					if (pos_snake[0].x == Toado[j].x && pos_snake[0].y == Toado[j].y && Toado[j].visit_1 == false)
					{
						Level_4 += char(Toado[j].so + 48);
						Toado[j].visit_1 = true;
						snakeLen++;
						eat = true;
					}
				}
			}
		}
		else
		{
			if (pos_snake[i].x == pos_snake[0].x && pos_snake[i].y == pos_snake[0].y)
			{
				check = false;
			}
			pos_snake[i].x0 = pos_snake[i].x;
			pos_snake[i].y0 = pos_snake[i].y;
			pos_snake[i].x = pos_snake[i - 1].x0;
			pos_snake[i].y = pos_snake[i - 1].y0;
		}
		GotoXY(pos_snake[i].x, pos_snake[i].y);
		cout << snake[i];
		if (i == snakeLen - 1 && !eat)
		{
			GotoXY(pos_snake[i].x0, pos_snake[i].y0);
			cout << ' ';
		}
	}
	if (Level == 3 && Level_4.length() >= 4)
	{
		if (Level_4 == Dap_an[da_chon] && check == true) check = true;
		else
		{
			check = false;
		}
	}
	return check;
}

void BarrelRun(const char* fname, int y)
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ifstream f;
	int pos_x = 163, pos_y = y, x_left = 52;
	int length;
	string s;
	int line = 0;
	for (int k = 0; k < 82; ++k)
	{
		line = 0;
		f.open(fname);
		while (!f.eof())
		{
			getline(f, s);
			if (pos_x >= x_left)
			{
				length = min(s.size(), abs(163 - pos_x));
				GotoXY(pos_x, y + line++);
				for (int i = 0; i < length; ++i)
					cout << s[i];
			}
			else
			{
				length = s.size() - x_left + pos_x;
				GotoXY(x_left, y + line++);
				for (int i = s.size() - 1 - length; i < s.size(); ++i)
					cout << s[i];
			}
		}
		f.close();
		Sleep(200);
		f.open(fname);
		line = 0;
		while (!f.eof())
		{
			getline(f, s);
			if (pos_x >= x_left)
			{
				length = min(s.size(), abs(163 - pos_x));
				GotoXY(pos_x, y + line++);
				for (int i = 0; i < length; ++i)
					cout << " ";
			}
			else
			{
				length = s.size() - x_left + pos_x;
				GotoXY(x_left, y + line++);
				for (int i = s.size() - 1 - length; i < s.size(); ++i)
					cout << " ";
			}
		}
		f.close();
		pos_x -= 2;
	}
}

void Game(Data& DuLieu, Data Lich_Su[10], Data HighScore[10], Kieu Man[5])
{
	if (DuLieu.Level == 4)
	{
		PlaySound(L"Xe_Lua.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
		BarrelRun("Win.txt", 18);
		Sleep(2000);


		Tomau(224, 51, 164, 7, 39);
		Khung_Lon();
		Khung_Nho();
		SetColor(9);
		GotoXY(70, 20);
		cout << "Please enter your name: ";
		// phan high score
		getline(cin, HighScore[5].TenNguoiChoi);
		HighScore[5].Score = 16;
		HighScore[5].Level = DuLieu.Level;
		time_t now = time(0);
		char* dt = ctime(&now);
		HighScore[5].Date = dt;
		Tomau(224, 51, 164, 7, 39);
		Tomau(224, 7, 49, 7, 39);

		return;
	}

	Khung_Lon();
	Khung_Nho();
	const string name = "Level" + to_string(DuLieu.Level + 1) + ".txt";
	SetColor(0);
	ghiFile(name, 67, 14);
	Sleep(1000);
	Tomau(224, 51, 164, 7, 39);
	Sleep(0);
	// Xuat man
	if (DuLieu.Level == 1)
	{



		// tren trai
		SetColor(0);
		GotoXY(83, 19);
		PrintLine(223, 223, 223, 18);
		for (int i = 14; i <= 18; ++i)
		{
			GotoXY(100, i);
			cout << char(222);
		}
		// duoi trai
		GotoXY(83, 22);
		PrintLine(220, 220, 220, 18);
		for (int i = 23; i <= 27; ++i)
		{
			GotoXY(100, i);
			cout << char(222);
		}
		// tren phai
		GotoXY(110, 19);
		PrintLine(223, 223, 223, 18);
		for (int i = 14; i <= 18; ++i)
		{
			GotoXY(110, i);
			cout << char(221);
		}
		// phai duoi
		GotoXY(110, 22);
		PrintLine(220, 220, 220, 18);
		for (int i = 23; i <= 27; ++i)
		{
			GotoXY(110, i);
			cout << char(221);
		}
	}
	if (DuLieu.Level == 2)
	{
		GotoXY(75, 6);
		cout << char(203);
		for (int i = 7; i <= 16; ++i)
		{
			GotoXY(75, i);
			cout << char(186);
		}
		GotoXY(145, 40);
		cout << char(202);
		for (int i = 30; i <= 39; ++i)
		{
			GotoXY(145, i);
			cout << char(186);
		}
		GotoXY(65, 30);
		Khung(12, 65, 67, 30, 32);

		GotoXY(85, 20);
		Khung(12, 85, 87, 20, 22);

		GotoXY(100, 27);
		Khung(12, 100, 102, 27, 29);

		GotoXY(117, 12);
		Khung(12, 117, 119, 12, 14);

		GotoXY(134, 20);
		Khung(12, 134, 136, 20, 22);

		GotoXY(153, 14);
		Khung(12, 153, 155, 14, 16);
	}
	if (DuLieu.Level == 3)
	{
		srand(time(NULL));
		da_chon = rand() % (4 - 0 + 1) + 0;
		const string name = "Cau" + to_string(da_chon + 1) + ".txt";
		ghiFile(name, 60, 10);
		for (int i = 0; i < 13; ++i)
		{
			Toado[i].visit_1 = false;
			Toado[i].visit_2 = false;
		}

		SetColor(12);
		GotoXY(92, 25);
		cout << "Press Enter to continue";
		SetColor(0);
		
		char str = tolower(_getch());
		while (str != 13)
		{
			str = tolower(_getch());
		}


		Tomau(224, 51, 164, 7, 39);

		Level_4 = "";
		SetColor(9);
		for (int i = 0; i <= 12; ++i)
		{
			GotoXY(Toado[i].x, Toado[i].y);
			cout << Toado[i].so;
		}
		SetColor(0);
		//cout << cauhoi[da_chon];

	}




	PlaySound(L"opening.wav", GetModuleHandle(NULL), SND_FILENAME);
	SetColor(9);
	int Score = DuLieu.Score;
	bool Dung = false, Thoat = false;
	char c, direct = 'w';
	int snakeLen = Score + 8;
	string snake = "2112703321127629211273062112773921127033211276292112730621127739";
	point direction;
	direction.x = 0;
	direction.y = -1;
	point pos_snake[100];
	point food = random(6, Man, DuLieu.Level);
	GotoXY(food.x, food.y);
	if (Score % 4 == 0 && (Score - DuLieu.Level * 4) == 4 || (DuLieu.Level == 3));
	else cout << char(food.character);
	GotoXY(25, 10);
	cout << "Score :" << Score << "  ";
	pos_snake[0].x = 60;
	pos_snake[0].y = 20;
	
	Pin(18, 25);
	bool key = false;
	while (Move(snakeLen, direction, pos_snake, snake, food, Dung, Thoat, Man, DuLieu.Level) && Thoat == false)
	{
		
		//if 4 cai la 4 man dua theo so diem
		//Sleep(200);
		//Sleep(0
		if (Score % 4 == 0 && Score == DuLieu.Level * 4)
		{
			key = true;
		}
		Thanh_diem(Score,key);



		if (Score % 4 == 0 && (Score - (DuLieu.Level + 1) * 4 >= 0) && Score != 0)
		{
			GotoXY(50, 20);
			cout << " ";
			//Sleep(200);
			GotoXY(50, 21);
			cout << " ";
			//Sleep(200);
			thread th1(Cua);
			th1.join();

			if ((pos_snake[0].x == 50) && ((pos_snake[0].y == 20) || (pos_snake[0].y == 21)))
			{
				vaoCong(pos_snake, snake, snakeLen, food, Man, DuLieu.Level);
				Tomau(224, 7, 49, 7, 39);
				SetColor(12);
				GotoXY(50, 20);
				cout << char(186);
				GotoXY(50, 21);
				cout << char(186);
				DuLieu.Score = Score;
				DuLieu.Level += 1;
				Tomau(224, 51, 164, 7, 39);
				Game(DuLieu, Lich_Su, HighScore, Man);

				Thoat = true;
			}
		}



		if (DuLieu.Level != 3)
		{
			if (food.x == pos_snake[0].x && food.y == pos_snake[0].y && Dung == false && Thoat == false)
			{
				++Score;
				key = false;
				GotoXY(25, 10);
				cout << "Score :" << Score << "  ";
				PlaySound(L"eatSound_2.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
				if (Score % 4 != 0) {
					food = random(6, Man, DuLieu.Level);
					GotoXY(food.x, food.y);
					cout << char(food.character);
				}
			}
		}
		else
		{
			for (int j = 0; j <= 12; ++j)
			{
				if (pos_snake[0].x == Toado[j].x && pos_snake[0].y == Toado[j].y && Toado[j].visit_2 == false)
				{
					++Score;
					Toado[j].visit_2 = true;
					key = false;
					GotoXY(25, 10);
					cout << "Score :" << Score << "  ";
					PlaySound(L"eatSound_2.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
				}
			}
		}
		if (_kbhit())
		{
			c = tolower(_getch());
			switch (c)
			{
			case 'a':
			{
				if (direct != 'd')
				{
					direction.x = -1;
					direction.y = 0;
					direct = 'a';
				}
			}break;
			case 'd':
			{
				if (direct != 'a')
				{
					direction.x = 1;
					direction.y = 0;
					direct = 'd';
				}
			}break;
			case 'w':
			{
				if (direct != 's')
				{
					direction.x = 0;
					direction.y = -1;
					direct = 'w';
				}
			}break;
			case 's':
			{
				if (direct != 'w')
				{
					direction.x = 0;
					direction.y = 1;
					direct = 's';
				}
			}break;
			case 'p':
			{
				Dung = true;
			}break;
			case 't':
			{
				Dung = false;
			}break;
			case 'l':
			{
				Tomau(224, 51, 164, 7, 39);
				GotoXY(70, 20);
				cout << "Nhap ten nguoi choi:";
				for (int i = 4; i >= 1; --i)
				{
					Lich_Su[i] = Lich_Su[i - 1];
				}
				getline(cin, Lich_Su[0].TenNguoiChoi);
				Lich_Su[0].Score = Score;
				Lich_Su[0].Level = DuLieu.Level;
				time_t now = time(0);
				char* dt = ctime(&now);
				Lich_Su[0].Date = dt;
				//
				luuFile("Game0.txt", Lich_Su[0]);
				luuFile("Game1.txt", Lich_Su[1]);
				luuFile("Game2.txt", Lich_Su[2]);
				luuFile("Game3.txt", Lich_Su[3]);
				luuFile("Game4.txt", Lich_Su[4]);
				//
				Thoat = true;
				Tomau(224, 51, 164, 7, 39);
				Tomau(224, 7, 49, 7, 39);
			}break;
			}
		}
	}
	if (DuLieu.Level == 3 && Thoat == false && Level_4 != Dap_an[da_chon] && Level_4.length() >= 4)
	{
		GotoXY(92, 20);
		cout << "Wrong answer ";
		Sleep(1000);
	}
	GotoXY(pos_snake[0].x, pos_snake[0].y);
	cout << "x";
	PlaySound(L"Died.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);

	bool Check = true;
	if (Thoat == false)
	{
		GotoXY(85, 20);
		cout << "Dead, type y to continue or anykey to exit";
		char c = tolower(_getch());
		if (c == 'y')
		{
			Tomau(224, 51, 164, 7, 39);
			Khung_Nho();
			SetColor(9);
			Game(DuLieu, Lich_Su, HighScore, Man);
			Check = false;
		}
	}

	if (Thoat == false && Check == true)
	{

		GotoXY(70, 20);
		cout << "                            Game over                                ";
		Sleep(1000);

		Tomau(224, 51, 164, 7, 39);
		Khung_Nho();
		SetColor(9);
		GotoXY(70, 20);
		cout << "Please enter your name: ";
		// phan high score
		getline(cin, HighScore[5].TenNguoiChoi);
		HighScore[5].Score = Score;
		HighScore[5].Level = DuLieu.Level;
		time_t now = time(0);
		char* dt = ctime(&now);
		HighScore[5].Date = dt;
		Tomau(224, 51, 164, 7, 39);
		Tomau(224, 7, 49, 7, 39);
	}
	Tomau(224, 51, 164, 7, 39);
	Tomau(224, 7, 49, 7, 39);
}

void Cua()
{
	std::unique_lock<mutex> locker(MTX);
	SetColor(12);
	GotoXY(45, 19);
	cout << char(222) << char(220) << char(220) << char(220) << char(220);
	GotoXY(45, 20);
	cout << char(222) << char(22) << char(221);
	GotoXY(45, 21);
	cout << char(222) << char(22) << char(221);
	GotoXY(45, 22);
	cout << char(222) << char(223) << char(223) << char(223) << char(223);
	SetColor(9);
	locker.unlock();
	CV.notify_one();
}
void Thanh_diem(int n, bool check) {

	if (check) {
		n = 0;
	}

		if (n % 4 == 1) {
			Tomau_thanh_diem(12, 19, 36, 35, 37);
			BackgroundColor(224);
		}
		if (n % 4 == 2) {
			Tomau_thanh_diem(12, 19, 36, 35, 37);
			BackgroundColor(224);
			Tomau_thanh_diem(6, 19, 36, 32, 34);
			BackgroundColor(224);
		}
		if (n % 4 == 3) {
			Tomau_thanh_diem(12, 19, 36, 35, 37);
			BackgroundColor(224);
			Tomau_thanh_diem(6, 19, 36, 32, 34);
			BackgroundColor(224);
			Tomau_thanh_diem(10, 19, 36, 29, 31);
			BackgroundColor(224);

		}
		if (n % 4 == 0 && n != 0) {
			Tomau_thanh_diem(12, 19, 36, 35, 37);
			BackgroundColor(224);
			Tomau_thanh_diem(6, 19, 36, 32, 34);
			BackgroundColor(224);
			Tomau_thanh_diem(10, 19, 36, 29, 31);
			BackgroundColor(224);
			Tomau_thanh_diem(2, 19, 36, 26, 28);
			BackgroundColor(224);

		}
	
	SetColor(9);
}
void PrintLine(const char& leftMostChar, const char& middleChar, const char& rightMostChar, const int& length, const int& width ) {
	cout << leftMostChar;
	for (int i = 1; i <= (length - 2) / width; ++i) {
		cout << setw(width) << middleChar;
	}
	cout << setw(width) << rightMostChar;
}

void Pin(int x, int y) {
	SetColor(8);
	GotoXY(x, y++);
	PrintLine(char(220), char(220), char(219), 10);
	PrintLine(char(219), char(220), char(220), 10);
	for (int i = 1; i <= 12; i++) {
		GotoXY(x, y++);
		PrintLine(char(219), ' ', char(219), 20);

	}
	GotoXY(x, y++);
	PrintLine(char(223), char(223), char(223), 20);
	SetColor(9);
	
}
void vaoCong(point pos_snake[100], string snake, int snakeLen, point food, Kieu Man[5], int Level)
{

	point direction;
	direction.x = -1;
	direction.y = 0;
	deque<char> s;
	int tocDo = 200 - (snakeLen - 8) * 10;
	for (int i = 0; i < 2; ++i)
	{
		Move(snakeLen, direction, pos_snake, snake, food, false, false, Man, Level);
	}
	for (int i = 0; i < snakeLen; ++i)
	{
		s.push_back(snake[i]);
	}
	while (!s.empty())
	{
		for (int i = 0; i < s.size(); ++i)
		{
			GotoXY(pos_snake[i].x, pos_snake[i].y);
			cout << s[i];
		}
		Sleep(tocDo);

		GotoXY(pos_snake[s.size() - 1].x, pos_snake[s.size() - 1].y);
		cout << "  ";
		GotoXY(pos_snake[s.size() - 1].x0, pos_snake[s.size() - 1].y0);
		cout << "  ";
		s.pop_front();
	}
}

