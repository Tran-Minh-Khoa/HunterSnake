#pragma once
#pragma warning(disable : 4996)
#include"mylib.h"
#include<ctime>

point random(short int character, Kieu Man[5], int soMan);

bool Move(int& snakeLen, point direction, point pos_snake[], string snake, point food, bool Dung, bool Thoat, Kieu Man[5], int Level);

void Game(Data& DuLieu, Data Lich_Su[10], Data HighScore[10], Kieu Man[5]);

void Cua();
void Thanh_diem(int n,bool check);
void Pin(int x, int y);
void PrintLine(const char& leftMostChar, const char& middleChar, const char& rightMostChar, const int& length, const int& width =1);
void vaoCong(point pos_snake[100], string snake, int snakeLen, point food, Kieu Man[5], int Level);