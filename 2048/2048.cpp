#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")

#define WIDTH 480
#define HEIGHT 680
#define MAX_GRID 4
#define GRID_WIDTH 100
#define MAX_INTERVAL 5
#define INTERVAL_WIDTH 15

#define REVERSE(m, n) \
    (m ^= n);         \
    (n ^= m);         \
    (m ^= n)

int score,score_i;
FILE* fpr = fopen("score.txt", "r");



enum Colorset
{
	two0 = RGB(204, 193, 180),
	two1 = RGB(237, 228, 218),
	two2 = RGB(236, 224, 201),
	two3 = RGB(237, 178, 123),
	two4 = RGB(239, 150, 102),
	two5 = RGB(239, 125, 98),
	two6 = RGB(238, 96, 64),
	two7 = RGB(234, 208, 117),
	two8 = RGB(233, 205, 101),
	two9 = RGB(233, 201, 85),
	two10 = RGB(233, 198, 69),
	two11 = RGB(242, 17, 158),
	background = RGB(227, 218, 208),
};
Colorset arr[13] = { two0, two1, two2, two3, two4, two5, two6, two7, two8, two9, two10, two11, background };

int num[12] = { 0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 };
int content[MAX_GRID][MAX_GRID];
POINT pos[MAX_GRID][MAX_GRID];

int tempx, tempy;
int condition = 0;

char Judge() {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (content[i][j] == 0 || content[i][j] == content[i][j + 1] || content[i][j + 1] == 0)
				return 1;
		}
	}

	// 纵向检测
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (content[j][i] == 0 || content[j][i] == content[j + 1][i] || content[j + 1][i] == 0)
				return 1;
		}
	}

	return 0;
}


int GenerateNumber()
{
	if (rand() % 10 == 1)
	{
		return 4;
	}
	else
	{
		return 2;
	}
}

void GeneratePosition()
{
	int x, y;
	do
	{
		x = rand() % MAX_GRID;
		y = rand() % MAX_GRID;
	} while (content[x][y] != 0);

	content[x][y] = GenerateNumber();
}

void GameInit()
{
	setbkcolor(background);
	cleardevice();

	setfillcolor(RGB(186, 173, 160));
	solidrectangle(50, 150, MAX_GRID * GRID_WIDTH + MAX_INTERVAL * INTERVAL_WIDTH + 50, MAX_GRID * GRID_WIDTH + MAX_INTERVAL * INTERVAL_WIDTH + 150);
	char text[11] = "2048小游戏";
	settextcolor(RGB(19, 20, 28));
	settextstyle(50, 0, "黑体");
	setbkmode(TRANSPARENT);
	tempx = (MAX_GRID * GRID_WIDTH + MAX_INTERVAL * INTERVAL_WIDTH + 100) / 2 - textwidth(text) / 2;
	outtextxy(tempx, 25, text);

	setfillcolor(RGB(165, 141, 117));
	solidrectangle(50, 100, 150, 140);
	char texta[9] = "本场分数";
	settextcolor(RGB(237, 228, 218));
	settextstyle(15, 0, "黑体");
	setbkmode(TRANSPARENT);
	tempx = 50 - textwidth(texta) / 2;
	outtextxy(50 + tempx, 105, texta);

	setfillcolor(RGB(165, 141, 117));
	solidrectangle(160, 100, 260, 140);
	char textb[9] = "最高纪录";
	settextcolor(RGB(237, 228, 218));
	settextstyle(15, 0, "黑体");
	setbkmode(TRANSPARENT);
	tempx = 50 - textwidth(textb) / 2;
	outtextxy(160 + tempx, 105, textb);

	setfillcolor(RGB(165, 141, 117));
	solidrectangle(300, 100, 525, 140);
	char textc[28] = "使用 ↑ ↓ ← → 键进行移动";
	settextcolor(RGB(237, 228, 218));
	settextstyle(15, 0, "黑体");
	setbkmode(TRANSPARENT);
	tempx = 113 - textwidth(textc) / 2;
	outtextxy(300 + tempx, 113, textc);

	for (int i = 0; i < MAX_GRID; i++)
	{
		for (int j = 0; j < MAX_GRID; j++)
		{
			pos[i][j].x = j * GRID_WIDTH + (j + 1) * INTERVAL_WIDTH + 50;
			pos[i][j].y = i * GRID_WIDTH + (i + 1) * INTERVAL_WIDTH + 150;
		}
	}

	srand((unsigned int)time(NULL));
	GeneratePosition();
	GeneratePosition();
}


