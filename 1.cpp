#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
//�������ʽ�Ľṹ��
struct node {
	char shu[13];//������
	char op[3];    //�����
};
//���ӱ任����
int ran(int &x)
{
	x++;
	return x;
}
//1.����������
char *shu(int max, int sign5,int &x)
{
	char str[100];
	int a, i;
	//����
	srand(ran(x));
	for (i = 0; i < max; i++)
	{
		a = rand() % 9+1;
		str[i] = a + '0';
	}
	//С��
	if (sign5 == 1) {
		str[i] = '.';
		srand(ran(x));
		for (i++; i < max + 3; i++)
		{
			a = rand() % 10;
			str[i] = a + '0';
		}
	}
	str[i] = '\0';
	return str;
}
//2.��������ʽ
int create1(int j1,node OperationFormula[][20],int max,int num,int sign5,int &x) {
	
	char op[10] = { '0','+','-','*','/' ,'0','0','0','0'};
	int i = 0, j = 0, p;
	int sign=0;//����ʽ������־
	//���������
	while (1) {
		p = num % 10;
		num = num / 10;
		op[p + 4] = '1';
		if (num == 0)break;
	}
	//��õ�һ��������
	srand(ran(x));
	strcpy(OperationFormula[j1][j++].shu ,shu(max,sign5,x));
	while (1) {
		//��������
		srand(ran(x));
		while (1) {
			srand(ran(x));
			i = rand() % 5;
			if (op[i + 4] == '1') {
				OperationFormula[j1][j].op[0] = op[i];
				OperationFormula[j1][j++].op[1] = '\0';
				break;
			}
			if (j>=3&&i == 0){
				sign = 1;
				break;
		    }
		}
		if (sign == 1 || j > 8)break;//�������������������������������
		//���������
		srand(ran(x));
		strcpy(OperationFormula[j1][j++].shu, shu(max, sign5,x));
		if (sign == 1 || j > 8)break;//�������������������������������
	}
	return j;//��������ʽ����
}
//3.���ǰ����
void qian(char *a) {
	char b[13];
	b[0] = '(';
	b[1] = '\0';
	strcat(b, a);
	strcpy(a, b);
}
//4.��Ӻ�����
void hou(char *a) {
	char b[2];
	b[0] = ')';
	b[1] = '\0';
	strcat(a, b);
}
//5�������
void create2(node OperationFormula[][20],int i,int j,int &x) {
	int a = 0, j1 = 0;
	int kuohao = 0;//��ǰ���ű�־��1���У�δ��ƥ�䵽�����ŵģ�ǰ���� 
	               //              0��û�У�δ��ƥ�䵽�����ŵģ�ǰ���� 
	while (1) {
		if (kuohao == 0 && j1 == j - 1){
			break;
		}
		if (kuohao == 1 && j1 == j - 1) {
			hou(OperationFormula[i][j-1].shu); 
			break;
		}
		
		if (kuohao == 0) {
			srand(ran(x));
			a = rand() % 2;//�Ƿ����ǰ���ţ�1�����  0�������
			if (a == 1) {
				qian(OperationFormula[i][j1].shu);
				kuohao = 1;
			}
		}
		else {
			srand(ran(x));
			a = rand() % 2;//�Ƿ���Ӻ����ţ�1�����  0�������
			if (a == 1) {
				hou(OperationFormula[i][j1].shu);
				kuohao = 0;
			}
		}
		j1=j1+2;
	}
}
//д�ļ�
void cun(char str[][100], int m)//������ļ�����ļ��ĺ���
{
	FILE *p1;
	int i;
	p1 = fopen("C://wang.txt", "rb");
	for (i = 0; i < m; i++)
		fprintf(p1, "%s", str[i]);
	fclose(p1);
	printf("\n�޸�����ɣ�����ļ� wang.txt ���в鿴         \n");
}
int main()
{
	char str[100][100];
	node OperationFormula[100][20];//�洢����ʽ
	int i, j, k, n, max, num, sign4, sign5, sign6;
	int x = 512;//���������
	printf("����Сѧ������\n");
	printf("1.������Ŀ����:");
	scanf("%d", &n);
	printf("2.�������ķ�ΧΪ��λ����");
	scanf("%d", &max);
	printf("3.ѡ�������(��������֮��û�м��)��1.+   2.-  3.*  4/   :");
	scanf("%d", &num);
	printf("4.ѡ���Ƿ�������:   1.��  2.��  :");
	scanf("%d", &sign4);
	printf("5.ѡ���Ƿ���С����  1.��  2.��  :");
	scanf("%d", &sign5);
	printf("6.�Ƿ�������ļ���  1.��  2.��  :");
	scanf("%d", &sign6);
	printf("\n*********ϵͳ�Զ�����**********\n");
	for (i = 0; i < n; i++)
	{
		printf("%d.", i+1);
		srand(ran(x));
		j = create1(i,OperationFormula, max, num, sign5,x);
		if (sign4 == 1)create2(OperationFormula, i, j,x);
		for (k = 0; k < j; k++)
		{
			if (k % 2 == 0) {
				strcat(str[i], OperationFormula[i][k].shu);
				printf("%s", OperationFormula[i][k].shu);
			}
			else {
				strcat(str[i], OperationFormula[i][k].op);
				printf("%s", OperationFormula[i][k].op);
			}
		}
		printf("\n");
	}
	if (sign6 == 1)cun(str, n);
	return 0;
}