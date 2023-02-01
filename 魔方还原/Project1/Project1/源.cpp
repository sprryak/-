#include<iostream>
#include<time.h>
#include <stdlib.h>
#include<queue>
using namespace std;
typedef struct magic_cube
{
	int state[13][3];
	int cnt = 0;
	int rear = 0;
	int path[50];
}Magic_Cube;
queue<Magic_Cube>q;

Magic_Cube Init()
{
	Magic_Cube init;
	init.state[1][1] = 1;
	init.state[1][2] = 1;
	init.state[2][1] = 1;
	init.state[2][2] = 1;
	init.state[3][1] = 2;
	init.state[3][2] = 2;
	init.state[4][1] = 2;
	init.state[4][2] = 2;
	init.state[5][1] = 3;
	init.state[5][2] = 3;
	init.state[6][1] = 3;
	init.state[6][2] = 3;
	init.state[7][1] = 4;
	init.state[7][2] = 4;
	init.state[8][1] = 4;
	init.state[8][2] = 4;
	init.state[9][1] = 5;
	init.state[9][2] = 5;
	init.state[10][1] = 5;
	init.state[10][2] = 5;
	init.state[11][1] = 6;
	init.state[11][2] = 6;
	init.state[12][1] = 6;
	init.state[12][2] = 6;
	return init;

}
Magic_Cube operation_1(Magic_Cube front) {//前层右转
	Magic_Cube temp;
	temp = front;
	temp.state[5][2] = front.state[6][2];
	temp.state[5][1] = front.state[5][2];
	temp.state[6][2] = front.state[6][1];
	temp.state[6][1] = front.state[5][1];

	temp.state[3][2] = front.state[3][2];
	temp.state[4][2] = front.state[4][2];
	temp.state[3][1] = front.state[11][2];
	temp.state[4][1] = front.state[11][1];

	temp.state[7][2] = front.state[2][2];
	temp.state[8][2] = front.state[2][1];
	temp.state[7][1] = front.state[7][1];
	temp.state[8][1] = front.state[8][1];

	temp.state[9][2] = front.state[9][2];
	temp.state[10][2] = front.state[10][2];
	temp.state[9][1] = front.state[9][1];
	temp.state[10][1] = front.state[10][1];

	temp.state[11][2] = front.state[8][2];
	temp.state[11][1] = front.state[7][2];
	temp.state[12][2] = front.state[12][2];
	temp.state[12][1] = front.state[12][1];

	temp.state[2][2] = front.state[4][1];
	temp.state[2][1] = front.state[3][1];
	temp.state[1][2] = front.state[1][2];
	temp.state[1][1] = front.state[1][1];

	temp.path[temp.rear++] = 1;
	temp.cnt++;
	return temp;
}

// 对应操作2
Magic_Cube operation_2(Magic_Cube front) {//前层左转
	Magic_Cube temp;
	temp = front;
	temp.state[5][2] = front.state[5][1];
	temp.state[6][2] = front.state[5][2];
	temp.state[5][1] = front.state[6][1];
	temp.state[6][1] = front.state[6][2];

	//左
	temp.state[3][1] = front.state[2][1];
	temp.state[4][1] = front.state[2][2];
	temp.state[3][2] = front.state[3][2];
	temp.state[4][2] = front.state[4][2];

	//右
	temp.state[7][2] = front.state[11][1];
	temp.state[8][2] = front.state[11][2];
	temp.state[7][1] = front.state[7][1];
	temp.state[8][1] = front.state[8][1];

	//背
	temp.state[9][2] = front.state[9][2];
	temp.state[10][2] = front.state[10][2];
	temp.state[9][1] = front.state[9][1];
	temp.state[10][1] = front.state[10][1];

	//顶
	temp.state[2][2] = front.state[7][2];
	temp.state[2][1] = front.state[8][2];
	temp.state[1][2] = front.state[1][2];
	temp.state[1][1] = front.state[1][1];


	//底
	temp.state[11][2] = front.state[3][1];
	temp.state[11][1] = front.state[4][1];
	temp.state[12][2] = front.state[12][2];
	temp.state[12][1] = front.state[12][1];

	temp.path[temp.rear++] = 2;
	temp.cnt++;
	return temp;
}

