#include<stdio.h>
#include<graphics.h>
#include<queue>
#include<iostream>
#define IMG_SIZE 39 //��һ������ͼƬ�Ŀ��
#define MEMBER_NUM 20 //�ܹ��Ķ�������
#define MAP_SIZE 8  //ÿ�ж��������
using namespace std;
IMAGE img_number[2];
IMAGE img_member[MEMBER_NUM][2];
//��ͼ
int map[MAP_SIZE + 2][MAP_SIZE + 2];
//�洢���ε����������±�
pair<int,int> Start = { -1, -1 }, End = { -1, -1 };
int flag = true;
//ƫ����
int dx[4] = { 0,-1,0,1 }, dy[4] = { -1,0,1,0 };
struct Node
{
	int x, y;
	int direct;
	int step;
};
//��Ϸ��ʼ��
void GameInit()
{
	//����һ��ͼ�δ��ڣ���ͼƬ
	initgraph(400, 400);
	//�������������
	srand(GetTickCount());
	loadimage(&img_number[0], "./image/animal.bmp");
	loadimage(&img_number[1], "./image/bk.jpg", 400, 400);
	//������ͼƬ���зָ���浽�µ�����
	SetWorkingImage(&img_number[0]);
	for (int i = 0; i < MEMBER_NUM; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			getimage(&img_member[i][j], j * IMG_SIZE, i * IMG_SIZE, IMG_SIZE, IMG_SIZE);
		}
	}
	SetWorkingImage();
	
	int temp = 1, count = 1;
	for (int i = 1; i <= MAP_SIZE; i++)
	{
		for (int j = 1; j <= MAP_SIZE; j++)
		{
			map[i][j] = temp;
			if (count % 8 == 0)
			{
				temp++;
			}
			count++;
		}
	}
	//����ͼƬ
	for (int i = 1; i <= MAP_SIZE; i++)
	{
		for (int j= 1; j <= MAP_SIZE; j++)
		{
			int temp = map[i][j];
			int row = rand() % 8 + 1;
			int col = rand() % 8 + 1;
			map[i][j] = map[row][col];
			map[row][col] = temp;
		}
	}
}
//��Ϸ�Ļ���
void GameDraw()
{
	putimage(0, 0, &img_number[1]);
	for (int i = 1; i <= MAP_SIZE; i++)
	{
		for (int j = 1; j <= MAP_SIZE; j++)
		{
			if (map[i][j] > 0)
			{
				putimage(j * IMG_SIZE, i * IMG_SIZE, &img_member[map[i][j]][1], SRCAND);
				putimage(j * IMG_SIZE, i * IMG_SIZE, &img_member[map[i][j]][0], SRCPAINT);
			}
		}
	}

}
//��������������ȡ�����Ϣ
void GameMouse()
{
	//����Ƿ���������
	if (MouseHit())
	{
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (flag == true)
			{
				//������ת��Ϊ�����±�
				Start.first = msg.y / IMG_SIZE;
				Start.second = msg.x / IMG_SIZE;
				flag = false;
			}
			else if (flag == false)
			{
				End.first = msg.y / IMG_SIZE;
				End.second = msg.x / IMG_SIZE;
				flag = true;
			}
			printf("begin(%d,%d),end(%d,%d)\n", Start.first, Start.second, End.first, End.second);
		}
	}
}

void show()
{
	for (int i = 0; i <= MAP_SIZE + 2; i++)
	{
		for (int j = 0; j <= MAP_SIZE + 2; j++)
		{
			printf("%d ", map[i][j]);

		}
		printf("\n");
	}

}
//ˮƽ�������Ƿ��ܹ�����
/*bool row(POINT Start, POINT End)
{
	//���ܵ��ͬһ��ͼƬ
	if (Start.x == End.x && Start.y == End.y)
	{
		return false;
	}
	//����Ƿ���ͬһˮƽ����
	if (Start.x != End.x)
	{
		return false;
	}
	//�����С
	int min = min(Start.y, End.y);
	int max = max(Start.y, End.y);
	//�ж�����ͼƬ֮���Ƿ�Ϊ��
	for (int i = min + 1; i < max; i++)
	{
		if (IsBlock(Start.x, i))
		{
			return false;
		}
	}
	return true;
}

//��ֱ�������Ƿ��ܹ�����
bool col(POINT Start, POINT End)
{
	//���ܵ��ͬһ��
	if (Start.x == End.x && Start.y == End.y)
	{
		return false;
	}
	//����Ƿ���ͬһ��ֱ����
	if (Start.y != End.y)
	{
		return false;
	}
	//�����С
	int min = min(Start.x, End.x);
	int max = max(Start.x, End.x);
	for (int i = min + 1; i < max; i++)
	{
		if (IsBlock(i, Start.y))
		{
			return false;
		}
	}
	return true;
}


//һ���սǼ��
bool turn_onecorner(POINT Start, POINT End)
{
	//���ܵ��ͬһ��
	if (Start.x == End.x && Start.y == End.y)
	{
		return false;
	}
	//���������ս���Ϣ
	POINT temp1 = { Start.x, End.y }, temp2 = { End.x, Start.y };
	if (!IsBlock(Start.x, End.y))
	{
		//ͨ��ˮƽ���ʹ�ֱ������ж��Ƿ��ܹ�����
		if (row(Start, temp1) && col(End, temp1))
		{
			return true;
		}
	}
	if (!IsBlock(End.x, Start.y))
	{
		if (row(End, temp2) && col(temp2, Start))
		{
			return true;
		}
	}
	return false;
}
*/