void GameDraw()
{
	setfillcolor(RGB(165, 141, 117));
	solidrectangle(50, 125, 150, 140);
	char Score[6];
	itoa(score, Score, 10);
	settextcolor(RGB(255, 255, 255));
	settextstyle(15, 0, "黑体");
	setbkmode(TRANSPARENT);
	tempx = 50 - textwidth(Score) / 2;
	outtextxy(50 + tempx, 125, Score);

	setfillcolor(RGB(165, 141, 117));
	solidrectangle(160, 125, 260, 140);
	char SCore[6];
	itoa(score_i, SCore, 10);
	settextcolor(RGB(255, 255, 255));
	settextstyle(15, 0, "黑体");
	setbkmode(TRANSPARENT);
	tempx = 50 - textwidth(SCore) / 2;
	outtextxy(160 + tempx, 125, SCore);

	for (int i = 0; i < MAX_GRID; i++)
	{
		for (int j = 0; j < MAX_GRID; j++)
		{
			for (int k = 0; k < 12; k++)
			{
				if (content[i][j] == num[k])
				{
					setfillcolor(arr[k]);
					solidrectangle(pos[i][j].x, pos[i][j].y, pos[i][j].x + GRID_WIDTH, pos[i][j].y + GRID_WIDTH);

					if (content[i][j] != 0)
					{
						char number[5] = " ";
						settextcolor(RGB(119, 110, 101));
						settextstyle(50, 0, "楷体");
						setbkmode(TRANSPARENT);
						sprintf(number, "%d", content[i][j]);

						tempx = GRID_WIDTH / 2 - textwidth(number) / 2;
						tempy = GRID_WIDTH / 2 - textheight(number) / 2;
						outtextxy(pos[i][j].x + tempx, pos[i][j].y + tempy, number);
					}
				}
			}
		}
	}
}

void Upmoving()
{
	for (int j = 0; j < MAX_GRID; j++)
	{
		for (int i = 1; i < MAX_GRID; i++)
		{
			if (!content[i - 1][j] && content[i][j])
			{
				REVERSE(content[i - 1][j], content[i][j]);
				condition = 1;
			}
		}

		for (int i = 1; i < MAX_GRID; i++)
		{
			if (!content[i - 1][j] && content[i][j])
			{
				REVERSE(content[i - 1][j], content[i][j]);
				condition = 1;
			}
		}

		for (int i = 1; i < MAX_GRID; i++)
		{
			if (content[i - 1][j] == content[i][j] && content[i - 1][j])
			{
				content[i - 1][j] <<= 1;
				score += content[i - 1][j];
				content[i][j] = 0;
				condition = 1;
			}
		}

		for (int i = 1; i < MAX_GRID; i++)
		{
			if (!content[i - 1][j] && content[i][j])
			{
				REVERSE(content[i - 1][j], content[i][j]);
				condition = 1;
			}
		}
	}

	printf("up\n");
}

void Downmoving()
{
	for (int j = 0; j < MAX_GRID; j++)
	{
		for (int i = MAX_GRID - 2; i >= 0; i--)
		{
			if (content[i][j] && !content[i + 1][j])
			{
				REVERSE(content[i + 1][j], content[i][j]);
				condition = 1;
			}
		}

		for (int i = MAX_GRID - 2; i >= 0; i--)
		{
			if (content[i][j] && !content[i + 1][j])
			{
				REVERSE(content[i + 1][j], content[i][j]);
				condition = 1;
			}
		}

		for (int i = MAX_GRID - 2; i >= 0; i--)
		{
			if (content[i][j] == content[i + 1][j] && content[i + 1][j])
			{
				content[i + 1][j] <<= 1;
				score += content[i + 1][j];
				content[i][j] = 0;
				condition = 1;
			}
		}

		for (int i = MAX_GRID - 2; i >= 0; i--)
		{
			if (content[i][j] && !content[i + 1][j])
			{
				REVERSE(content[i + 1][j], content[i][j]);
				condition = 1;
			}
		}
	}

	printf("down\n");
}

