#include "Menu.h"
#pragma comment(lib, "winmm.lib")

bool Cmp(Data a, Data b)
{
	if (a.Score > b.Score) return true;
	if (a.Score == b.Score && a.Level > b.Level) return true;
	return false;
}

void High_Score(Data HighScore[10])
{
	GotoXY(65, 10);
	cout << "TOP";
	GotoXY(83, 10);
	cout << "NAME";
	GotoXY(102, 10);
	cout << "SCORE";
	GotoXY(122, 10);
	cout << "LEVEL";
	GotoXY(142, 10);
	cout << "DATE";

	// ===================================
	
	sort(HighScore, HighScore + 6, Cmp);
	luuFile("1.txt", HighScore[0]);
	luuFile("2.txt", HighScore[1]);
	luuFile("3.txt", HighScore[2]);
	luuFile("4.txt", HighScore[3]);
	luuFile("5.txt", HighScore[4]);
	int vitri = 0;
	for (int i = 0; i <= 4; ++i)
	{
		GotoXY(65, 13 + vitri);
		cout << i + 1;
		GotoXY(83, 13 + vitri);
		cout << HighScore[i].TenNguoiChoi;
		GotoXY(102, 13 + vitri);
		cout << HighScore[i].Score;
		GotoXY(122, 13 + vitri);
		if (HighScore[i].Level + 1 == 5) cout << "Win";
		else cout << HighScore[i].Level + 1;
		GotoXY(135, 13 + vitri);
		cout << HighScore[i].Date;
		vitri += 2;
	}
}

void Xuat_Load_Game(Data Lich_Su[10])
{
	GotoXY(65, 10);
	cout << "TOP";
	GotoXY(83, 10);
	cout << "NAME";
	GotoXY(102, 10);
	cout << "SCORE";
	GotoXY(122, 10);
	cout << "LEVEL";
	GotoXY(142, 10);
	cout << "DATE";

	// ===================================
	int vitri = 0;
	for (int i = 0; i <= 4; ++i)
	{
		GotoXY(65, 13 + vitri);
		cout << i + 1;
		GotoXY(83, 13 + vitri);
		cout << Lich_Su[i].TenNguoiChoi;
		GotoXY(102, 13 + vitri);
		cout << Lich_Su[i].Score;
		GotoXY(122, 13 + vitri);
		cout << Lich_Su[i].Level + 1;
		GotoXY(135, 13 + vitri);
		cout << Lich_Su[i].Date;
		vitri += 2;
	}
}

void Di_Chuyen_Load_Game(int load_i, int load_i_cu, Data Lich_Su[10]) // code dich thang sang chon game load 
{
	// khoi tao lai thanh cu
	Tomau(224, 63, 160, 13 + load_i_cu * 2, 13 + load_i_cu * 2);
	GotoXY(65, 13 + load_i_cu * 2);
	cout << load_i_cu + 1;
	GotoXY(83, 13 + load_i_cu * 2);
	cout << Lich_Su[load_i_cu].TenNguoiChoi;
	GotoXY(102, 13 + load_i_cu * 2);
	cout << Lich_Su[load_i_cu].Score;
	GotoXY(122, 13 + load_i_cu * 2);
	cout << Lich_Su[load_i_cu].Level + 1;
	GotoXY(135, 13 + load_i_cu * 2);
	cout << Lich_Su[load_i_cu].Date;

	// sang thanh moi
	GotoXY(60, 13 + load_i * 2);
	Tomau(240, 63, 160, 13 + load_i * 2, 13 + load_i * 2);
	GotoXY(60, 13 + load_i * 2);
	//
	GotoXY(65, 13 + load_i * 2);
	cout << load_i + 1;
	GotoXY(83, 13 + load_i * 2);
	cout << Lich_Su[load_i].TenNguoiChoi;
	GotoXY(102, 13 + load_i * 2);
	cout << Lich_Su[load_i].Score;
	GotoXY(122, 13 + load_i * 2);
	cout << Lich_Su[load_i].Level + 1;
	GotoXY(135, 13 + load_i * 2);
	cout << Lich_Su[load_i].Date;
	//
	BackgroundColor(224);

}

