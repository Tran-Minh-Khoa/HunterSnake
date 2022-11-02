#pragma once
#include "mylib.h"

using namespace std;

bool Cmp(Data a, Data b);

void High_Score(Data HighScore[10]);

void Xuat_Load_Game(Data Lich_Su[10]);

void Di_Chuyen_Load_Game(int load_i, int load_i_cu, Data Lich_Su[10]);

void Menu_dongs(string menu[], int menu_i);

void Play(int x, Data Lich_Su[10], Data HighScore[10], int load_i, int load_i_cu, bool phai, char c);

void control_func(Data Lich_Su[10], Data HighScore[10], Kieu Man[5]);

void keoRem();
