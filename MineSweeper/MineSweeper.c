#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int Menu() {
	printf("============\n");
	printf("1.��ʼ��Ϸ\n");
	printf("0.������Ϸ\n");
	printf("============\n");
	printf("���������ѡ��");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}

#define ROW 9
#define COL 9
#define MineCount 11

//ɨ����Ϸ˼·��
//1.����Ҫ�����ݵ�ͼ(��char�Ͷ�ά������Ա�ʾ)	
//	a)����ҿ��ĵ�ͼShowMap(��Ҫ��ʾ��Щ�����ѷ���,��Щ����δ������' '��ʾδ�����ĸ���,
//	  ���ֱ�ʾ�˸����Ѿ�����������Χ�İ˸��������м�������)
//	b)���׷ֲ���ͼMineMap('0'��ʾ�˸��Ӳ��ǵ��ף�'1'��ʾ�˸����ǵ���
//    ������Ϸ�̴�С��������õ�����)
//2.��ʼ��������ͼ
//	a)ShowMap:ȫ����ʼ��Ϊ' '(�ո�)
//	b)MineMap:ȫ����ʼ��Ϊ'0'
//3.��ӡShowMap��Ȼ����ʾ����������겢У�������Ƿ�Ϸ�
//��������ĸ������ף�����Ϸ����(��ʾɨ��ʧ��)
//��������ĸ��Ӳ����ף������������һ�������׵ĸ��ӡ�����Ϸ����(��ʾɨ�׳ɹ�)��
//��������ĸ��Ӳ����ף��������������һ�������׵ĸ��ӡ��������Ϸ״̬��

void Init(char show_map[ROW + 2][COL + 2],
	char mine_map[ROW + 2][COL + 2]) {
	//�Ƚ�show_mapȫ����ʼ��Ϊ' '
	for (int row = 0; row < ROW + 2; ++row) {
		for (int col = 0; col < COL + 2; ++col) {
			show_map[row][col] = ' ';
		}
	}
	//�ٽ�mine_mapȫ����ʼ��Ϊ'0'
	for (int row = 0; row < ROW + 2; ++row) {
		for (int col = 0; col < COL + 2; ++col) {
			mine_map[row][col] = '0';
		}
	}
	//���mine_map�е�������������ú�
	int mine_count = MineCount;
	while (mine_count > 0) {
		int row = rand() % ROW + 1;
		int col = rand() % COL + 1;
		//�жϵ����Ƿ�Ϸ�
		//���Ƿ���������
		if (mine_map[row][col] == '1') {
			continue;
		}
		//���Ϸ����򽫵�ǰλ�÷��õ���
		mine_map[row][col] = '1';
		--mine_count;
	}
}

void DisplayMap(char map[ROW + 2][COL + 2]) {
	//�ȴ�ӡ���ϽǵĿո�
	printf("  ");
	//��ӡ������
	for (int i = 1; i <= ROW; ++i) {
		printf("%d",i);
	}
	printf("\n");
	//��ӡ�ϱ߿�
	for (int i = 1; i <= ROW; ++i) {
		printf("--");
	}
	printf("\n");
	//���д�ӡ
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
	//��ȡ�˸�����Χ8�������Ƿ��ǵ��ף�Ȼ����������ܺͱ��Ǵ˸�����Χ�ĵ�����
	//���ñ߿�ʹ���±겻����Խ�������ʹ������
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
		printf("������һ������(row,col)��");
		scanf("%d %d", &row, &col);
		//��֤���������Ƿ�Ϸ�
		if (row < 1 || row > ROW || col < 1 || col > COL) {
			printf("����Ƿ�������������.\n");
			continue;
		}
		//��֤�Ƿ�ȵ�����
		if (mine_map[row][col] == '1') {
			printf("�ȵ����ף���Ϸʧ�ܣ�");
			printf("\n");
			break;
		}
		//����Ϸ��򷭿��ĸ�������һ
		++zero_lattice_number;
		//��֤�Ƿ�ɨ�׳ɹ�
		if (zero_lattice_number == ROW*COL - MineCount) {
			printf("��Ϸ������ɨ�׳ɹ���\n");
			break;
		}
		//δ�ɹ�����µ�ͼ״̬
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
			printf("�ټ���\n");
			return;
		}
		if (choice == 1) {
			Game();
			return;
		}
	}

	return 0;
}