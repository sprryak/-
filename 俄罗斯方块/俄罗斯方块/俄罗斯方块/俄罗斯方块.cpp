#include<stdio.h>
#include<graphics.h>
#include<time.h>
#include<conio.h>

#define BLOCKTYPE 16//方块种类
int g_block[BLOCKTYPE][4][4] =
{
	//l型
	{
		0,1,0,0,
		0,1,0,0,
		0,1,0,0,
		0,1,0,0
	},
	{
		0,0,0,0,
		1,1,1,1,
		0,0,0,0,
		0,0,0,0
	},
	{
		0,1,0,0,
		0,1,0,0,
		0,1,0,0,
		0,1,0,0
	},
	{
		0,0,0,0,
		1,1,1,1,
		0,0,0,0,
		0,0,0,0
	},
	//L型
	{
		0,1,0,0,
		0,1,0,0,
		0,1,1,0,
		0,0,0,0
	},
	{
		0,1,1,1,
		0,1,0,0,
		0,0,0,0,
		0,0,0,0
	},
	{
		0,1,1,0,
		0,0,1,0,
		0,0,1,0,
		0,0,0,0
	},
	{
		0,0,0,1,
		0,1,1,1,
		0,0,0,0,
		0,0,0,0
	},
	//山型
	{
		0,0,0,0,
		0,1,0,0,
		1,1,1,0,
		0,0,0,0
	},
	{
		0,1,0,0,
		0,1,1,0,
		0,1,0,0,
		0,0,0,0
	},
	{
		0,0,0,0,
		1,1,1,0,
		0,1,0,0,
		0,0,0,0
	},
	{
		0,1,0,0,
		1,1,0,0,
		0,1,0,0,
		0,0,0,0
	},
	//z型
	{
		0,0,0,0,
		0,1,1,0,
		0,0,1,1,
		0,0,0,0
	},
	{
		0,0,1,0,
		0,1,1,0,
		0,1,0,0,
		0,0,0,0
	},
	{
		0,0,0,0,
		0,1,1,0,
		0,0,1,1,
		0,0,0,0
	},
	{
		0,0,1,0,
		0,1,1,0,
		0,1,0,0,
		0,0,0,0
	}
};
int startX = 120, startY = 0;//初始坐标
int blockNow = 0;
int blockNext = 0;
//地图
int g_Map[30][15] = { 0 };
int score = 0;

//显示游戏界面
void GameView()
{
	char str[16];//存放分数
	initgraph(500, 630);
	rectangle(10, 10, 315, 615);
	rectangle(10, 10, 315, 615);
	rectangle(330, 10, 490, 170);
	settextstyle(24, 0, _T("宋体"));
	outtextxy(350, 180, "下一个方块");

	setcolor(RGB(255, 255, 255));
	outtextxy(385, 280, _T("分数"));
	sprintf_s(str, 16, "%d", score);
	outtextxy(400, 300, str);

	setcolor(CYAN);
	outtextxy(360, 450, "操作指示:");
	outtextxy(360, 480, "↑:旋转");
	outtextxy(360, 505, "↓:下降");
	outtextxy(360, 530, "←:左移");
	outtextxy(360, 555, "→:右移");
}

//显示方块
void ShowBlock(int blockID,int x,int y)
{
	BeginBatchDraw();
	setcolor(CYAN);
	settextstyle(20, 0, _T("楷体"));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (g_block[blockID][i][j] == 1)
			{
				outtextxy(11 + x + 20 * j, 11 + y + 20 * i, "■");
			}
		}
	}
	EndBatchDraw();
}
//清除方块
void ClearBlock(int blockID,int x,int y)
{
	BeginBatchDraw();
	setcolor(BLACK);
	//settextstyle(20, 0, _T("楷体"));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (g_block[blockID][i][j] == 1)
			{
				outtextxy(11 + x + 20 * j, 11 + y + 20 * i, "■");
			}
		}
	}
	EndBatchDraw();
}

//判断是否触底
int IsDown(int blockID)
{
	int i = 0, j = 0;
	int y = 0;
	int m = 0, n = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (g_block[blockNow][i][j] == 1)
			{
				y = startY + 20 * i;//y是每个小方块的y坐标

				m = startY / 20 + i;
				n = startX / 20 + j;

				if (y == 580 || g_Map[m+1][n] == 1)//下一个位置有方块
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

//标记地图
void MarkMap()
{
	int i = 0, j = 0;
	int m = 0, n = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (g_block[blockNow][i][j] == 1)
			{
				m = startY / 20 + i;//每个方块相应的行
				n = startX / 20 + j;//每个方块相应的列
				g_Map[m][n] = 1;
			}
		}
	}
}

