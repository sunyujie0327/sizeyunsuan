#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
//存放运算式的结构体
struct node {
	char shu[13];//运算数
	char op[3];    //运算符
};
//种子变换函数
int ran(int &x)
{
	x++;
	return x;
}
//1.产生运算数
char *shu(int max, int sign5,int &x)
{
	char str[100];
	int a, i;
	//整数
	srand(ran(x));
	for (i = 0; i < max; i++)
	{
		a = rand() % 9+1;
		str[i] = a + '0';
	}
	//小数
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
//2.生成运算式
int create1(int j1,node OperationFormula[][20],int max,int num,int sign5,int &x) {
	
	char op[10] = { '0','+','-','*','/' ,'0','0','0','0'};
	int i = 0, j = 0, p;
	int sign=0;//运算式结束标志
	//设置运算符
	while (1) {
		p = num % 10;
		num = num / 10;
		op[p + 4] = '1';
		if (num == 0)break;
	}
	//获得第一个运算数
	srand(ran(x));
	strcpy(OperationFormula[j1][j++].shu ,shu(max,sign5,x));
	while (1) {
		//获得运算符
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
		if (sign == 1 || j > 8)break;//设置最多五个运算数截至或者随机截至
		//获得运算数
		srand(ran(x));
		strcpy(OperationFormula[j1][j++].shu, shu(max, sign5,x));
		if (sign == 1 || j > 8)break;//设置最多五个运算数截至或者随机截至
	}
	return j;//返回运算式长度
}
//3.添加前括号
void qian(char *a) {
	char b[13];
	b[0] = '(';
	b[1] = '\0';
	strcat(b, a);
	strcpy(a, b);
}
//4.添加后括号
void hou(char *a) {
	char b[2];
	b[0] = ')';
	b[1] = '\0';
	strcat(a, b);
}
//5添加括号
void create2(node OperationFormula[][20],int i,int j,int &x) {
	int a = 0, j1 = 0;
	int kuohao = 0;//当前括号标志：1：有（未能匹配到后括号的）前括号 
	               //              0；没有（未能匹配到后括号的）前括号 
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
			a = rand() % 2;//是否添加前括号：1：添加  0：不添加
			if (a == 1) {
				qian(OperationFormula[i][j1].shu);
				kuohao = 1;
			}
		}
		else {
			srand(ran(x));
			a = rand() % 2;//是否添加后括号：1：添加  0：不添加
			if (a == 1) {
				hou(OperationFormula[i][j1].shu);
				kuohao = 0;
			}
		}
		j1=j1+2;
	}
}
//写文件
void cun(char str[][100], int m)//如果有文件则打开文件的函数
{
	FILE *p1;
	int i;
	p1 = fopen("C://wang.txt", "rb");
	for (i = 0; i < m; i++)
		fprintf(p1, "%s", str[i]);
	fclose(p1);
	printf("\n修改已完成，请打开文件 wang.txt 进行查看         \n");
}
int main()
{
	char str[100][100];
	node OperationFormula[100][20];//存储运算式
	int i, j, k, n, max, num, sign4, sign5, sign6;
	int x = 512;//随机数种子
	printf("定制小学计算题\n");
	printf("1.定制题目数量:");
	scanf("%d", &n);
	printf("2.设置数的范围为几位数：");
	scanf("%d", &max);
	printf("3.选择运算符(输入的序号之间没有间隔)：1.+   2.-  3.*  4/   :");
	scanf("%d", &num);
	printf("4.选择是否有括号:   1.有  2.无  :");
	scanf("%d", &sign4);
	printf("5.选择是否有小数：  1.有  2.无  :");
	scanf("%d", &sign5);
	printf("6.是否输出到文件：  1.是  2.否  :");
	scanf("%d", &sign6);
	printf("\n*********系统自动生题**********\n");
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