#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#include"mylib.h"
#include"CauTruc.h"

void ghiFile(const string fname, int x, int y);

void luuFile(const char* fname, Data a);

void layFile(const char* fname, Data& a);

void Tomau(int color, int x_dau, int x_cuoi, int y_dau, int y_cuoi);
void Tomau_thanh_diem(int color, int x_dau, int x_cuoi, int y_dau, int y_cuoi);

void Khung(WORD color, int x_dau, int x_cuoi, int y_dau, int y_cuoi);

void TEAM_3();

void Khung_Lon();

void Khung_Nho();

void Theme();

void MoveWindow(int posx, int posy);