//�����սǼ�� ���� һ���սǼ�� �� һ��ˮƽ ���� ��ֱ���
/*bool turn_twocorner(POINT Start, POINT End)
{
	if (Start.x == End.x && Start.y == End.y)
	{
		return false;
	}
	//ˮƽ���
	POINT temp = { -1,-1 };
	//ˮƽ����ÿ���㣬���Ϊ�գ��ڽ���ˮƽ���͹սǼ��
	for (int y = 0; y <= MAP_SIZE + 1; y++)
	{
		if (y == Start.y)
			continue;
		if (!IsBlock(Start.x, y))
		{
			temp = { Start.x,y };

			if (row(Start, temp))
			{
				//�սǼ��
				if (turn_onecorner(temp, End))
				{
					return true;
				}
			}
		}
	}
	
	//��ֱ���
	POINT temp2 = { -1,-1 };
	//��ֱ����ÿ���㣬���Ϊ�գ��ٽ��д�ֱ���͹սǼ��
	for (int x = 0; x <= MAP_SIZE + 1; x++)
	{
		if (x == Start.x)
			continue;
		if (!IsBlock(x, Start.y))
		{
			temp2 = { x,Start.y };
			if (col(Start, temp2))
			{
				//�սǼ��
				if (turn_onecorner(temp2, End))
				{
					return true;
				}
			}
		}
	}
	return false;
}*/

bool bfs(pair<int,int> Start, pair<int,int> End)
{
	//��ͬ��λ�÷���false
	if (Start.first == End.first && Start.second == End.second)
	{
		return false;
	}
	//����λ��Ϊ�շ���false
	if (map[Start.first][Start.second] == 0 && map[End.first][End.second] == 0)
		return false;
	queue<Node>q;
	Node s, temp;
	s.x = Start.first;
	s.y = Start.second;
	//��ʼ����
	s.direct = -1;
	//ת�����
	s.step = 0;
	q.push(s);
	while (!q.empty())
	{
		temp = q.front();
		q.pop();
		if (temp.x == End.first && temp.y == End.second)
			return true;
		//�����ĸ�����
		for (int i = 0; i < 4; i++)
		{
			s = temp;
			s.x += dx[i];
			s.y += dy[i];
			//�����߽���������ѭ��
			if (s.x<0 || s.x>=MAP_SIZE + 2 || s.y < 0 || s.y >= MAP_SIZE + 2)
				continue;
			if (map[s.x][s.y] == 0||(s.x==End.first&&s.y==End.second))
			{
				if (s.direct != -1)
				{
					//˵��ת����
					if (s.direct != i)
					{
						s.direct = i;
						s.step++;
					}
				}
				else
					s.direct = i;
				if (s.step >= 3)
					continue;
				q.push(s);
			}
		}
	}
	return false;
}


int main()
{
	GameInit();
	show();
	BeginBatchDraw();
	while (1)
	{
		GameDraw();
		FlushBatchDraw();
		GameMouse();
		//��ͬ��ͼƬ��
		if (map[Start.first][Start.second] == map[End.first][End.second])
		{
			/*if (row(Start, End))
			{
				map[Start.x][Start.y] = 0;
				map[End.x][End.y] = 0;
			}
			else if (col(Start, End))
			{
				map[Start.x][Start.y] = 0;
				map[End.x][End.y] = 0;
			}
			else if (turn_onecorner(Start, End))
			{
				map[Start.x][Start.y] = 0;
				map[End.x][End.y] = 0;
			}
			else if (turn_twocorner(Start, End))
			{
				map[Start.x][Start.y] = 0;
				map[End.x][End.y] = 0;
			}*/
			if (bfs(Start, End))
			{
				map[Start.first][Start.second] = 0;
				map[End.first][End.second] = 0;
			}
		}
	}
	return 0;
}