/*
------------------------------------------------------------------------------------------
Title: Sudoku
Usage: ��J�t��9x9�ӼƦr�ΪŮ檺�ƿW�D���ɮסA��X�䤤�@�ոѡC
Date : 2018.05.15

By B10413040�BB10331040
------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <fstream>
#include <string>
#define N 9
using namespace std;

const string FILE_NAME = "Question.txt";

char a[N][N] = { 'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n' };
bool existNum[N][N];	//�Y���D�ح즳���Ʀr�A�b�����G���}�C��m�W�|��true�C

struct position
{
	short row, col;
};

void print(char a[N][N]);
void initialize(char a[N][N]);	//�Nn�אּ0�A�H�K�ާ@
void fillIn(char a[N][N]);	//�񺡤E�c��
void findNum(short row, short col, char a[N][N]);	//��backtracing�覡�M��A��Ʀr
void checkExistNum(char a[N][N], bool e[N][N]);	//�N�D�ح즳���Ʀr�D�X�ӡA�s��bool existNum���C
bool checkRow(char n, short row, short col, char a[N][N]);	//�T�{�P�@�C�����L���ƼƦr
bool checkColumn(char n, short row, short col, char a[N][N]);	//�T�{�P�@�椤���L���ƼƦr
bool checkBlock(char n, short row, short col, char a[N][N]);	//�T�{�P�@�E�c�椤���L���ƼƦr
position checkPreviousPos(short i, short j);	//�^�ǥثe�@�Τ��Ů檺�e�@��y��
position checkNextPos(short i, short j);	//�^�ǥثe�@�Τ��Ů檺�U�@��y��

int main()
{
	fstream file;
	file.open(FILE_NAME, ios::in);
	char output[100];
	char ans[N][N];
	int i = 0;
	while (file.getline(output, sizeof(output), '\n')) {//���ɮ�input��x�}
		for (int j = 0; j < 9; j++) {
			a[i][j] = output[j * 2];
		}
		i++;
	}
	file.close();

	checkExistNum(a, existNum);
	initialize(a);
	fillIn(a);
	print(a);

	system("pause");
	return 0;
}

// �L�X�x�}
void print(char a[N][N])
{
	for (int i = 0; i < N; i++)
	{
		printf(" ---------  ---------  ---------\n");
		if (i == 3 || i == 6)
			printf(" ---------  ---------  ---------\n");

		for (int j = 0; j < N; j++)
		{
			if (j == 3 || j == 6)
				printf("�U");
			printf("�U%c", a[i][j]);
		}
		printf("�U\n");
	}
	printf(" ---------  ---------  ---------\n");
}

void initialize(char a[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (a[i][j] == 'n')
				a[i][j] = '0';
		}
	}

	return;
}

void fillIn(char a[N][N])
{
	position firstBlank;
	firstBlank.row = 9;
	firstBlank.col = 9;

	//����D�ؤ����Ĥ@�ӪŮ�(Row major)��}�l�D��
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (!existNum[i][j] && a[i][j] == '0')
			{
				firstBlank.row = i;
				firstBlank.col = j;
				break;
			}
		}
		if (firstBlank.row != 9 && firstBlank.col != 9)
		{
			break;
		}
	}

	findNum(firstBlank.row, firstBlank.col, a);

	return;
}

void findNum(short row, short col, char a[N][N])
{
	position prePos, nextPos;
	short flag = 0;	//�ΨӽT�{�p�G�J���D�ح즳���Ʀr�A�n���eskip�٬O����skip�C-1: ��h 1: �e�i

	do
	{
		if (existNum[row][col])
		{
			if (flag == 1)
			{
				nextPos = checkNextPos(row, col);
				row = nextPos.row;
				col = nextPos.col;
				continue;
			}
			else if (flag == -1)
			{
				prePos = checkPreviousPos(row, col);
				row = prePos.row;
				col = prePos.col;
				continue;
			}
		}

		a[row][col]++;

		if (a[row][col] > '9')
		{
			a[row][col] = '0';
			prePos = checkPreviousPos(row, col);
			row = prePos.row;
			col = prePos.col;
			flag = -1;
		}
		else if (checkRow(a[row][col], row, col, a) && checkColumn(a[row][col], row, col, a) && checkBlock(a[row][col], row, col, a))
		{
			nextPos = checkNextPos(row, col);
			row = nextPos.row;
			col = nextPos.col;
			flag = 1;
		}

	} while (row != -1);

	return;
}

void checkExistNum(char a[N][N], bool e[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (a[i][j] != 'n')
				e[i][j] = true;
		}
	}
}

bool checkRow(char n, short row, short col, char a[N][N])
{
	for (int i = 0; i < N; i++)
	{
		if (i == col)
			continue;
		if (a[row][i] == n)
			return false;
	}
	return true;
}

bool checkColumn(char n, short row, short col, char a[N][N])
{
	for (int i = 0; i < N; i++)
	{
		if (i == row)
			continue;
		if (a[i][col] == n)
			return false;
	}
	return true;
}

bool checkBlock(char n, short row, short col, char a[N][N])
{
	if (row >= 0 && row <= 2)
	{
		if (col >= 0 && col <= 2)
		{
			//���W
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (i == row && j == col)
						continue;
					if (a[i][j] == n)
						return false;
				}
			}
		}
		else if (col >= 3 && col <= 5)
		{
			//����
			for (int i = 0; i < 3; i++)
			{
				for (int j = 3; j < 6; j++)
				{
					if (i == row && j == col)
						continue;
					if (a[i][j] == n)
						return false;
				}
			}
		}
		else if (col >= 6 && col <= 8)
		{
			//���U
			for (int i = 0; i < 3; i++)
			{
				for (int j = 6; j < 9; j++)
				{
					if (i == row && j == col)
						continue;
					if (a[i][j] == n)
						return false;
				}
			}
		}
	}
	else if (row >= 3 && row <= 5)
	{
		if (col >= 0 && col <= 2)
		{
			//���W
			for (int i = 3; i < 6; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (i == row && j == col)
						continue;
					if (a[i][j] == n)
						return false;
				}
			}
		}
		else if (col >= 3 && col <= 5)
		{
			//������
			for (int i = 3; i < 6; i++)
			{
				for (int j = 3; j < 6; j++)
				{
					if (i == row && j == col)
						continue;
					if (a[i][j] == n)
						return false;
				}
			}
		}
		else if (col >= 6 && col <= 8)
		{
			//���U
			for (int i = 3; i < 6; i++)
			{
				for (int j = 6; j < 9; j++)
				{
					if (i == row && j == col)
						continue;
					if (a[i][j] == n)
						return false;
				}
			}
		}
	}
	else if (row >= 6 && row <= 8)
	{
		if (col >= 0 && col <= 2)
		{
			//�k�W
			for (int i = 6; i < 9; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (i == row && j == col)
						continue;
					if (a[i][j] == n)
						return false;
				}
			}
		}
		else if (col >= 3 && col <= 5)
		{
			//�k��
			for (int i = 6; i < 9; i++)
			{
				for (int j = 3; j < 6; j++)
				{
					if (i == row && j == col)
						continue;
					if (a[i][j] == n)
						return false;
				}
			}
		}
		else if (col >= 6 && col <= 8)
		{
			//�k�U
			for (int i = 6; i < 9; i++)
			{
				for (int j = 6; j < 9; j++)
				{
					if (i == row && j == col)
						continue;
					if (a[i][j] == n)
						return false;
				}
			}
		}
	}
	return true;
}

position checkPreviousPos(short i, short j)
{
	position tmp;

	if (i == 0)
	{
		if (j == 0)
		{
			cout << "No solution.";
			system("PAUSE");
			exit(0);
		}
		else
		{
			tmp.row = i;
			tmp.col = j - 1;
			return tmp;
		}
	}
	else if (j == 0)
	{
		tmp.row = i - 1;
		tmp.col = 8;
		return tmp;
	}
	else
	{
		tmp.row = i;
		tmp.col = j - 1;
		return tmp;
	}
}

position checkNextPos(short i, short j)
{
	position tmp;

	if (i == 8)
	{
		if (j == 8)
		{
			tmp.row = -1;
			tmp.col = -1;
			return tmp;
		}
		else
		{
			tmp.row = i;
			tmp.col = j + 1;
			return tmp;
		}
	}
	else if (j == 8)
	{
		tmp.row = i + 1;
		tmp.col = 0;
		return tmp;
	}
	else
	{
		tmp.row = i;
		tmp.col = j + 1;
		return tmp;
	}
}

