#include<stdio.h>
#include<graphics.h>
#include<time.h>
#include<conio.h>

#define BLOCKTYPE 16//��������
int g_block[BLOCKTYPE][4][4] =
{
	//l��
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
	//L��
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
	//ɽ��
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
	//z��
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
int startX = 120, startY = 0;//��ʼ����
int blockNow = 0;
int blockNext = 0;
//��ͼ
int g_Map[30][15] = { 0 };
int score = 0;

//��ʾ��Ϸ����
void GameView()
{
	char str[16];//��ŷ���
	initgraph(500, 630);
	rectangle(10, 10, 315, 615);
	rectangle(10, 10, 315, 615);
	rectangle(330, 10, 490, 170);
	settextstyle(24, 0, _T("����"));
	outtextxy(350, 180, "��һ������");

	setcolor(RGB(255, 255, 255));
	outtextxy(385, 280, _T("����"));
	sprintf_s(str, 16, "%d", score);
	outtextxy(400, 300, str);

	setcolor(CYAN);
	outtextxy(360, 450, "����ָʾ:");
	outtextxy(360, 480, "��:��ת");
	outtextxy(360, 505, "��:�½�");
	outtextxy(360, 530, "��:����");
	outtextxy(360, 555, "��:����");
}

//��ʾ����
void ShowBlock(int blockID,int x,int y)
{
	BeginBatchDraw();
	setcolor(CYAN);
	settextstyle(20, 0, _T("����"));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (g_block[blockID][i][j] == 1)
			{
				outtextxy(11 + x + 20 * j, 11 + y + 20 * i, "��");
			}
		}
	}
	EndBatchDraw();
}
//�������
void ClearBlock(int blockID,int x,int y)
{
	BeginBatchDraw();
	setcolor(BLACK);
	//settextstyle(20, 0, _T("����"));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (g_block[blockID][i][j] == 1)
			{
				outtextxy(11 + x + 20 * j, 11 + y + 20 * i, "��");
			}
		}
	}
	EndBatchDraw();
}

//�ж��Ƿ񴥵�
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
				y = startY + 20 * i;//y��ÿ��С�����y����

				m = startY / 20 + i;
				n = startX / 20 + j;

				if (y == 580 || g_Map[m+1][n] == 1)//��һ��λ���з���
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

//��ǵ�ͼ
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
				m = startY / 20 + i;//ÿ��������Ӧ����
				n = startX / 20 + j;//ÿ��������Ӧ����
				g_Map[m][n] = 1;
			}
		}
	}
}

//�ж��Ƿ񳬳���߽�
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

				m = startY / 20 + i;//ÿ�������Ӧ��ͼ����
				n = startX / 20 + j;//ÿ�������Ӧ��ͼ����
				if (x == 0||g_Map[m][n-1]==1)
					return 1;
			}
		}
	}
	return 0;
}

//�ж��Ƿ񳬳��ұ߽�
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

//�ж��Ƿ�����
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

//������
void ClearLine()
{
	int flag = 0;
	int i = 0;
	int j = 0;
	for (i = 29; i >= 0; i--)
	{
		for (j = 0; j < 15; j++)
		{
			if (g_Map[i][j] == 0)//�����һ��Ϊ�գ��Ͳ���Ҫ�����У�ֱ���˳�
			{
				break;
			}
		}
		//˵��������Ҫ����
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
	//���»���
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
				outtextxy(11 + 20 * j, 11 + 20 * i, "��");
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
			if (!IsDown(blockNow))//���ж��Ƿ񴥵ף�û�����ٱ仯y����
			{
				startY += 20;
			}
		}
	}
}

void GameRun()
{
	//�����ͼ
	memset(g_Map, 0, sizeof(g_Map));
	srand(time(NULL));
	blockNow = rand() % BLOCKTYPE;
	blockNext = rand() % BLOCKTYPE;
	//��ʾ��һ������
	ShowBlock(blockNext,350,50);
	while (1)
	{
		if (IsDown(blockNow) == 1)//����
		{
			MarkMap();
			//ShowMap();
			ClearLine();
			if (IsDie())
			{
				outtextxy(120, 200, "��Ϸ����");
				Sleep(3000);
				break;
			}
			//�ص��ͷ����ʼ����
			startY = 0;
			startX = 120;

			//���µ�ǰ����
			blockNow = blockNext;

			//������һ������
			ClearBlock(blockNext, 350, 50);
			blockNext = rand() % BLOCKTYPE;
			ShowBlock(blockNext, 350, 50);
		}
		else//û�д���
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