void Menu_dongs(string menu[], int menu_i)
{
	string s;
	int i = 0;
	SetColor(12);
	ghiFile("Snake.txt", 10, 10);
	SetColor(8);
	GotoXY(20, 22);
	cout << menu[(menu_i + 5) % 6];
	GotoXY(20, 24);
	cout << menu[(menu_i + 7) % 6];
	SetColor(12);
	GotoXY(20, 23);
	cout << menu[menu_i];
}

void Play(int x, Data Lich_Su[10], Data HighScore[10], int load_i, int load_i_cu, bool phai, char c)
{
	switch (x)
	{
	case 0: // start game
	{
		Tomau(224, 51, 164, 7, 39);
		SetColor(9);
		ghiFile("Start.txt", 90, 15);
		while (!_kbhit())
		{
			Sleep(300);
			GotoXY(98, 23);
			cout << "                     ";
			Sleep(200);
			GotoXY(98, 23);
			cout << "PRESS ENTER TO START!";
		}
		SetColor(0);
	}break;
	case 1: // load game
	{
		if (phai == false)
		{
			Tomau(224, 51, 164, 7, 39); // xoa man hinh
			Xuat_Load_Game(Lich_Su);
		}
		if (phai == true) Di_Chuyen_Load_Game(load_i, load_i_cu, Lich_Su);
	}break;
	case 2: // High score
	{
		if (c == 'w' || c == 's')
		{
			Tomau(224, 51, 164, 7, 39);
			High_Score(HighScore);
		}
	}break;
	case 3:
	{
		if (c == 'w' || c == 's')
		{
			Tomau(224, 51, 164, 7, 39);
			SetColor(0);
			ghiFile("Danh_Sach.txt", 52, 10);
		}
	}break;
	case 4:
	{
		if (c == 'w' || c == 's')
		{
			Tomau(224, 51, 164, 7, 39);
			SetColor(12);
			GotoXY(95, 20);
			cout << "    WANNA NEW CHALLENGE?   ";
		}
	}break;
	case 5:
	{
		if (c == 'w' || c == 's')
		{
			Tomau(224, 51, 164, 7, 39);
			GotoXY(95, 20);
			SetColor(12);
			cout << "PRESS ENTER TO QUIT THE GAME";
		}
	}break;
	/*default:
	{
		GotoXY(98, 23);
		SetColor(9);
		cout << "Nothing here         ";
	}break;*/
	}
}

