#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void welcome();  //欢迎界面 
void border();  //创建边界 
void Pos(int x, int y);  //改变控制台光标位置 
void getRandomPos(int* x, int* y);  //获取随机坐标
void initSnake();  //蛇的初始化
void createFood();  //生成食物
int inSnake(int x, int y);  //判断(x, y)是否在蛇上，1表示在，0表示不在 
void snakeMove();  //蛇的移动 
int getDirection();  //获取移动方向，0、1、2、3分别代表上、下、左、右 

typedef struct Node {
	int x;
	int y;
	struct Node* next;
}node;

//全局变量
node* head;  //蛇头
node food;  //食物 
int reCreateFood;  //判断食物是否被吃掉
int fail;  //如果蛇头碰到蛇身或边界则失败 
int score, add = 10;  //定义分数和每个食物的分数 
int dx[4] = { 0, 0, -1, 1 }, dy[4] = { -1, 1, 0, 0 };  //(dx[0], dy[0])为(0, 1)，即代表“上”
int d = -1;  //表示蛇前进的方向，与上一行对应，0为上，1为下，2为左，3为右
//开局时初始化为-1，表示还未按方向键 

int main() {
	welcome();  //欢迎界面 
	border();  //创建边界 
	initSnake();  //蛇的初始化 
	createFood();  //生成食物 

	//fail ！= 0就一直进行 
	while (1) {
		if (fail) break;
		//食物被吃掉需要重新生成 
		if (reCreateFood) {
			createFood();
			reCreateFood = 0;
		}
		snakeMove();  //蛇的移动 
		Sleep(500);  //程序暂停500毫秒，注释掉运行一下就懂了
		//获取新的方向 
		d = getDirection();
	}

	//这个也是注释掉对比一下就懂了 
	Pos(0, 24);
	printf("\n");

	return 0;
}

void welcome() {
	system("mode con cols=100 lines=30");
	system("cls");

	Pos(38, 6);
	printf("欢迎来到贪吃蛇游戏\n");
	Pos(38, 8);
	printf("↑↓←→控制方向\n");
	Pos(45, 10);
	printf("ESC 退出\n");
	Pos(42, 12);
	printf("Enter 开始\n");
	getchar();
	system("cls");
}

void border() {  //创建以(0, 0), (59， 25)为顶点的矩形边界
	for (int i = 0; i < 60; i++) {
		Pos(i, 0);  //上行 
		printf("▇");
		Pos(i, 25);  //下行 
		printf("▇");
	}

	for (int i = 1; i < 25; i++) {
		Pos(0, i);  //左列 
		printf("▇");
		Pos(59, i);  //右列 
		printf("▇");
	}
}

void Pos(int x, int y) {
	COORD pos;  //位置坐标 
	pos.X = x;
	pos.Y = y;

	HANDLE handleOutput = GetStdHandle(STD_OUTPUT_HANDLE);  //获取输出句柄 
	SetConsoleCursorPosition(handleOutput, pos);   //定位 
}

void getRandomPos(int* x, int* y) {
	srand((unsigned int)time(NULL));
	*x = rand() % 58 + 1;
	*y = rand() % 24 + 1;
}

void initSnake() {
	head = (node*)malloc(sizeof(node));
	//保证在边界内
	head->x = rand() % 58 + 1;
	head->y = rand() % 24 + 1;
	head->next = NULL;

	Pos(head->x, head->y);
	printf("*");
}

void createFood() {
	int x, y;
	getRandomPos(&x, &y);
	if (inSnake(x, y)) createFood();  //重新生成
	food.x = x;
	food.y = y;
	Pos(x, y);
	printf("$");
}

int inSnake(int x, int y) {
	node* p = head->next;
	while (p) {  //从头遍历蛇身 
		if (x == p->x && y == p->y)
			return 1;
		p = p->next;
	}
	return 0;
}

void snakeMove() {
	//刚开局未按方向键的情况 
	if (d == -1)
		while (d == -1) d = getDirection();

	node* newHead = (node*)malloc(sizeof(node));
	newHead->x = head->x + dx[d];
	newHead->y = head->y + dy[d];
	newHead->next = head;
	head = newHead;

	node* p = head;
	if (inSnake(p->x, p->y) || (p->x == 0 || p->x == 59 || p->y == 0 || p->y == 25))
		fail = 1;
	else if (p->x != food.x || p->y != food.y) {
		Pos(p->x, p->y);
		printf("*");

		while (p->next->next) p = p->next;
		Pos(p->next->x, p->next->y);
		printf(" ");
		p->next = NULL;
	}
	else {
		reCreateFood = 1;
		score += add;
		Pos(p->x, p->y);
		printf("*");
	}
	Pos(61, 25);
	printf("您的得分为：%d", score);
}

int getDirection() {
	//不能往反方向走 
	if ((GetAsyncKeyState(VK_UP) & 0x8000) && d != 1) d = 0;
	else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && d != 0) d = 1;
	else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && d != 3) d = 2;
	else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && d != 2) d = 3;
	return d;
}

