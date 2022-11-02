#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct Data
{
	string TenNguoiChoi;
	string TenFile;
	long Score = 0;
	int Level = 0;
	string Date;
};

struct point
{
	int x, y;
	int x0, y0;
	short int character;
};

struct Point_a
{
	int x;
	int y;
};

struct Point_b
{
	int x;
	int y;
	short int so;
	bool visit_1 = false;
	bool visit_2 = false;
};

struct Line
{
	Point_a dau;
	Point_a cuoi;
};

typedef vector<Line>Kieu;