void Leftmoving()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		for (int j = 1; j < MAX_GRID; j++)
		{
			if (!content[i][j - 1] && content[i][j])
			{
				REVERSE(content[i][j - 1], content[i][j]);
				condition = 1;
			}
		}

		for (int j = 1; j < MAX_GRID; j++)
		{
			if (!content[i][j - 1] && content[i][j])
			{
				REVERSE(content[i][j - 1], content[i][j]);
				condition = 1;
			}
		}

		for (int j = 1; j < MAX_GRID; j++)
		{
			if (content[i][j - 1] == content[i][j] && content[i][j - 1])
			{
				content[i][j - 1] <<= 1;
				score += content[i][j - 1];
				content[i][j] = 0;
				condition = 1;
			}
		}

		for (int j = 1; j < MAX_GRID; j++)
		{
			if (!content[i][j - 1] && content[i][j])
			{
				REVERSE(content[i][j - 1], content[i][j]);
				condition = 1;
			}
		}
	}

	printf("left\n");
}

void Rightmoving()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		for (int j = MAX_GRID - 2; j >= 0; j--)
		{
			if (content[i][j] && !content[i][j + 1])
			{
				REVERSE(content[i][j], content[i][j + 1]);
				condition = 1;
			}
		}

		for (int j = MAX_GRID - 2; j >= 0; j--)
		{
			if (content[i][j] && !content[i][j + 1])
			{
				REVERSE(content[i][j], content[i][j + 1]);
				condition = 1;
			}
		}

		for (int j = MAX_GRID - 2; j >= 0; j--)
		{
			if (content[i][j] == content[i][j + 1] && content[i][j + 1])
			{
				content[i][j + 1] <<= 1;
				score += content[i][j + 1];
				content[i][j] = 0;
				condition = 1;
			}
		}

		for (int j = MAX_GRID - 2; j >= 0; j--)
		{
			if (content[i][j] && !content[i][j + 1])
			{
				REVERSE(content[i][j], content[i][j + 1]);
				condition = 1;
			}
		}
	}

	printf("right\n");
}

void MoveOrNot()
{
	if (condition == 1)
	{
		GeneratePosition();
		condition = 0;
	}
}


void GameControl()
{
	char direction = getch();

	switch (direction)
	{
	case 72:
		Upmoving();
		break;
	case 80:
		Downmoving();
		break;
	case 75:
		Leftmoving();
		break;
	case 77:
		Rightmoving();
		break;
	}
}


void Start()
{
	void Check();
	score = 0;

	initgraph(MAX_GRID * GRID_WIDTH + MAX_INTERVAL * INTERVAL_WIDTH + 100, MAX_GRID * GRID_WIDTH + MAX_INTERVAL * INTERVAL_WIDTH + 150);
	GameInit();
	GameDraw();
	while (Judge())
	{
		GameControl();
		MoveOrNot();
		GameDraw();
	}

	if (score > score_i) {
		score_i = score;
		FILE* fpw = fopen("score.txt", "w");
		fprintf(fpw, "%d", score_i);
	}

	for (int i = 0;i < 4;++i)
		for (int j = 0;j < 4;++j) {
			content[i][j] = 0;
		}

	Check();

}

