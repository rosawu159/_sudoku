/*
------------------------------------------------------------------------------------------
Title: Sudoku
Usage: 輸入含有9x9個數字及空格的數獨題目檔案，輸出其中一組解。
Date : 2018.05.15

By B10413040、B10331040
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
bool existNum[N][N];	//若為題目原有的數字，在對應二維陣列位置上會為true。

struct position
{
	short row, col;
};

void print(char a[N][N]);
void initialize(char a[N][N]);	//將n改為0，以便操作
void fillIn(char a[N][N]);	//填滿九宮格
void findNum(short row, short col, char a[N][N]);	//用backtracing方式尋找適當數字
void checkExistNum(char a[N][N], bool e[N][N]);	//將題目原有的數字挑出來，存到bool existNum當中。
bool checkRow(char n, short row, short col, char a[N][N]);	//確認同一列中有無重複數字
bool checkColumn(char n, short row, short col, char a[N][N]);	//確認同一行中有無重複數字
bool checkBlock(char n, short row, short col, char a[N][N]);	//確認同一九宮格中有無重複數字
position checkPreviousPos(short i, short j);	//回傳目前作用中空格的前一格座標
position checkNextPos(short i, short j);	//回傳目前作用中空格的下一格座標

int main()
{
	fstream file;
	file.open(FILE_NAME, ios::in);
	char output[100];
	char ans[N][N];
	int i = 0;
	while (file.getline(output, sizeof(output), '\n')) {//把檔案input到矩陣
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

// 印出矩陣
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
				printf("｜");
			printf("｜%c", a[i][j]);
		}
		printf("｜\n");
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

	//找到題目中的第一個空格(Row major)後開始求解
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
	short flag = 0;	//用來確認如果遇到題目原有的數字，要往前skip還是往後skip。-1: 後退 1: 前進

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
			//左上
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
			//左中
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
			//左下
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
			//中上
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
			//正中間
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
			//中下
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
			//右上
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
			//右中
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
			//右下
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

