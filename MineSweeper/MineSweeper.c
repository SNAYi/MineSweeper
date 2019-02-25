#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int Menu() {
	printf("============\n");
	printf("1.开始游戏\n");
	printf("0.结束游戏\n");
	printf("============\n");
	printf("请输入你的选择：");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}

#define ROW 9
#define COL 9
#define MineCount 11

//扫雷游戏思路：
//1.首先要有两份地图(用char型二维数组可以表示)	
//	a)给玩家看的地图ShowMap(需要表示哪些格子已翻开,哪些格子未翻开）' '表示未翻开的格子,
//	  数字表示此格子已经翻开并且周围的八个格子中有几个地雷)
//	b)地雷分布地图MineMap('0'表示此格子不是地雷，'1'表示此格子是地雷
//    根据游戏盘大小来随机设置地雷数)
//2.初始化两个地图
//	a)ShowMap:全部初始化为' '(空格)
//	b)MineMap:全部初始化为'0'
//3.打印ShowMap，然后提示玩家输入坐标并校验输入是否合法
//如果翻开的格子是雷，则游戏结束(提示扫雷失败)
//如果翻开的格子不是雷，并且它是最后一个不是雷的格子。则游戏结束(提示扫雷成功)。
//如果翻开的格子不是雷，并且它不是最后一个不是雷的格子。则更新游戏状态。

void Init(char show_map[ROW + 2][COL + 2],
	char mine_map[ROW + 2][COL + 2]) {
	//先将show_map全部初始化为' '
	for (int row = 0; row < ROW + 2; ++row) {
		for (int col = 0; col < COL + 2; ++col) {
			show_map[row][col] = ' ';
		}
	}
	//再将mine_map全部初始化为'0'
	for (int row = 0; row < ROW + 2; ++row) {
		for (int col = 0; col < COL + 2; ++col) {
			mine_map[row][col] = '0';
		}
	}
	//最后将mine_map中的随机地雷数设置好
	int mine_count = MineCount;
	while (mine_count > 0) {
		int row = rand() % ROW + 1;
		int col = rand() % COL + 1;
		//判断地雷是否合法
		//若非法，则重置
		if (mine_map[row][col] == '1') {
			continue;
		}
		//若合法，则将当前位置放置地雷
		mine_map[row][col] = '1';
		--mine_count;
	}
}

void DisplayMap(char map[ROW + 2][COL + 2]) {
	//先打印左上角的空格
	printf("  ");
	//打印列坐标
	for (int i = 1; i <= ROW; ++i) {
		printf("%d",i);
	}
	printf("\n");
	//打印上边框
	for (int i = 1; i <= ROW; ++i) {
		printf("--");
	}
	printf("\n");
	//逐行打印
	for (int row = 1; row <= ROW;++row) {
		printf("%d|",row);
		for (int col = 1; col <= COL; ++col) {
			printf("%c",map[row][col]);
		}
		printf("\n");
	}
}

void UpdateShowMap(char show_map[ROW + 2][COL + 2], char mine_map[ROW + 2][COL + 2],
	int row, int col) {
	//获取此格子周围8个格子是否是地雷，然后加起来的总和便是此格子周围的地雷数
	//采用边框使得下标不存在越界情况，使代码简洁
	int count = 0;
	if (mine_map[row - 1][col - 1] == '1') {
		++count;
	}
	if (mine_map[row - 1][col] == '1') {
		++count;
	}
	if (mine_map[row - 1][col + 1] == '1') {
		++count;
	}
	if (mine_map[row ][col - 1] == '1') {
		++count;
	}
	if (mine_map[row][col + 1] == '1') {
		++count;
	}
	if (mine_map[row + 1][col - 1] == '1') {
		++count;
	}
	if (mine_map[row + 1][col] == '1') {
		++count;
	}
	if (mine_map[row + 1][col] == '1') {
		++count;
	}
	/*count = (mine_map[row - 1][col - 1] - '0'
		+ mine_map[row - 1][col] - '0'
		+ mine_map[row - 1][col + 1] - '0'
		+ mine_map[row][col - 1] - '0'
		+ mine_map[row][col + 1] - '0'
		+ mine_map[row + 1][col - 1] - '0'
		+ mine_map[row + 1][col] - '0'
		+ mine_map[row + 1][col + 1] - '0');*/
	show_map[row][col] = count + '0';
}

void Game( ) {
	char show_map[ROW + 2][COL + 2];
	char mine_map[ROW + 2][COL + 2];
	Init(show_map, mine_map);
	int zero_lattice_number = 0;
	while (1) {
		DisplayMap(show_map);
		int row = 0;
		int col = 0;
		printf("请输入一组坐标(row,col)：");
		scanf("%d %d", &row, &col);
		//验证坐标输入是否合法
		if (row < 1 || row > ROW || col < 1 || col > COL) {
			printf("输入非法！请重新输入.\n");
			continue;
		}
		//验证是否踩到地雷
		if (mine_map[row][col] == '1') {
			printf("踩到地雷，游戏失败！");
			printf("\n");
			break;
		}
		//如果合法则翻开的格子数加一
		++zero_lattice_number;
		//验证是否扫雷成功
		if (zero_lattice_number == ROW*COL - MineCount) {
			printf("游戏结束，扫雷成功！\n");
			break;
		}
		//未成功则更新地图状态
		UpdateShowMap(show_map,mine_map,row,col);
		system("cls"); 
	}
	DisplayMap(mine_map);
}

int main() {
	srand((unsigned int)time(0));
	while (1) {
		int choice = Menu();
		if (choice == 0) {
			printf("再见！\n");
			return;
		}
		if (choice == 1) {
			Game();
			return;
		}
	}

	return 0;
}