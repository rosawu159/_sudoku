#include <iostream>
#include<fstream>
#include<string>
#define N 9
using namespace std;


const std::string FILE_NAME = "Question.txt";

void print(char a[N][N]);

char a[N][N] = { 'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n' };

int main()
{

	fstream file;
	file.open(FILE_NAME, ios::in);
	char output[100];
	int i = 0;
	while (file.getline(output, sizeof(output), '\n')) {//���ɮ�input��x�}
		for (int j = 0; j < 9; j++) {
			a[i][j] = output[j * 2];
		}
		i++;
	}



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