//判断是否超出左边界
int LeftCheck(int blockID)
{
	int i = 0, j = 0;
	int x = 0;
	int m = 0, n = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (g_block[blockID][i][j] == 1)
			{
				x = startX + 20 * j;

				m = startY / 20 + i;//每个方块对应地图的列
				n = startX / 20 + j;//每个方块对应地图的行
				if (x == 0||g_Map[m][n-1]==1)
					return 1;
			}
		}
	}
	return 0;
}

//判断是否超出右边界
int RightCheck(int blockID)
{
	int i = 0, j = 0;
	int x = 0;
	int m = 0, n = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (g_block[blockNow][i][j] == 1)
			{
				x = startX + 20 * j;
				m = startY / 20 + i;
				n = startX / 20 + j;
				if (x == 280 || g_Map[m][n+1] == 1)
					return 1;
			}
		}
	}
	return 0;
}

//判断是否死亡
int IsDie()
{
	for (int j = 0; j < 15; j++)
	{
		if (g_Map[0][j] == 1)
		{
			return 1;
		}
	}
	return 0;
}

//消除行
void ClearLine()
{
	int flag = 0;
	int i = 0;
	int j = 0;
	for (i = 29; i >= 0; i--)
	{
		for (j = 0; j < 15; j++)
		{
			if (g_Map[i][j] == 0)//如果有一个为空，就不需要消除行，直接退出
			{
				break;
			}
		}
		//说明这行需要消除
		if (j == 15)
		{
			char str[16];
			score += 10;
			sprintf_s(str, 16, "%d", score);
			setcolor(WHITE);
			outtextxy(400, 300, str);
			flag = 1;
			int m = 0, n = 0;
			//int score=0;
			for ( m = i; m > 0; m--)
			{
				for ( n = 0; n < 15; n++)
				{
					g_Map[m][n] = g_Map[m - 1][n];
				}
			}
			i++;
		}
	}
	//重新绘制
	if (flag == 1)
	{
		for (i = 0; i < 30; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (g_Map[i][j] == 1)
				{
					setcolor(CYAN);
				}
				else
				{
					setcolor(BLACK);
				}
				outtextxy(11 + 20 * j, 11 + 20 * i, "■");
			}
		}
	}
}

void KeyControl()
{
	if (_kbhit())	
	{
		_getch();
		if (GetAsyncKeyState(VK_LEFT))
		{
			if (!LeftCheck(blockNow))
			{
				startX -= 20;
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			if (!RightCheck(blockNow))
			{
				startX += 20;
			}
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			int blockid = 0;

			if (blockNow % 4 == 3)
			{
				blockid = blockNow - 3;
			}
			else
			{
				blockid = blockNow + 1;
			}
			if (!LeftCheck(blockid)&&!RightCheck(blockid)&&!IsDown(blockid))
			{
				blockNow = blockid;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			if (!IsDown(blockNow))//先判断是否触底，没触底再变化y坐标
			{
				startY += 20;
			}
		}
	}
}

void GameRun()
{
	//清除地图
	memset(g_Map, 0, sizeof(g_Map));
	srand(time(NULL));
	blockNow = rand() % BLOCKTYPE;
	blockNext = rand() % BLOCKTYPE;
	//显示下一个方块
	ShowBlock(blockNext,350,50);
	while (1)
	{
		if (IsDown(blockNow) == 1)//触底
		{
			MarkMap();
			//ShowMap();
			ClearLine();
			if (IsDie())
			{
				outtextxy(120, 200, "游戏结束");
				Sleep(3000);
				break;
			}
			//回到最开头的起始坐标
			startY = 0;
			startX = 120;

			//更新当前方块
			blockNow = blockNext;

			//更新下一个方块
			ClearBlock(blockNext, 350, 50);
			blockNext = rand() % BLOCKTYPE;
			ShowBlock(blockNext, 350, 50);
		}
		else//没有触底
		{
			ClearBlock(blockNow,startX,startY);
			startY += 20;
			//ShowBlock(blockNow, startX, startY);
		}
		KeyControl();
		ShowBlock(blockNow, startX, startY);
		Sleep(150);
	}
}
int main()
{
	while (1)
	{
		GameView();
		GameRun();
	}
}