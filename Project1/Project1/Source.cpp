#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

void print(char a[N][N]);
void rowFillIn(char a[N][N], char ans[N][N]);

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

	//把a複製到ans
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			ans[i][j] = a[i][j];
	}

	/*insert code below*/
	rowFillIn(a, ans);

	/*insert code above*/

	print(ans);
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

//以一列當中的數字不重複為原則，填滿九宮格
void rowFillIn(char a[N][N], char ans[N][N])
{
	vector<int> existNums;
	vector<int>::iterator it;

	for (int i = 0; i < N; i++)
	{
		//先檢查每列已存在的數字，並push到vector裡
		for (int j = 0; j < N; j++)
		{
			if (a[i][j] != 'n')
				existNums.push_back(a[i][j] - 48);
		}

		for (int j = 0; j < N; j++)
		{
			//尋找目前的j是否已存在
			it = find(existNums.begin(), existNums.end(), j + 1);
			
			//若不存在，填入陣列ans的對應格子內(若存在會留空)
			if (it == existNums.end() && ans[i][j] == 'n')
				ans[i][j] = j + 49;
		}

		existNums.clear();
	}
}