// 对应操作3
Magic_Cube operation_3(Magic_Cube front) {//右层前转
	Magic_Cube temp;
	temp = front;
	//前
	temp.state[5][1] = front.state[1][1];
	temp.state[6][1] = front.state[2][1];
	temp.state[5][2] = front.state[5][2];
	temp.state[6][2] = front.state[6][2];

	//左
	temp.state[3][2] = front.state[3][2];
	temp.state[3][1] = front.state[3][1];
	temp.state[4][2] = front.state[4][2];
	temp.state[4][1] = front.state[4][1];

	//右
	temp.state[7][2] = front.state[7][1];
	temp.state[7][1] = front.state[8][1];
	temp.state[8][2] = front.state[7][2];
	temp.state[8][1] = front.state[8][2];

	//背
	temp.state[9][2] = front.state[12][1];
	temp.state[10][2] = front.state[11][1];
	temp.state[9][1] = front.state[9][1];
	temp.state[10][1] = front.state[10][1];

	//底
	temp.state[11][1] = front.state[5][1];
	temp.state[12][1] = front.state[6][1];
	temp.state[11][2] = front.state[11][2];
	temp.state[12][2] = front.state[12][2];

	//顶部
	temp.state[1][1] = front.state[10][2];
	temp.state[2][1] = front.state[9][2];
	temp.state[1][2] = front.state[1][2];
	temp.state[2][2] = front.state[2][2];

	temp.path[temp.rear++] = 3;
	temp.cnt++;
	return temp;
}

Magic_Cube operation_4(Magic_Cube front) {//右层后转
	Magic_Cube temp;
	temp = front;
	//前
	temp.state[5][1] = front.state[11][1];
	temp.state[6][1] = front.state[12][1];
	temp.state[5][2] = front.state[5][2];
	temp.state[6][2] = front.state[6][2];

	//左
	temp.state[3][2] = front.state[3][2];
	temp.state[3][1] = front.state[3][1];
	temp.state[4][2] = front.state[4][2];
	temp.state[4][1] = front.state[4][1];

	//右
	temp.state[7][2] = front.state[8][2];
	temp.state[7][1] = front.state[7][2];
	temp.state[8][1] = front.state[7][1];
	temp.state[8][2] = front.state[8][1];

	//背
	temp.state[9][2] = front.state[2][1];
	temp.state[10][2] = front.state[1][1];
	temp.state[9][1] = front.state[9][1];
	temp.state[10][1] = front.state[10][1];

	//顶部
	temp.state[1][1] = front.state[5][1];
	temp.state[2][1] = front.state[6][1];
	temp.state[1][2] = front.state[1][2];
	temp.state[2][2] = front.state[2][2];

	//底
	temp.state[11][1] = front.state[10][2];
	temp.state[12][1] = front.state[9][2];
	temp.state[11][2] = front.state[11][2];
	temp.state[12][2] = front.state[12][2];

	temp.path[temp.rear++] = 4;
	temp.cnt++;
	return temp;
}

Magic_Cube operation_5(Magic_Cube front) {//上层右转
	Magic_Cube temp;
	temp = front;
	//前
	temp.state[5][2] = front.state[7][2];
	temp.state[5][1] = front.state[7][1];
	temp.state[6][2] = front.state[6][2];
	temp.state[6][1] = front.state[6][1];

	//左
	temp.state[3][2] = front.state[5][2];
	temp.state[3][1] = front.state[5][1];
	temp.state[4][2] = front.state[4][2];
	temp.state[4][1] = front.state[4][1];

	//右
	temp.state[7][2] = front.state[9][2];
	temp.state[7][1] = front.state[9][1];
	temp.state[8][2] = front.state[8][2];
	temp.state[8][1] = front.state[8][1];

	//背
	temp.state[9][2] = front.state[3][2];
	temp.state[9][1] = front.state[3][1];
	temp.state[10][2] = front.state[10][2];
	temp.state[10][1] = front.state[10][1];

	//顶
	temp.state[2][2] = front.state[2][1];
	temp.state[1][2] = front.state[2][2];
	temp.state[2][1] = front.state[1][1];
	temp.state[1][1] = front.state[1][2];

	//底部
	temp.state[11][2] = front.state[11][2];
	temp.state[12][2] = front.state[12][2];
	temp.state[11][1] = front.state[11][1];
	temp.state[12][1] = front.state[12][1];

	temp.path[temp.rear++] = 5;
	temp.cnt++;
	return temp;
}

