#include<stdio.h>
#include<graphics.h>
#include<queue>
#include<iostream>
#define IMG_SIZE 39 //隔一个动物图片的宽度
#define MEMBER_NUM 20 //总共的动物数量
#define MAP_SIZE 8  //每行动物的数量
using namespace std;
IMAGE img_number[2];
IMAGE img_member[MEMBER_NUM][2];
//地图
int map[MAP_SIZE + 2][MAP_SIZE + 2];
//存储两次点击的数组的下标
pair<int,int> Start = { -1, -1 }, End = { -1, -1 };
int flag = true;
//偏移量
int dx[4] = { 0,-1,0,1 }, dy[4] = { -1,0,1,0 };
struct Node
{
	int x, y;
	int direct;
	int step;
};
//游戏初始化
void GameInit()
{
	//创建一个图形窗口，贴图片
	initgraph(400, 400);
	//设置随机数种子
	srand(GetTickCount());
	loadimage(&img_number[0], "./image/animal.bmp");
	loadimage(&img_number[1], "./image/bk.jpg", 400, 400);
	//把整个图片进行分割，保存到新的数组
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
	//打乱图片
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
//游戏的绘制
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
//鼠标控制消除，获取鼠标消息
void GameMouse()
{
	//检测是否有鼠标操作
	if (MouseHit())
	{
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (flag == true)
			{
				//把坐标转化为数组下标
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
//水平方向检测是否能够消除
/*bool row(POINT Start, POINT End)
{
	//不能点击同一个图片
	if (Start.x == End.x && Start.y == End.y)
	{
		return false;
	}
	//检测是否在同一水平方向
	if (Start.x != End.x)
	{
		return false;
	}
	//求出大小
	int min = min(Start.y, End.y);
	int max = max(Start.y, End.y);
	//判断两个图片之间是否都为空
	for (int i = min + 1; i < max; i++)
	{
		if (IsBlock(Start.x, i))
		{
			return false;
		}
	}
	return true;
}

//垂直方向检测是否能够消除
bool col(POINT Start, POINT End)
{
	//不能点击同一个
	if (Start.x == End.x && Start.y == End.y)
	{
		return false;
	}
	//检测是否在同一垂直方向
	if (Start.y != End.y)
	{
		return false;
	}
	//求出大小
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


//一个拐角检测
bool turn_onecorner(POINT Start, POINT End)
{
	//不能点击同一个
	if (Start.x == End.x && Start.y == End.y)
	{
		return false;
	}
	//保存两个拐角信息
	POINT temp1 = { Start.x, End.y }, temp2 = { End.x, Start.y };
	if (!IsBlock(Start.x, End.y))
	{
		//通过水平检测和垂直检测来判断是否能够消除
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

//两个拐角检测 等于 一个拐角检测 加 一个水平 或者 竖直检测
/*bool turn_twocorner(POINT Start, POINT End)
{
	if (Start.x == End.x && Start.y == End.y)
	{
		return false;
	}
	//水平检测
	POINT temp = { -1,-1 };
	//水平遍历每个点，如果为空，在进行水平检测和拐角检测
	for (int y = 0; y <= MAP_SIZE + 1; y++)
	{
		if (y == Start.y)
			continue;
		if (!IsBlock(Start.x, y))
		{
			temp = { Start.x,y };

			if (row(Start, temp))
			{
				//拐角检测
				if (turn_onecorner(temp, End))
				{
					return true;
				}
			}
		}
	}
	
	//垂直检测
	POINT temp2 = { -1,-1 };
	//垂直遍历每个点，如果为空，再进行垂直检测和拐角检测
	for (int x = 0; x <= MAP_SIZE + 1; x++)
	{
		if (x == Start.x)
			continue;
		if (!IsBlock(x, Start.y))
		{
			temp2 = { x,Start.y };
			if (col(Start, temp2))
			{
				//拐角检测
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
	//相同的位置返回false
	if (Start.first == End.first && Start.second == End.second)
	{
		return false;
	}
	//两个位置为空返回false
	if (map[Start.first][Start.second] == 0 && map[End.first][End.second] == 0)
		return false;
	queue<Node>q;
	Node s, temp;
	s.x = Start.first;
	s.y = Start.second;
	//初始方向
	s.direct = -1;
	//转弯次数
	s.step = 0;
	q.push(s);
	while (!q.empty())
	{
		temp = q.front();
		q.pop();
		if (temp.x == End.first && temp.y == End.second)
			return true;
		//遍历四个方向
		for (int i = 0; i < 4; i++)
		{
			s = temp;
			s.x += dx[i];
			s.y += dy[i];
			//超出边界就跳过这次循环
			if (s.x<0 || s.x>=MAP_SIZE + 2 || s.y < 0 || s.y >= MAP_SIZE + 2)
				continue;
			if (map[s.x][s.y] == 0||(s.x==End.first&&s.y==End.second))
			{
				if (s.direct != -1)
				{
					//说明转弯了
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
		//相同的图片·
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