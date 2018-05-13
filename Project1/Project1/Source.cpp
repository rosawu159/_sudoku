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
bool existNum[N][N];

struct position
{
	int row, col;
};

void print(char a[N][N]);
void fillIn(char a[N][N]);
void findNum(int row, int col,int k, char a[N][N]);
void checkExistNum(char a[N][N], bool e[N][N]);
bool checkRow(int n,int row, char a[N][N]);
bool checkColumn(int n, int col, char a[N][N]);
bool checkBlock(int n, int row, int col, char a[N][N]);
position checkPreviousPos(int i, int j);
position checkNextPos(int i, int j);

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


	/*insert code below*/
	checkExistNum(a, existNum);
	fillIn(a);

	/*insert code above*/

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

//填滿九宮格
void fillIn(char a[N][N])
{
	position firstBlank;
	firstBlank.row = 9;
	firstBlank.col = 9;

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (!existNum[i][j] && a[i][j] == 'n')
				{
					firstBlank.row = i;
					firstBlank.col = i;
					break;
				}
			}
			if (firstBlank.row != 9 && firstBlank.col != 9)
			{
				break;
			}
		}

		findNum(firstBlank.row, firstBlank.col, '1', a);

	return;
}

void findNum(int row, int col,int k,char a[N][N])
{
	bool isAns = false, notAns = false;

	if (existNum[row][col] && k > '1')
	{
		position prePos = checkPreviousPos(row, col);
		row = prePos.row;
		col = prePos.col;
		if (a[row][col] <= '9'&&a[row][col] >= '1')
		{
			findNum(row, col, a[row][col] + 1, a);
		}
		else if (a[row][col] == 'n')
		{
			findNum(row, col, '1', a);
		}
	}
	else if (existNum[row][col] && k == '1')
	{
		position nextPos = checkNextPos(row, col);
		row = nextPos.row;
		col = nextPos.col;
		findNum(row, col, '1', a);
	}

	if (checkRow(k, row, a) && checkColumn(k, col, a) && checkBlock(k, row, col, a) && !existNum[row][col] &&( a[row][col] < '9'||a[row][col]=='n'))
	{
		print(a);
		cout << "===================" << endl;

		a[row][col] = k;
		position nextPos = checkNextPos(row, col);
		row = nextPos.row;
		col = nextPos.col;
		findNum(row, col, '1', a);

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (a[i][j] == 'n')
				{
					notAns = true;
					break;
				}
			}
			if (notAns)
			{
				notAns = false;
				break;
			}
			if (i == N - 1 && !notAns)
				isAns = true;
		}

		if (isAns)
			return;
	}
	else if (k < '9'&&k >= '1')
	{
		findNum(row, col, ++k,a);
	}
	else
	{
		if (!existNum[row][col])
		{
			a[row][col] = 'n';
		}
		position prePos = checkPreviousPos(row, col);
		row = prePos.row;
		col = prePos.col;
		if (a[row][col] <= '9'&&a[row][col] >= '1')
		{
			findNum(row, col, a[row][col] + 1, a);
		}
		else if (a[row][col] == 'n')
		{
			findNum(row, col, '1', a);
		}
	}
}

void checkExistNum(char a[N][N], bool e[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (a[i][j] != 'n')
			{
				e[i][j] = true;
			}
		}
	}
}

bool checkRow(int n,int row, char a[N][N])
{
	for (int i = 0; i < N; i++)
	{
		if (a[row][i] == n)
			return false;
	}
	return true;
}

bool checkColumn(int n,int col, char a[N][N])
{
	for (int i = 0; i < N; i++)
	{
		if (a[i][col] == n)
			return false;
	}
	return true;
}

bool checkBlock(int n,int row,int col, char a[N][N])
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
					if (a[i][j] == n)
						return false;
				}
			}
		}
	}
	return true;
}

position checkPreviousPos(int i, int j)
{
	position tmp;

	if (i == 0)
	{
		if (j == 0)
		{
			tmp.row = 8;
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

position checkNextPos(int i, int j)
{
	position tmp;

	if (i == 8)
	{
		if (j == 8)
		{
			tmp.row = 0;
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

