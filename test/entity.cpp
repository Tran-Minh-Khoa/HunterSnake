#include "entity.h"
short LEVEL = INITIAL_LEVEL;
short SNAKE_SPEED = SPD_AT_LEVEL_1;
bool GAME_OVER = false;
bool WIN_GAME = false;
bool PAUSE = false;
short SCORE = INITIAL_SCORE;
short TIME = TIME_AT_LEVEL_1;
bool TIME_OVER = false;
Word FR_COLOR = Word::WHITE;
Word SNAKE_COLOR = Word::BLACK;
bool FlagOpenGate = true;
short SNAKE_SIZE = ORIGINAL_SIZE;
point_1 HEAD_point_1{ 0,0 };
const string SNAKE_APPEARANCE = "2112703321127629211273062112773921127033211276292112730621127739";
short MAX_SCORE_PER_LEVEL[] = { SCORE_AT_LEVEL_1,SCORE_AT_LEVEL_1 + SCORE_AT_LEVEL_2, UNDEFINED };
short MAX_TIME_PER_LEVEL[] = { TIME_AT_LEVEL_1,TIME_AT_LEVEL_2, UNDEFINED };
short gate[3][3] = {
	   {219, 32, 219},
	   {220, 32, 223},
	   {220, 219, 223},
};
Data_1* ptrToData_1 = nullptr;
Announce* ptrToAnnoun = nullptr;
PlayFrame* ptrToPF = nullptr;
queue<Word> NextColor{};
std::mutex mtx;
std::condition_variable cv;
/* ============================================================ */
class Obstacle : public WALL {
private:
	short x{ -1 }, y{ -1 }, tms{ -1 };
	void Letter_U(WALL& wall, const short& height, const short& width) {
		// Chu U: net doc
		tms = height;// chieu cao cua net doc
		y = wall.endCoord.y - 5 - 1;// Khoang cach so voi PlayFrame: 4
		x = wall.center.x - 25;	// (total width)51 / 2

		while (tms--) {
			// 2 cot ben trai
			wall.frame[y][x] = true;
			wall.frame[y][x + 1] = true;

			// 2 cot ben phai
			wall.frame[y][x + 32] = true;
			wall.frame[y][x + 33] = true;

			y--;
		}

		// Chu U: net ngang
		tms = width - 4; // so ky tu
		y = wall.endCoord.y - 5 - 1; // Khoang cach so voi PlayFrame: 4
		x += 2;	// vi tri ke ben cot trai

		while (tms--) {
			wall.frame[y][x] = true;
			x++;
		}
	}
	void Letter_N(WALL& wall, const short& height, const short& width) {
		// Chu N: net doc
		tms = height;// chieu cao cua net doc
		y = wall.startCoord.y + 5; // Khoang cach so voi PlayFrame: 4
		x = wall.center.x - (short)round(width / 4 + 0.5);// Vi tri giua chu U: [width/4]

		while (tms--) {
			// 2 cot ben trai
			wall.frame[y][x] = true;
			wall.frame[y][x + 1] = true;

			// 2 cot ben phai
			wall.frame[y][x + 32] = true;
			wall.frame[y][x + 33] = true;

			y++;
		}

		// Chu N: net ngang
		tms = width - 4; // so ky tu
		y = wall.startCoord.y + 5; // Khoang cach so voi PlayFrame: 4
		x += 2;

		while (tms--) {
			wall.frame[y][x] = true;
			x++;
		}
	}
	void Letter_L(WALL& wall) {
		/**************************************************
		 Goc tren trai	-----
							  |
		 ***************************************************/
		tms = 14;
		y = wall.startCoord.y + 4;
		x = wall.startCoord.x + 10;
		while (tms--) {
			wall.frame[y - 1][x] = true;
			wall.frame[y][x] = true;
			x++;
		}

		x -= 2;
		y++;
		tms = 6;
		while (tms--) {
			wall.frame[y][x] = true;
			wall.frame[y][x + 1] = true;
			y++;
		}
		/**************************************************
		Goc duoi trai	|
						-----
		***************************************************/
		tms = 14;
		y = wall.endCoord.y - 4 - 1;
		x = wall.startCoord.x + 10;
		while (tms--) {
			wall.frame[y + 1][x] = true;
			wall.frame[y][x] = true;
			x++;
		}

		x = wall.startCoord.x + 10;
		y--;
		tms = 6;
		while (tms--) {
			wall.frame[y][x] = true;
			wall.frame[y][x + 1] = true;
			y--;
		}
	}
	void Pillar(WALL& wall) {
		// Cot 1
		tms = (wall.endCoord.y - wall.startCoord.y - 1) * 2 / 3;
		y = wall.startCoord.y;
		x = wall.endCoord.x - 36 - 1;
		while (tms--) {
			wall.frame[y][x] = true;
			y++;
		}

		// Cot 2
		y = wall.endCoord.y - 1 - 1;
		x += 9;
		tms = (wall.endCoord.y - wall.startCoord.y - 1) * 3 / 4;
		while (tms--) {
			wall.frame[y][x] = true;
			y--;
		}

		// Cot 3
		y = wall.startCoord.y;
		x += 9;
		tms = (wall.endCoord.y - wall.startCoord.y - 1) * 3 / 4;
		while (tms--) {
			wall.frame[y][x] = true;
			y++;
		}

		// Cot 4
		y = wall.endCoord.y - 1 - 1;
		x += 9;
		tms = (wall.endCoord.y - wall.startCoord.y - 1) * 2 / 3;
		while (tms--) {
			wall.frame[y][x] = true;
			y--;
		}

	}
public:
	void getObstacle(WALL& wall, const short& LEVEL) {
		if (LEVEL <= INITIAL_LEVEL || LEVEL >= MAX_LEVEL) {
			return;
		}
		/**************************************************
		Goc giua	  *******	 density/tur: 2, width: 34, height: 32/2 = 16
					* * * *	 total width = 34 + 34 / 2 = 51
					* * * *	 thanh ngang: 34-2*2 = 30 => 14 khoang trang
					*******
		***************************************************/
		short height = 16, width = 34;
		/* Letter U */
		Letter_U(wall, height, width);

		/* Letter N */
		Letter_N(wall, height, width);

		/**************************************************
		Goc trai	*******
						 *
						 *

					*
					*
					*******
		***************************************************/
		Letter_L(wall);

		/**************************************************
			Goc phai	*		  *
						*		  *
						*		  *
		width = 36		*		  *
						*		  *
								  *
								  *
							 *  *
							 *
							 *		  *
							 *		  *
							 *		  *
							 *		  *
							 *		  *
		***************************************************/
		Pillar(wall);
	}
};
class EastGate : public WALL {
private:
	char rightArrow{ 16 };
	point_1 mid{ WALL::endCoord.x - 1,WALL::center.y };
	point_1 top{ mid.x,mid.y / 2 };
	point_1 bot{ mid.x,mid.y * 3 / 2 };
	void Exit(WALL& wall, const point_1& pt) {
		std::unique_lock<mutex> locker(mtx);

		wall.frame[pt.y][pt.x] = false;

		for (short i = 0; i < 3; ++i) {
			Sleep(50 + 10 * i);
			HorizontalDraw(pt.x + i, pt.y - 1, gate[i]);
		}

		Sleep(50);
		gotoXY(pt);
		cout << rightArrow;

		locker.unlock();
		cv.notify_one();
	}
public:
	void NextLevelGate(WALL& wall) {
		WordColor(Word::LIGHT_RED);
		Exit(wall, mid);
	}
};
class WestGate {
public:
	friend void Entrance(WALL& wall) {
		std::unique_lock<mutex> locker(mtx);

		point_1 pt{ wall.startCoord.x, wall.center.y };

		wall.frame[pt.y][pt.x] = false;

		for (short i = 0; i < 3; ++i) {
			Sleep(50 + 10 * i);
			HorizontalDraw(pt.x - i, pt.y - 1, gate[i]);
		}

		Sleep(50);
		gotoXY(pt);
		cout << char(16);

		locker.unlock();
		cv.notify_one();
	}
};
class Gate : public EastGate, public WestGate {

};
Obstacle ob{};
Gate g{};
/****************************************************************/
void print(string s, const short& sleepTime) {
	std::unique_lock<mutex> locker_1(mtx);
	WordColor(Word::LIGHT_GREEN);
	for (short i = 0; i < (short)s.length(); ++i) {
		std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
		cout << s[i];
	}
	locker_1.unlock();
	cv.notify_one();
}
void HorizontalDraw(const short& x, const short& y, short* ltr) {
	for (short i = 0; i < 3; i++)
	{
		gotoXY(x, y + i);
		cout << static_cast<char>(*(ltr + i));
	}
};
// Khoi tao ran ban dau
void SnakeInit(Snake& snake, const WALL& wall) {
	if (LEVEL == INITIAL_LEVEL) {
		snake.reserve(MAX_LENGTH_SNAKE);
		snake.resize(ORIGINAL_SIZE);

		short x = wall.startCoord.x + ORIGINAL_SIZE + 1;
		short y = (wall.endCoord.y - wall.startCoord.y) / 2;

		for (short i = 0; i < (short)snake.size(); i++)
		{
			snake[i].pos = { x,y };
			snake[i].appearance = SNAKE_APPEARANCE[i];
			x--;
		}
	}
}
// Ve ran
void DrawSnake(const Snake& snake) {
	WordColor(SNAKE_COLOR);

	for (int i = 0; i < (int)snake.size(); i++)
	{
		gotoXY(snake[i].pos);
		cout << snake[i].appearance;
	}
}
// Khoi tao ran len man hinh console
void SetupSnake(Snake& snake, const WALL& wall) {
	SnakeInit(snake, wall);
	// Ve ran
	DrawSnake(snake);
	HEAD_point_1 = snake[0].pos;
}
// Xu ly nhap phim di chuyen ran tu ban phim
void HandleMovingSnakeInput(const Direction& dir, Moving& check) {
	if (dir == Direction::DOWN && check != Moving::UP)// di xuong
	{
		check = Moving::DOWN;
	}
	else  if (dir == Direction::UP && check != Moving::DOWN)	// di len
	{
		check = Moving::UP;
	}
	else  if (dir == Direction::RIGHT && check != Moving::LEFT)// qua phai
	{
		check = Moving::RIGHT;
	}
	else  if (dir == Direction::LEFT && check != Moving::RIGHT)// qua trai
	{
		check = Moving::LEFT;
	}
}
// Tim diem ngay truoc dau con ran
void FindHeadPos(const Moving& check) 
{
	if (check == Moving::DOWN)
	{
		HEAD_point_1.y++;
	}
	else if (check == Moving::UP)
	{
		HEAD_point_1.y--;
	}
	else if (check == Moving::RIGHT)
	{
		HEAD_point_1.x++;
	}
	else if (check == Moving::LEFT)
	{
		HEAD_point_1.x--;
	}
}
//	Kiem tra ran cham than
bool CheckSnakeTouchBody(const Snake& snake) {
	for (short i = 1; i < (short)snake.size(); i++)
	{
		if (CheckTwopoint_1sOverlap(snake[0].pos, snake[i].pos) == true)
		{
			PlaySound(L"hit-body_1.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
			return true;
		}
	}
	return false;
}
// Kiem tra ran cham tuong
inline bool CheckSnakeHitWall(const snake& headSnake, WALL& wall) {
	if (wall.frame[headSnake.pos.y][headSnake.pos.x]) {
		PlaySound(L"hit-wall_1.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
		return true;
	}
	return false;
}
// Kiem tra hai diem trung nhau
inline bool CheckTwopoint_1sOverlap(const point_1& p1, const point_1& p2)
{
	if ((p1.x == p2.x) && (p1.y == p2.y)) {
		return true;
	}
	return false;
}
// Kiem tra qua de len ran
bool CheckFruitOverlapSnake(const fruit& fr, const Snake& snake)
{
	for (int i = 0; i < (int)snake.size(); i++)
	{
		if (CheckTwopoint_1sOverlap(fr.pos, snake[i].pos))
		{
			return true;
		}
	}
	return false;
}
// Kiem tra qua de len tuong
inline bool CheckFruitOverlapWall(const fruit& fr, WALL& wall) {

	return wall.frame[fr.pos.y][fr.pos.x];
}
// kiem tra khoi tao qua co bi loi hay khong
bool CheckFruitInvalidAppear(const fruit& fr, WALL& wall, const Snake& snake)
{
	bool isFruitOverlapWall = CheckFruitOverlapWall(fr, wall);
	bool isFruitOverlapSnake = CheckFruitOverlapSnake(fr, snake);
	return(isFruitOverlapWall || isFruitOverlapSnake);
}
// Khoi tao qua
point_1 RandomFruitCoord(const point_1& min, const point_1& max) {
	point_1 tmp{};
	tmp.x = (rand() % (max.x - min.x - 1)) + (min.x + 1);
	tmp.y = (rand() % (max.y - min.y - 1)) + (min.y + 1);
	return tmp;
}
Word RandomColor(const Word& start, const Word& end) {
	Word tmp{};
	short noColor = (rand() % ((short)end - (short)start + 1)) + (short)start;
	tmp = static_cast<Word>(noColor);
	return tmp;
}
void GetFruitColor() {
	Word color{ Word::LIGHT_YELLOW };

	do {
		color = RandomColor(Word::BLUE, Word::LIGHT_PURPLE);

	} while (color == Word::YELLOW
		|| color == Word::WHITE
		|| color == Word::GRAY
		|| color == Word::LIGHT_AQUA);

	NextColor.push(color);
}
void GenerateFruit(fruit& fr, WALL& wall, const Snake& snake) {
	if (SCORE < MAX_SCORE_PER_LEVEL[LEVEL - 1])
	{
		do {
			// random toa do x,y cua qua trong khoang cho phep
			fr.pos = RandomFruitCoord(wall.startCoord, wall.endCoord);

		} while (CheckFruitInvalidAppear(fr, wall, snake) == true);
		// random hinh dang fr
		fr.shape = rand() % (6 - 3 + 1) + 3;

		// random fruit color
		GetFruitColor();

		if (!NextColor.empty()) {
			FR_COLOR = NextColor.back();
		}
		else {
			cerr << "[!] Error: empty color [!]";
		}
		// Xuat fruit ra console screen
		WordColor(FR_COLOR);
		gotoXY(fr.pos);
		cout << char(fr.shape);
	}
	else if (SCORE == MAX_SCORE_PER_LEVEL[LEVEL - 1]) {
		fr.pos.x = 0;
		fr.pos.y = 0;
	}
}
// Kiem tra ran an moi
bool CheckSnakeEatFruit(const snake& headSnake, const fruit& fr) {
	if (CheckTwopoint_1sOverlap(headSnake.pos, fr.pos) == true)
	{
		return true;
	}
	return false;
}
// them toa do moi vao dau con ran
void Add(Snake& snake) {
	SNAKE_SIZE++;
	snake.resize(SNAKE_SIZE);

	for (int i = SNAKE_SIZE - 1; i > 0; i--)
	{
		snake[i].pos = snake[(abs)(i - 1)].pos;
	}
	snake[0].pos = HEAD_point_1;
}
// Xoa toa do o duoi con ran
void Delete(Snake& snake) {
	snake.pop_back();
	SNAKE_SIZE--;
}
// Xu ly khi ran an moi
void HandleSnakeEatFruit(Snake& snake, const fruit& fr) {
	snake[(abs)(SNAKE_SIZE - 1)].appearance = SNAKE_APPEARANCE[(abs)(SNAKE_SIZE - 1)];
	SNAKE_SPEED += fr.shape * 5;
	SCORE += 1;

	// Chuyen mau ran
	if (!NextColor.empty()) {
		SNAKE_COLOR = NextColor.front();
		NextColor.pop();
	}
}
// Xu ly ran
void HandleSnake(Snake& snake, fruit& fr, WALL& wall) {
	this_thread::sleep_for(microseconds(1));
	std::unique_lock<mutex> locker(mtx);
	// Xoa du lieu cu
	BackSpace(snake[(abs)(SNAKE_SIZE - 1)].pos);

	// Them mot vi tri o dau mang
	Add(snake);

	// Neu ran khong an qua
	if (CheckSnakeEatFruit(snake[0], fr) == false)
	{
		// Xoa mot vi tri o cuoi mang
		Delete(snake);
	}
	// ======== Xu ly ran an qua ========
	else {
		PlaySound(L"eatSound_2_1.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
		// Tai tao qua moi
		HandleSnakeEatFruit(snake, fr);
		GenerateFruit(fr, wall, snake);
		ShowScore(ptrToData_1);
	}
	// Ve ran
	DrawSnake(snake);

	locker.unlock();
}

bool** CreateArray(const WALL& wall) {
	bool** arr = NULL;

	if ((wall.endCoord.x > 0) || (wall.endCoord.y > 0)) {
		arr = new bool* [wall.endCoord.y * sizeof(bool)];

		for (int i = 0; i < wall.endCoord.y; ++i) {
			arr[i] = new bool[wall.endCoord.x * sizeof(bool)];
		}
	}
	else {
		cerr << "[!] Invalid coord value from wall !";
	}
	return arr;
}

void DeleteArray(WALL& wall) {
	for (int i = 0; i < wall.endCoord.y; ++i)
	{
		delete[]wall.frame[i];
	}
	delete[]wall.frame;
	wall.frame = NULL;
}
// Khoi tao gia tri ban dau cho tuong
void WallInit(WALL& wall) {
	for (int i = 0; i < wall.endCoord.y; ++i)
	{
		for (int j = 0; j < wall.endCoord.x; ++j)
		{
			wall.frame[i][j] = false;
		}
	}
}
// Basic level
void Wall_At_Level_1(WALL& wall) {
	short i;
	// Truc hoanh
	for (i = wall.startCoord.x; i < wall.endCoord.x; ++i)
	{
		wall.frame[wall.startCoord.y][i] = true;
		wall.frame[wall.endCoord.y - 1][i] = true;
	}
	// Truc tung
	for (i = wall.startCoord.y + 1; i < wall.endCoord.y - 1; ++i)
	{
		wall.frame[i][wall.startCoord.x] = true;
		wall.frame[i][wall.endCoord.x - 1] = true;
	}
}
// Ve tuong
void DrawWall(const WALL& wall) {
	int i, j;
	for (i = 0; i < wall.endCoord.y; ++i)
	{
		for (j = 0; j < wall.endCoord.x; ++j)
		{
			if (wall.frame[i][j] == true)
			{
				gotoXY(j, i);
				cout << "#";
			}
		}
	}
}

void SetupWall(WALL& wall) {
	// Khoi tao mang dong
	if (wall.frame == NULL) {
		wall.frame = CreateArray(wall);
	}

	// Set gia tri mac dich = false
	WallInit(wall);

	Wall_At_Level_1(wall);
}

void SnakeEnterTheGate(const Snake& __snake) {
	deque<char> Dq;
	short i;

	for (i = 0; i < SNAKE_SIZE; ++i) {
		Dq.push_back(__snake[i].appearance);
	}

	WordColor(SNAKE_COLOR);
	while (!Dq.empty()) {
		// Xoa cac phan tu o duoi ran
		BackSpace(__snake[Dq.size() - 1].pos);

		// Giam so phan tu cua deque
		Dq.pop_front();

		if (!Dq.empty()) {
			// Xuat cac ky tu con lai
			i = 0;
			for (auto& item : Dq) {
				gotoXY(__snake[i].pos);
				cout << item;
				i++;
			}
			this_thread::sleep_for(chrono::milliseconds(20));
		}
		else {
			break;
		}
	}
}

void SetPosInLevel2(Snake& snake) {
	short x = 20;
	short y = 20;

	for (int i = 0; i < (short)snake.size(); i++)
	{
		snake[i].pos = { x,y };
		y--;
	}
	// Ve ran
	DrawSnake(snake);
	HEAD_point_1 = snake[0].pos;
}

void SetPosInLevel3(Snake& snake, WALL& wall) {
	short x = wall.startCoord.x + (short)snake.size() + 3;
	short y = wall.center.y;

	for (int i = 0; i < (short)snake.size(); i++)
	{
		snake[i].pos = { x,y };
		x--;
	}
	// Ve ran
	DrawSnake(snake);
	HEAD_point_1 = snake[0].pos;
}

void drawScreen(Snake& snake, WALL& wall, fruit& fr) {
	/* Setup next level */
	SetupWall(wall);
	ob.getObstacle(wall, LEVEL);// them chuong ngai vat

	if (ptrToData_1 != nullptr) {
		ptrToData_1->DrawFrame();
	}
	if (ptrToAnnoun != nullptr) {
		ptrToAnnoun->DrawFrame();
	}
	if (ptrToPF != nullptr) {
		ptrToPF->DrawFrame(LEVEL);
	}

	switch (LEVEL)
	{
	case 1: {
		SetupSnake(snake, wall);
		GenerateFruit(fr, wall, snake);
	}	break;

	case 2: {
		// SetupSnake(snake, wall);
		SetPosInLevel2(snake);
		GenerateFruit(fr, wall, snake);
	}	break;

	case 3: {
		readFile("Text_12.txt", wall.startCoord.x + 1, wall.center.y - 7);
		SetPosInLevel3(snake, wall);
	}	break;
	}
	// Thong tin khung nho
	ptrToData_1->SetupData_1(TIME, SCORE);
	ptrToAnnoun->LevelInfo(LEVEL);
}

void LevelUp(Snake& snake, WALL& wall, fruit& fr) {
	PAUSE = true;
	SNAKE_SPEED = SPD_AT_LEVEL_2;
	if (!NextColor.empty()) {
		NextColor.pop();
	}
	/* Hieu ung ran qua cong */
	SnakeEnterTheGate(snake);

	/* Tang level(neu khong vuot qua gioi han) */
	if (LEVEL < MAX_LEVEL) {
		LEVEL += UP_LEVEL;
		TIME = MAX_TIME_PER_LEVEL[(abs)(LEVEL - 1)];
	}
	else if (LEVEL == MAX_LEVEL) {
		PAUSE = false;
		WIN_GAME = true;
		return;
	}
	ClearScreen();
	drawScreen(snake, wall, fr);
	PAUSE = false;
	cv.notify_all();
}

void init() {
	// Cap phat dong mot so bien toan cuc
	if (ptrToData_1 == nullptr) {
		ptrToData_1 = new Data_1();
	}
	if (ptrToAnnoun == nullptr) {
		ptrToAnnoun = new Announce();
	}
	if (ptrToPF == nullptr) {
		ptrToPF = new PlayFrame();
	}
}
// Kiem tra game over
bool CheckGameOver(const Snake& snake, WALL& wall) {
	bool isSnakeHitWall = CheckSnakeHitWall(snake[0], wall);
	bool isSnakeTouchBody = CheckSnakeTouchBody(snake);
	return (isSnakeHitWall || isSnakeTouchBody || TIME_OVER);
}
/* Nhom ham xu ly luong */
void OpenGate(WALL& wall) {
	PAUSE = true;
	g.NextLevelGate(wall);
	PlaySound(L"typing_1.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
	if (LEVEL >= MAX_LEVEL) {
		ptrToAnnoun->FinishChal();
	}
	else {
		ptrToAnnoun->NextLevel();
	}
	FlagOpenGate = false;
	PAUSE = false;
}

void EndGame(WALL& wall, Snake& snake, fruit& fr) {
	SNAKE_SPEED = TERMINAL_SPD;
	PlaySound(L"victory_1.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);

	Moving check = Moving::RIGHT;
	Direction dir = Direction::RIGHT;

	while (CheckTwopoint_1sOverlap(snake[0].pos, { (short)(wall.endCoord.x - 2), wall.center.y }) == false)
	{
		HandleMovingSnakeInput(dir, check);
		// Tim diem ngay phia truoc dau con ran
		FindHeadPos(check);
		HandleSnake(snake, fr, wall);
		Sleep(SLEEP_TIME / SNAKE_SPEED);
	}
	//LEVEL++;
}

void WinGame(WALL& wall) {
	PlaySound(L"win-game_1.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
	ClearScreen();
	WordColor(Word::BLUE);
	readFile("YouWon_12.txt", wall.center.x - 15, wall.center.y);

	gotoXY(0, 0);
}

void ResetData_1(WALL& wall, Snake& snk) {
	// xoa mang
	DeleteArray(wall);

	// Xoa cac con tro toi class
	delete ptrToData_1; ptrToData_1 = nullptr;
	delete ptrToAnnoun; ptrToAnnoun = nullptr;
	delete ptrToPF; ptrToPF = nullptr;

	// Xoa bo nho trong queue
	while (!NextColor.empty()) {
		NextColor.pop();
	}
	// Xoa bo nho trong Snake
	while (!snk.empty()) {
		snk.pop_back();
	}

	SNAKE_SPEED = SPD_AT_LEVEL_1;
	GAME_OVER = false;
	WIN_GAME = false;
	SCORE = INITIAL_SCORE;
	TIME = TIME_AT_LEVEL_1;
	LEVEL = INITIAL_LEVEL;
	TIME_OVER = false;
	FR_COLOR = Word::WHITE;
	SNAKE_COLOR = Word::BLACK;
	FlagOpenGate = true;
	PAUSE = false;
	SNAKE_SIZE = ORIGINAL_SIZE;
	HEAD_point_1 = { 0,0 };
}

void PauseThread(Direction& dir) {
	bool checkPause = false;
	if (PAUSE == true) { checkPause = true; }
	else { PAUSE = true; }
	if (ptrToAnnoun != nullptr) {
		ptrToAnnoun->Pause();
	}
	while (1) {
		if (_kbhit()) {
			dir = static_cast<Direction>(toupper(_getch()));
			if (dir == Direction::LOAD) {
				this_thread::yield();
				ptrToAnnoun->Play();
				if (!checkPause) { PAUSE = false; }
				return;
			}
		}
	}
}

void ShowScore(Data_1* dt) {
	// Delete old Data_1
	BackSpace(dt->posOfScore, 3);

	// Print new Data_1
	WordColor(Word::LIGHT_BLUE);

	gotoXY(dt->posOfScore);
	cout << SCORE;
}

void ShowTime(Data_1* dt) {
	if (dt == nullptr) {
		return;
	}
	// Delete old Data_1
	BackSpace(dt->posOfTime, 3);

	// Print new Data_1
	if (TIME >= 40) {
		WordColor(Word::GREEN);
	}
	else if (TIME >= 20) {
		WordColor(Word::LIGHT_GREEN);
	}
	else if (TIME >= 10) {
		WordColor(Word::LIGHT_RED);
	}
	else {
		WordColor(Word::RED);
	}

	gotoXY(dt->posOfTime);
	if (TIME >= 0) { cout << TIME; }
	else { cout << INF; }
}

void DeadThread(WALL& wall, Snake& snk) {
	gotoXY(snk[0].pos);
	WordColor(SNAKE_COLOR);
	cout << "x";
	this_thread::sleep_for(seconds(1));
	while (1) {
		if (_kbhit()) {
			ClearScreen();
			PlaySound(L"Died_1.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
			WordColor(Word::LIGHT_RED);
			readFile("YouLose_12.txt", wall.center.x - 15, wall.center.y);

			gotoXY(0, 0);
			return;
		}
	}
}
void CheckTimeOver() {
	// count down
	--TIME;

	while (GAME_OVER == false) {
		if (TIME >= 0) {
			Sleep(1000);
			std::unique_lock<mutex> locker(mtx);
			cv.wait(locker, []() {return !PAUSE; });
			this_thread::yield();
			if (GAME_OVER) { break; }
			ShowTime(ptrToData_1);
			locker.unlock();
			cv.notify_one();
			--TIME;
		}
		else {
			break;
		}
	}
	TIME_OVER = true;
}

int MiniGame() {
	srand((unsigned)time(NULL));
	SetupConsoleScreen();
	ColoringBackGround();

	WALL wall;
	Snake advSnake;
	fruit fr;

	init();
	drawScreen(advSnake, wall, fr);

	//// ================== Khoi tao thoi gian ==================
	thread th1(CheckTimeOver);

	Moving check = Moving::RIGHT;
	Direction dir = Direction::RIGHT;// huong di chuyen: mac dinh sang phai
	while (GAME_OVER == false)
	{
		// =========== Xu ly mo cong ===========
		if ((SCORE == MAX_SCORE_PER_LEVEL[LEVEL - 1]) && (FlagOpenGate == true)) {
			OpenGate(wall);
			PAUSE = true;
			TIME = SHRT_MAX;
		}
		// =========== Xu ly ran qua cong ===========
		if (advSnake[0].pos.x == wall.endCoord.x - 1 && advSnake[0].pos.y == wall.center.y) {
			FlagOpenGate = true;
			LevelUp(advSnake, wall, fr);

			if (LEVEL == MAX_LEVEL) {
				EndGame(wall, advSnake, fr);
				OpenGate(wall);
				LevelUp(advSnake, wall, fr);
			}
			if (WIN_GAME == true) {
				WinGame(wall);
				break;
			}
		}
		//============= Xu ly cho nguoi choi nhan phim chuyen huong	=============
		if (_kbhit())
		{
			dir = static_cast<Direction>(toupper(_getch()));
			if (dir == Direction::PAUSE) {
				PauseThread(dir);
			}
			else {
				HandleMovingSnakeInput(dir, check);
			}
		}
		// Tim diem ngay phia truoc dau con ran
		FindHeadPos(check);

		//============= Xu ly ve ran len man hinh console =============
		HandleSnake(advSnake, fr, wall);

		//============= Kiem tra game over	=============
		GAME_OVER = CheckGameOver(advSnake, wall);
		if (GAME_OVER == true) {
			DeadThread(wall, advSnake);
			break;
		}

		Sleep(SLEEP_TIME / SNAKE_SPEED);
	}
	// ===================== GIAI PHONG BO NHO =====================	
	TIME = 0;
	PAUSE = false;
	GAME_OVER = true;
	if (th1.joinable()) {
		th1.detach();
	}
	ResetData_1(wall, advSnake);

	system("pause>0");
	return 0;
}