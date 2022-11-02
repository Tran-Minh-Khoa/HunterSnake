#include "lib.h"

short whereX() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}
//========= lấy tọa độ y của con trỏ hiện tại =======
short whereY() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}
//============== dịch con trỏ hiện tại đến điểm có tọa độ (x,y) ==========
void gotoXY(const short& x, const short& y) {
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void gotoXY(const point_1& p) {
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { p.x, p.y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
//============= đặt màu cho chữ =========
void WordColor(Word color) {
	WORD __color = static_cast<WORD>(color);
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	__color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= __color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void ResetWordColor() {
	WordColor(Word::BLACK);
}
//============== làm ẩn trỏ chuột ===========
void ShowCur(bool CursorVisibility) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
//======= trả về mã phím người dùng bấm =========
short inputKey() {
	if (_kbhit()) {
		short key = _getch();

		if (key == 224) {
			key = _getch();
			return key + 1000;
		}
		return key;
	}
	else {
		return UNDEFINED;
	}
}
// Chuyen mau nen man hinh console
void BackgroundColor(Background color) {
	HANDLE bg_color;
	bg_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(bg_color, (WORD)color);
}
void ResetBGColor() {
	BackgroundColor(Background::LIGHT_YELLOW);
}
// Thay doi kich thuoc man hinh console
void resizeConsole(const short& width, const short& height) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
// Co dinh man hinh console
void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
// Dich chuyen man hinh console den toa do (x,y)
void MoveWindow(const short& posx, const short& posy) {
	RECT rectClient, rectWindow;
	HWND hWnd = GetConsoleWindow();
	GetClientRect(hWnd, &rectClient);
	GetWindowRect(hWnd, &rectWindow);
	MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}
// An thanh cuon chuot 
void HideScrollBar() {
	HWND x = GetConsoleWindow();
	ShowScrollBar(x, SB_BOTH, FALSE);
}
// Ham xoa du lieu cu
void BackSpace(const short& x, const short& y, const short& width) {
	gotoXY(x, y);
	for (short i = 1; i <= width; i++) {
		std::cout << " ";
	}
}
void BackSpace(const point_1& pos, const short& width) {
	gotoXY(pos);
	for (short i = 1; i <= width; ++i) {
		std::cout << " ";
	}
}

point_1 Centerpoint_1(const point_1& head, const point_1& tail) {
	point_1 tmp{};
	tmp.x = (tail.x - head.x) / 2;
	tmp.y = (tail.y - head.y) / 2;
	return tmp;
}
short GetWidth(const short& start, const short& end) {
	return end - start + 1;
}
// Xoa man hinh
void ClearScreen() {
	short i(-1);
	for (i = 0; i < (short)Console::HEIGHT; ++i) {
		gotoXY(0, i);
		PrintLine(SPACE, (short)Console::WIDTH);
	}
}
// dieu chinh ty le man hinh console
void SetupConsoleScreen() {
	// Dieu chinh ty le va vi tri man hinh console
	SetConsoleTitle(L"Mini Game");
	MoveWindow(-7, -5);
	resizeConsole(1920, 1080);
	FixConsoleWindow();
	HideScrollBar();
	ShowCur(0);
}
void ColoringBackGround() {
	ResetBGColor();
	short i(-1), j(-1);
	for (i = 0; i <= (short)Console::WIDTH; i++)
	{
		for (j = 0; j <= (short)Console::HEIGHT; j++)
		{
			std::cout << " ";
		}
	}
}
void PrintLine(const char& leftMostChar, const char& middleChar, const char& rightMostChar, const short& length, const short& width) {
	std::cout << leftMostChar;

	for (short i = 0; i < ((length - 1) / width - width); i++)
	{
		std::cout << std::setw(width) << middleChar;
	}

	std::cout << std::setw(width) << rightMostChar;
}

void PrintLine(const char& Ch, const short& length, const short& width) {
	std::cout << Ch;

	for (short i = 0; i < ((length - 1) / width); i++)
	{
		std::cout << std::setw(width) << Ch;
	}
}

void PrintChar(const short& x, const short& y, const char& Ch) {
	gotoXY(x, y);
	std::cout << Ch;
}
void readFile(const char* fname, short x, short y) {
	std::string str;
	std::ifstream fIn;
	fIn.open(fname, std::ios::beg);

	if (fIn.is_open()) {
		short i(0);

		while (!fIn.eof()) {
			Sleep(1);
			std::getline(fIn, str);

			gotoXY(x, y);
			std::cout << str;

			y++;
		}
		fIn.close();
	}
}