void Show1()
{
	cleardevice();//清屏
	IMAGE img1;
	loadimage(&img1, "1.jpg", 480, 680); // 加载图片
	putimage(0, 0, &img1); // 在(x, y)位置显示图片

	setfont(50, 0, "方正行黑简体");//字体设置
	RECT r1 = { 0,0,WIDTH,HEIGHT / 3 };
	drawtext("欢迎来到2048的世界", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setbkcolor(RGB(0, 0, 0));
	setbkmode(TRANSPARENT);
	setfont(30, 0, "Microsoft Yahei Ul Boid");
	solidroundrect(146, 140, 188, 170, 10, 10);//圆角梯形
	solidroundrect(78, 140, 118, 170, 10, 10);//圆角梯形

	setfont(30, 0, "微软雅黑");
	RECT r2 = { WIDTH / 2 - 45,HEIGHT / 3,WIDTH / 2 + 45,HEIGHT / 3 + 30 };
	drawtext("开始游戏", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r5 = { WIDTH / 2 - 45,HEIGHT / 3 + 90,WIDTH / 2 + 45,HEIGHT / 3 + 120 };
	drawtext("退出游戏", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setfillcolor(RGB(230, 60, 50));//设置当前的填充颜色

	setfont(30, 0, "Microsoft Yahei UI Bold");//设置字体

	char sq[] = "作者：13组";
	outtextxy(180, 440, sq);
	settextcolor(WHITE);//字体颜色
	char sbq[] = "温馨提醒:此界面均用鼠标左键点击";
	outtextxy(75, 520, sbq);
	settextcolor(RGB(150, 126, 104));
	//setbkcolor(RGB(244, 186, 1));
	setbkmode(TRANSPARENT);
	solidroundrect(146, 140, 188, 170, 10, 10);//圆角梯形
	solidroundrect(78, 140, 118, 170, 10, 10);//圆角梯形
	setbkcolor(RGB(150, 126, 104));
	setfont(30, 0, "Microsoft Yahei UI Bold");//设置字体
	char wq[] = "音乐:   开  /   关   ";
	outtextxy(20, 140, wq);
}


//询问是否继续或结束
//继续:直接开始
//结束:回到开始界面(同时更新最高分数)

void Menu()
{
	initgraph(WIDTH, HEIGHT);//长宽
	setbkcolor(RGB(251, 248, 241));//背景
	settextcolor(RGB(150, 126, 104));

	initgraph(WIDTH, HEIGHT); // 初始化图形窗口，只调用一次
	BeginBatchDraw(); // 开始批量绘图模式

	while (1) {
		Show1(); // 显示界面
		FlushBatchDraw(); // 将批量绘图的内容输出到屏幕

		MOUSEMSG msg;
		if (MouseHit()) { // 检查是否有鼠标事件
			msg = GetMouseMsg(); // 获取鼠标事件
			if (msg.uMsg == WM_LBUTTONDOWN) { // 检查是否为左键点击
				// 判断点击位置是否在“开始游戏”按钮上
				if (msg.x > WIDTH / 2 - 45 && msg.x < WIDTH / 2 + 45 && msg.y > HEIGHT / 3 && msg.y < HEIGHT / 3 + 30) {
					EndBatchDraw(); // 结束批量绘图模式
					Start(); // 开始游戏
					// 
				}
				// 判断点击位置是否在“退出游戏”按钮上
				else if (msg.x > WIDTH / 2 - 45 && msg.x < WIDTH / 2 + 45 && msg.y > HEIGHT / 3 + 90 && msg.y < HEIGHT / 3 + 120) {
					closegraph(); // 关闭图形窗口
				}
				else if (msg.x > 78 && msg.x < 118 && msg.y>140 && msg.y < 170)
				{
					mciSendString("open \"2.mp3\" alias music", NULL, 0, NULL);
					mciSendString("play music repeat", NULL, 0, NULL);
				}
				else if (msg.x > 148 && msg.x < 188 && msg.y>140 && msg.y < 170)
				{
					mciSendString("close music", NULL, 0, NULL);
				}

			}
		}
	}

	EndBatchDraw();
	closegraph();
}

void Check()
{
	
	initgraph(WIDTH, HEIGHT);
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 0, 480, 680);

	cleardevice();//清屏
	IMAGE img2;
	loadimage(&img2, "2.jpg", 480, 680); // 加载图片
	putimage(0, 0, &img2); // 在(x, y)位置显示图片

	settextcolor(RED);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, "黑体");
	outtextxy(140, 150, ("游戏结束"));

	settextcolor(BLACK);
	settextstyle(25, 0, ("黑体"));
	setbkmode(TRANSPARENT);
	outtextxy(155, 300, ("输入R/r重新开始"));
	setbkmode(TRANSPARENT);
	outtextxy(142, 400, ("输入S/s返回主界面"));
	while (1) {
		switch (getch()) {
		case 82://R
		case 114:
			Start();
			break;
		case 83://S
		case 115:
			Menu();
			break;
		default:
			Check();
		}

	}
	EndBatchDraw();
	closegraph();
}

int main(void) {
	mciSendString("close \"2.mp3", NULL, 0, NULL);  // 确保文件名正确
	if (mciSendString("open \"2.mp3\" alias music", NULL, 0, NULL) == 0) {
		mciSendString("play music repeat", NULL, 0, NULL);
	}
	else {
		printf("Failed to open music file.\n");
	}
	fscanf(fpr, "%d", &score_i);
	Menu();

	return 0;
}