void control_func(Data HighScore[10], Data Lich_Su[10], Kieu Man[5])
{
	Data DuLieu;
	bool phai = false;
	int menu_i = 0, load_i = 0, load_i_cu = 0;
	bool Enter = false;
	string Danh_sach_MN[6] = { "   PLAY GAME ","   LOAD GAME  ","   HIGHSCORE  "," INTRODUCTIONS ", "   MINI GAME   ","   QUIT GAME  " };
	Menu_dongs(Danh_sach_MN, menu_i);
	Play(menu_i, Lich_Su, HighScore, load_i, load_i_cu, phai, 'w');
	while (!Enter)
	{
		if (_kbhit())
		{
			char c = tolower(_getch());
			if (c != 'w' && c != 'a' && c != 's' && c != 'd' && c != 13) continue;
			if (menu_i == 0 && c == 13) // neu menu_i = 0 va c la enter thi chay ham game()
			{
				Tomau(224, 51, 164, 7, 39);
				Tomau(224, 7, 49, 7, 39);
				// Chay ham game()
				Game(DuLieu, Lich_Su, HighScore, Man);
				// Quay lai
				Khung_Nho();
				menu_i = 0;
				load_i = 0;
				load_i_cu = 0;
				phai = false;
				Menu_dongs(Danh_sach_MN, menu_i);
				Play(menu_i, Lich_Su, HighScore, load_i, load_i_cu, phai, 'w');
			}
			if (menu_i == 1 && c == 13 && phai) // menu_i = 1, con tro dang ben phai va c la enter chay ham vao game()
			{
				Tomau(224, 51, 164, 7, 39);
				Tomau(224, 7, 49, 7, 39);
				// Chay ham game()
				DuLieu = Lich_Su[load_i];
				Game(DuLieu, Lich_Su, HighScore, Man);
				// Quay lai
				Khung_Nho();
				menu_i = 1;
				load_i = 0;
				load_i_cu = 0;
				phai = false;
				Menu_dongs(Danh_sach_MN, menu_i);
				Play(menu_i, Lich_Su, HighScore, load_i, load_i_cu, phai, 'w');
			}
			if (menu_i == 4 && c == 13)
			{
				keoRem();
				MiniGame();
				Sleep(1000);
				ClearScreen();
				SetConsoleTitle(L"Hunting Snake");
				Khung_Lon();
				Khung_Nho();
				Menu_dongs(Danh_sach_MN, menu_i);
				Play(menu_i, Lich_Su, HighScore, load_i, load_i_cu, phai, 'w');
			}
			if (menu_i == 5 && c == 13 && !phai) // thoat khoi game
			{
				Tomau(224, 2, 169, 1, 41);

				SetColor(12);
				ghiFile("Thanks.txt", 30, 10);
				Sleep(200);

				SetColor(10);
				ghiFile("Thanks.txt", 30, 10);
				Sleep(200);

				SetColor(12);
				ghiFile("Thanks.txt", 30, 10);
				Sleep(200);

				SetColor(9);
				ghiFile("Thanks.txt", 30, 10);
				Sleep(200);

				SetColor(12);
				ghiFile("Thanks.txt", 30, 10);

				Sleep(500);
				PlaySound(L"Bye_Bye.wav", GetModuleHandle(NULL), SND_FILENAME);
				GotoXY(2, 41);
				break;
			}
			if (!phai) //neu dang o ben trai thi nhan cac phim 'w' 's' de dieu khien
			{
				if (c == 'w')
				{
					menu_i = (menu_i + 5) % 6;
				}
				else if (c == 's')
				{
					menu_i = (menu_i + 7) % 6;
				}
				else if (c == 'd' && menu_i == 1)
				{
					phai = true;
				}
			}
			if (phai) //neu dang o ben phai thi nhan cac phim 'w' 's' de dieu khien
			{
				if (c == 'w')
				{
					load_i_cu = load_i;
					load_i = (load_i + 5) % 6;
				}
				else if (c == 's')
				{
					load_i_cu = load_i;
					load_i = (load_i + 7) % 6;
				}
				else if (c == 'a') // nhay qua trai
				{
					phai = false;
				}
			}
			Menu_dongs(Danh_sach_MN, menu_i);
			Play(menu_i, Lich_Su, HighScore, load_i, load_i_cu, phai, c);
		}
	}
}

void keoRem()
{
	string TAB = "                   ";
	const int block = 10;
	for (int i = 0; i <= block; ++i)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j <= 42; ++j)
			{
				BackgroundColor(0);
				GotoXY(19 * i, j);
				if (i <= 8)
				{
					if (i == block - 2) cout << TAB << " ";
					else cout << TAB;
				}
				if (i >= 2)
				{
					BackgroundColor(224);
					GotoXY(19 * (i - 2), 42 - j);
					if (i == block) cout << TAB << " ";
					else cout << TAB;
				}
				this_thread::sleep_for(chrono::microseconds(4));
			}
		}
		else
		{
			for (int j = 42; j >= 0; --j)
			{
				BackgroundColor(0);
				GotoXY(19 * i, j);
				if (i <= 8)
				{
					if (i == block - 2) cout << TAB << " ";
					else cout << TAB;
				}
				if (i >= 2)
				{
					BackgroundColor(224);
					GotoXY(19 * (i - 2), 42 - j);
					if (i == block) cout << TAB << " ";
					else cout << TAB;
				}
				this_thread::sleep_for(chrono::microseconds(4));
			}
		}
	}
}