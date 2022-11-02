#include "GiaoDienBasic.h"

void ghiFile(const string fname, int x, int y)
{
	ifstream fi;
	fi.open(fname);
	string c;
	int i = 0;
	while (!fi.eof())
	{
		getline(fi, c);
		GotoXY(x, y + i);
		if (fname == "Thanks.txt")
		{
			for (int i = 0; i <= c.length() - 1; ++i)
			{
				if (c[i] == '+') cout << char(3);
				else cout << c[i];
			}
		}else cout << c << "\n";
		++i;
	}
	fi.close();
}

void luuFile(const char* fname, Data a)
{
	ofstream fo;
	fo.open(fname);
	fo << a.TenNguoiChoi << "\n";
	fo << a.Score << "\n";
	fo << a.Level << "\n";
	fo << a.Date << "\n";
	fo.close();
}

void layFile(const char* fname, Data& a)
{
	ifstream fi;
	fi.open(fname);
	getline(fi, a.TenNguoiChoi);
	fi >> a.Score;
	fi >> a.Level;
	fi.ignore();
	getline(fi, a.Date);
}

void Tomau(int color, int x_dau, int x_cuoi, int y_dau, int y_cuoi)
{
	BackgroundColor(color);
	for (int i = y_dau; i <= y_cuoi; ++i)
	{
		for (int j = x_dau; j <= x_cuoi; ++j)
		{
			GotoXY(j, i);
			cout << " ";
		}
		cout << "\n";
	}
}

void Tomau_thanh_diem(int color, int x_dau, int x_cuoi, int y_dau, int y_cuoi)
{
	SetColor(color);
	for (int i = y_dau; i <= y_cuoi; ++i)
	{
		for (int j = x_dau; j <= x_cuoi; ++j)
		{
			GotoXY(j, i);
			cout <<char(178);
		}
		cout << "\n";
	}
}

void Khung(WORD color, int x_dau, int x_cuoi, int y_dau, int y_cuoi)
{
	SetColor(color);
	// cach tren
	GotoXY(x_dau, y_dau);
	cout << char(201);
	for (int i = x_dau + 1; i <= x_cuoi - 1; ++i)
	{
		cout << char(205);
	}
	cout << char(187);
	// 2 canh ben
	for (int i = y_dau + 1; i <= y_cuoi - 1; ++i)
	{
		GotoXY(x_dau, i);
		cout << char(186);
		GotoXY(x_cuoi, i);
		cout << char(186);
	}
	// cach duoi
	GotoXY(x_dau, y_cuoi);
	cout << char(200);
	for (int i = x_dau + 1; i <= x_cuoi - 1; ++i)
	{
		cout << char(205);
	}
	cout << char(188);
	GotoXY(0, 0);
}

void TEAM_3()
{
	int IDx = 74, IDy = 2;
	// T
	BackgroundColor(112);
	GotoXY(IDx, IDy);
	SetColor(12);
	cout << char(220) << char(220) << char(220) << char(220) << char(220);
	GotoXY(2 + IDx, 1 + IDy);
	BackgroundColor(192);
	cout << " ";
	GotoXY(2 + IDx, 2 + IDy);
	cout << " ";
	BackgroundColor(112);
	// E
	SetColor(10);
	GotoXY(6 + IDx, 0 + IDy);
	cout << char(220) << char(220) << char(220);
	GotoXY(8 + IDx, 1 + IDy);
	BackgroundColor(160);
	cout << " ";
	BackgroundColor(112);
	SetColor(10);
	GotoXY(6 + IDx, 1 + IDy);
	cout << char(220) << char(220);
	BackgroundColor(160);
	GotoXY(8 + IDx, 2 + IDy);
	cout << " ";
	BackgroundColor(112);
	SetColor(10);
	GotoXY(6 + IDx, 2 + IDy);
	cout << char(220) << char(220);
	BackgroundColor(112);
	// A
	SetColor(12);
	GotoXY(11 + IDx, 0 + IDy);
	cout << char(220) << char(220) << char(220);
	BackgroundColor(192);
	GotoXY(10 + IDx, 1 + IDy);
	cout << " ";
	BackgroundColor(112);
	SetColor(12);
	GotoXY(11 + IDx, 1 + IDy);
	cout << char(220) << char(220) << char(220);
	BackgroundColor(192);
	GotoXY(10 + IDx, 2 + IDy);
	cout << " ";
	GotoXY(14 + IDx, 1 + IDy);
	cout << " ";
	GotoXY(14 + IDx, 2 + IDy);
	cout << " ";
	BackgroundColor(112);
	// M
	SetColor(12);
	GotoXY(16 + IDx, 0 + IDy);
	cout << char(220);
	GotoXY(17 + IDx, 1 + IDy);
	cout << char(223);
	GotoXY(18 + IDx, 1 + IDy);
	cout << char(220);
	BackgroundColor(192);
	GotoXY(16 + IDx, 1 + IDy);
	cout << " ";
	GotoXY(16 + IDx, 2 + IDy);
	cout << " ";
	BackgroundColor(112);
	SetColor(12);
	GotoXY(20 + IDx, 0 + IDy);
	cout << char(220);
	GotoXY(19 + IDx, 1 + IDy);
	cout << char(223);
	BackgroundColor(192);
	GotoXY(20 + IDx, 1 + IDy);
	cout << " ";
	GotoXY(20 + IDx, 2 + IDy);
	cout << " ";
	BackgroundColor(112);

}

void Khung_Lon()
{
	resizeConsole(1920, 1080);
	FixConsoleWindow();
	// to mau nen
	Tomau(224, 0, 171, 0, 42);
	// xet khung vien
	Khung(0, 2, 169, 1, 41);
	ShowCur(0);
}

void Khung_Nho()
{
	BackgroundColor(224);
	Khung(12, 6, 165, 6, 40);
	GotoXY(50, 6);
	cout << char(203);
	GotoXY(50, 40);
	cout << char(202);
	for (int i = 7; i <= 39; ++i)
	{
		GotoXY(50, i);
		cout << char(186);
	}
}

void Theme()
{
	string c;
	int i = 0;
	PlaySound(L"marvel.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
	Sleep(2000);
	ghiFile("Text.txt", 22, 2);
	Sleep(2000);
	ghiFile("Text1.txt", 20, 3);
	Sleep(2000);
	ghiFile("Text2.txt", 22, 2);
	Sleep(2000);
	ghiFile("Text3.txt", 20, 3);
	Sleep(2000);
}

void MoveWindow(int posx, int posy)
{
	RECT rectClient, rectWindow;
	HWND hWnd = GetConsoleWindow();
	GetClientRect(hWnd, &rectClient);
	GetWindowRect(hWnd, &rectWindow);
	MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}
