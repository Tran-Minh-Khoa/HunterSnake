#pragma warning(disable : 4996)
#include<iostream>
#include"Menu.h"
#include<fstream>
#include<string>
#include<ctime>

Data Lich_Su[10], HighScore[10];
Kieu Man[5];

void Cai_dat(Data Lich_Su[])
{
	layFile("Game0.txt", Lich_Su[0]);
	layFile("Game1.txt", Lich_Su[1]);
	layFile("Game2.txt", Lich_Su[2]);
	layFile("Game3.txt", Lich_Su[3]);
	layFile("Game4.txt", Lich_Su[4]);

	layFile("1.txt", HighScore[0]);
	layFile("2.txt", HighScore[1]);
	layFile("3.txt", HighScore[2]);
	layFile("4.txt", HighScore[3]);
	layFile("5.txt", HighScore[4]);
	// man 2
	Man[1].push_back({ {83,19},{101,19} });
	Man[1].push_back({ {100,14},{100,18} });
	Man[1].push_back({ {83,22},{101,22} });
	Man[1].push_back({ {100,23},{100,27} });
	Man[1].push_back({ {110,19},{128,19} });
	Man[1].push_back({ {110,14},{110,18} });
	Man[1].push_back({ {110,22},{128,22} });
	Man[1].push_back({ {110,23},{110,27} });
	// man 3
	Man[2].push_back({ {75,6},{75,16} });
	Man[2].push_back({ {145,30},{145,40} });

	Man[2].push_back({ {65,30},{65,32} });
	Man[2].push_back({ {67,30},{67,32} });
	Man[2].push_back({ {65,30},{67,30} });
	Man[2].push_back({ {65,32},{67,32} });

	Man[2].push_back({ {85,20},{85,22} });
	Man[2].push_back({ {87,20},{87,22} });
	Man[2].push_back({ {85,20},{87,20} });
	Man[2].push_back({ {85,22},{87,22} });
	
	Man[2].push_back({ {100,27},{100,29} });
	Man[2].push_back({ {102,27},{102,29} });
	Man[2].push_back({ {100,27},{102,27} });
	Man[2].push_back({ {100,29},{102,29} });

	Man[2].push_back({ {117,12},{117,14} });
	Man[2].push_back({ {119,12},{119,14} });
	Man[2].push_back({ {117,12},{119,12} });
	Man[2].push_back({ {117,14},{119,14} });

	Man[2].push_back({ {134,20},{134,22} });
	Man[2].push_back({ {136,20},{136,22} });
	Man[2].push_back({ {134,20},{136,20} });
	Man[2].push_back({ {134,22},{136,22} });

	Man[2].push_back({ {153,14},{153,16} });
	Man[2].push_back({ {155,14},{155,16} });
	Man[2].push_back({ {153,14},{155,14} });
	Man[2].push_back({ {153,16},{155,16} });
}

int main()
{
	SetupConsoleScreen();
	ClearScreen();
	ColoringBackGround();
	SetConsoleTitle(L"Hunting Snake");
	MoveWindow(0, 0);
	Khung_Lon();
	Theme();
	Sleep(1500);
	BackgroundColor(14);
	ClearScreen();
	Cai_dat(Lich_Su);
	Khung_Lon();
	TEAM_3();
	Khung_Nho();
	control_func(HighScore,Lich_Su, Man);
	system("pause>0");
	return 0;
}