Magic_Cube operation_6(Magic_Cube front) {//上层左转	
	Magic_Cube temp;
	temp = front;
	//前
	temp.state[5][2] = front.state[3][2];
	temp.state[5][1] = front.state[3][1];
	temp.state[6][2] = front.state[6][2];
	temp.state[6][1] = front.state[6][1];

	//左
	temp.state[3][2] = front.state[9][2];
	temp.state[3][1] = front.state[9][1];
	temp.state[4][2] = front.state[4][2];
	temp.state[4][1] = front.state[4][1];

	//右
	temp.state[7][2] = front.state[5][2];
	temp.state[7][1] = front.state[5][1];
	temp.state[8][2] = front.state[8][2];
	temp.state[8][1] = front.state[8][1];

	//背部
	temp.state[9][2] = front.state[7][2];
	temp.state[9][1] = front.state[7][1];
	temp.state[10][2] = front.state[10][2];
	temp.state[10][1] = front.state[10][1];

	//顶
	temp.state[1][1] = front.state[2][1];
	temp.state[1][2] = front.state[1][1];
	temp.state[2][2] = front.state[1][2];
	temp.state[2][1] = front.state[2][2];

	//底部
	temp.state[11][2] = front.state[11][2];
	temp.state[12][2] = front.state[12][2];
	temp.state[11][1] = front.state[11][1];
	temp.state[12][1] = front.state[12][1];

	temp.path[temp.rear++] = 6;
	temp.cnt++;
	return temp;
}


bool is_back(Magic_Cube front) {
	if (front.state[1][1] == front.state[1][2] && front.state[1][1] == front.state[2][1] && front.state[1][1] == front.state[2][2] &&
		front.state[3][1] == front.state[3][2] && front.state[3][1] == front.state[4][1] && front.state[3][1] == front.state[4][2] &&
		front.state[5][1] == front.state[5][2] && front.state[5][1] == front.state[6][1] && front.state[5][1] == front.state[6][2] &&
		front.state[7][1] == front.state[7][2] && front.state[7][1] == front.state[8][1] && front.state[7][1] == front.state[8][2] &&
		front.state[9][1] == front.state[9][2] && front.state[9][1] == front.state[10][1] && front.state[9][1] == front.state[10][2] &&
		front.state[11][1] == front.state[11][2] && front.state[11][1] == front.state[12][1] && front.state[11][1] == front.state[12][2])
		return true;
	else
		return false;
}
Magic_Cube rand_magic_cube(Magic_Cube init)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < 6;i++)
	{
		int n = rand() % 6 + 1;
		if (n == 1)
			init = operation_1(init);
		if (n == 2)
			init = operation_2(init);
		if (n == 3)
			init = operation_3(init);
		if (n == 4)
			init = operation_4(init);
		if (n == 5)
			init = operation_5(init);
		if (n == 6)
			init = operation_6(init);

	}
	init.cnt = 0;
	init.rear = 0;
	return init;
}


void show(Magic_Cube front)
{
	printf("步数为:%d\n", front.cnt);
	printf("还原后的魔方状态为:");
	for (int i = 1; i <= 12; i++)
		for (int j = 1; j <= 2; j++)
			printf("%d ", front.state[i][j]);
	
	printf("\n");
	printf("还原步骤为:");
	for (int i = 0; i < front.rear; i++)
	{
		printf("%d ", front.path[i]);
	}
	return;
}
void bfs(Magic_Cube init)
{
	int head = 0, tail = 0;
	Magic_Cube front;
	init = rand_magic_cube(init);
	init.rear = 0;
	init.cnt = 0;
	q.push(init);
	
	while (!q.empty())
	{
		front = q.front();
		q.pop();
		if (is_back(front))
		{
			show(front);
			return;
		}
		q.push(operation_1(front));
		q.push(operation_2(front));
		q.push(operation_3(front));
		q.push(operation_4(front));
		q.push(operation_5(front));
		q.push(operation_6(front));
	}
}


int main()
{
	Magic_Cube init = Init();
	bfs(init);
}