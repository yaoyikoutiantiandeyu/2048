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

int score, score_i;
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

	//       
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
	char text[11] = "2048С  Ϸ";
	settextcolor(RGB(19, 20, 28));
	settextstyle(50, 0, "    ");
	setbkmode(TRANSPARENT);
	tempx = (MAX_GRID * GRID_WIDTH + MAX_INTERVAL * INTERVAL_WIDTH + 100) / 2 - textwidth(text) / 2;
	outtextxy(tempx, 25, text);

	setfillcolor(RGB(165, 141, 117));
	solidrectangle(50, 100, 150, 140);
	char texta[9] = "        ";
	settextcolor(RGB(237, 228, 218));
	settextstyle(15, 0, "    ");
	setbkmode(TRANSPARENT);
	tempx = 50 - textwidth(texta) / 2;
	outtextxy(50 + tempx, 105, texta);

	setfillcolor(RGB(165, 141, 117));
	solidrectangle(160, 100, 260, 140);
	char textb[9] = "  ߼ ¼";
	settextcolor(RGB(237, 228, 218));
	settextstyle(15, 0, "    ");
	setbkmode(TRANSPARENT);
	tempx = 50 - textwidth(textb) / 2;
	outtextxy(160 + tempx, 105, textb);

	setfillcolor(RGB(165, 141, 117));
	solidrectangle(300, 100, 525, 140);
	char textc[28] = "ʹ                      ƶ ";
	settextcolor(RGB(237, 228, 218));
	settextstyle(15, 0, "    ");
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
	settextstyle(15, 0, "    ");
	setbkmode(TRANSPARENT);
	tempx = 50 - textwidth(Score) / 2;
	outtextxy(50 + tempx, 125, Score);

	setfillcolor(RGB(165, 141, 117));
	solidrectangle(160, 125, 260, 140);
	char SCore[6];
	itoa(score_i, SCore, 10);
	settextcolor(RGB(255, 255, 255));
	settextstyle(15, 0, "    ");
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
						settextstyle(50, 0, "    ");
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
	cleardevice();//    
	IMAGE img1;
	loadimage(&img1, "1.jpg", 480, 680); //     ͼƬ
	putimage(0, 0, &img1); //   (x, y)λ    ʾͼƬ

	setfont(50, 0, "     кڼ   ");//        
	RECT r1 = { 0,0,WIDTH,HEIGHT / 3 };
	drawtext("  ӭ    2048      ", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setbkcolor(RGB(0, 0, 0));
	setbkmode(TRANSPARENT);
	setfont(30, 0, "Microsoft Yahei Ul Boid");
	solidroundrect(146, 140, 188, 170, 10, 10);//Բ      
	solidroundrect(78, 140, 118, 170, 10, 10);//Բ      

	setfont(30, 0, "΢   ź ");
	RECT r2 = { WIDTH / 2 - 45,HEIGHT / 3,WIDTH / 2 + 45,HEIGHT / 3 + 30 };
	drawtext("  ʼ  Ϸ", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r5 = { WIDTH / 2 - 45,HEIGHT / 3 + 90,WIDTH / 2 + 45,HEIGHT / 3 + 120 };
	drawtext(" ˳   Ϸ", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setfillcolor(RGB(230, 60, 50));//   õ ǰ       ɫ

	setfont(30, 0, "Microsoft Yahei UI Bold");//        

	char sq[] = "   ߣ 13  ";
	outtextxy(180, 440, sq);
	settextcolor(WHITE);//      ɫ
	char sbq[] = "  ܰ    : ˽               ";
	outtextxy(75, 520, sbq);
	settextcolor(RGB(150, 126, 104));
	//setbkcolor(RGB(244, 186, 1));
	setbkmode(TRANSPARENT);
	solidroundrect(146, 140, 188, 170, 10, 10);//Բ      
	solidroundrect(78, 140, 118, 170, 10, 10);//Բ      
	setbkcolor(RGB(150, 126, 104));
	setfont(30, 0, "Microsoft Yahei UI Bold");//        
	char wq[] = "    :       /        ";
	outtextxy(20, 140, wq);
}


//ѯ   Ƿ         
//    :ֱ ӿ ʼ
//    : ص   ʼ    (ͬʱ      ߷   )

void Menu()
{
	initgraph(WIDTH, HEIGHT);//    
	setbkcolor(RGB(251, 248, 241));//    
	settextcolor(RGB(150, 126, 104));

	initgraph(WIDTH, HEIGHT); //   ʼ  ͼ δ  ڣ ֻ    һ  
	BeginBatchDraw(); //   ʼ      ͼģʽ

	while (1) {
		Show1(); //   ʾ    
		FlushBatchDraw(); //         ͼ             Ļ

		MOUSEMSG msg;
		if (MouseHit()) { //     Ƿ       ¼ 
			msg = GetMouseMsg(); //   ȡ    ¼ 
			if (msg.uMsg == WM_LBUTTONDOWN) { //     Ƿ Ϊ      
				//  жϵ  λ   Ƿ  ڡ   ʼ  Ϸ    ť  
				if (msg.x > WIDTH / 2 - 45 && msg.x < WIDTH / 2 + 45 && msg.y > HEIGHT / 3 && msg.y < HEIGHT / 3 + 30) {
					EndBatchDraw(); //           ͼģʽ
					Start(); //   ʼ  Ϸ
					// 
				}
				//  жϵ  λ   Ƿ  ڡ  ˳   Ϸ    ť  
				else if (msg.x > WIDTH / 2 - 45 && msg.x < WIDTH / 2 + 45 && msg.y > HEIGHT / 3 + 90 && msg.y < HEIGHT / 3 + 120) {
					closegraph(); //  ر ͼ δ   
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

	cleardevice();//    
	IMAGE img2;
	loadimage(&img2, "2.jpg", 480, 680); //     ͼƬ
	putimage(0, 0, &img2); //   (x, y)λ    ʾͼƬ

	settextcolor(RED);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, "    ");
	outtextxy(140, 150, ("  Ϸ    "));

	settextcolor(BLACK);
	settextstyle(25, 0, ("    "));
	setbkmode(TRANSPARENT);
	outtextxy(155, 300, ("    R/r   ¿ ʼ"));
	setbkmode(TRANSPARENT);
	outtextxy(142, 400, ("    S/s          "));
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
	mciSendString("close \"2.mp3", NULL, 0, NULL);  // ȷ   ļ     ȷ
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