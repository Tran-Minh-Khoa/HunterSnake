#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cwchar>
#include<conio.h>
#include<Windows.h>
#include<deque>
#include <algorithm>
#include"GiaoDienBasic.h"
#include"CauTruc.h"
#include"Game.h"
#include "entity.h"
using namespace std;

void resizeConsole(int width, int height);

void GotoXY(int x, int y);

void SetColor(WORD color);

void BackgroundColor(int color);