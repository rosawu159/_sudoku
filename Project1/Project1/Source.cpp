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
	while (file.getline(output, sizeof(output), '\n')) {//���ɮ�input��x�}
		for (int j = 0; j < 9; j++) {
			a[i][j] = output[j * 2];
		}
		i++;
	}
	file.close();

	//��a�ƻs��ans
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

//�H�@�C�����Ʀr�����Ƭ���h�A�񺡤E�c��
void rowFillIn(char a[N][N], char ans[N][N])
{
	vector<int> existNums;
	vector<int>::iterator it;

	for (int i = 0; i < N; i++)
	{
		//���ˬd�C�C�w�s�b���Ʀr�A��push��vector��
		for (int j = 0; j < N; j++)
		{
			if (a[i][j] != 'n')
				existNums.push_back(a[i][j] - 48);
		}

		for (int j = 0; j < N; j++)
		{
			//�M��ثe��j�O�_�w�s�b
			it = find(existNums.begin(), existNums.end(), j + 1);
			
			//�Y���s�b�A��J�}�Cans��������l��(�Y�s�b�|�d��)
			if (it == existNums.end() && ans[i][j] == 'n')
				ans[i][j] = j + 49;
		}

		existNums.clear();
	}
}

