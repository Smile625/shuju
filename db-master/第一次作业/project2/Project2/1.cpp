#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<math.h>
#pragma warning(disable:4996)
#define LEN1 sizeof(struct salesman)
#define LEN2 sizeof(struct projectcount)
#define uk 72
#define dk 80
#define lk 75
#define rk 77
#define M 100
struct salesman {
	int d;//天数day
	int sc;//销售员代号salesman code 1-4
	int pc;//产品代号product code 1-5
	float sale;//产品销售额
	struct salesman* next;
};
int n = 0;//记录便条的数目
int m = 0;//记录录入数据的天数
void mainMenu() {
	printf("**********销售管理系统**********\n");
	printf("*           1.录入信息         *\n");
	printf("*           2.统计功能         *\n");
	printf("*           3.查询功能         *\n");
	printf("*           4.历史数据         *\n");
	printf("*           5.历史数据查询     *\n");
	printf("*           6.历史数据统计     *\n");
	printf("*           7.退出             *\n");
	printf("********************************\n");
	//提示用户选择
	printf("请点击方向键进入你想要实现的功能界面。");
}
//1.录入信息
struct salesman* creat(void) {
	struct salesman* p1, * p2;
	struct salesman* head1;
	head1 = NULL;
	printf("Please input the sale information.\nfor examlpe :\n1\n1\n4\n100.05\n");
	p1 = p2 = (struct salesman*)malloc(LEN1);
	if (p1 == NULL) { printf("分配内存失败"); exit(-1); }
	printf("input the date:\n");
	scanf("%d%d%d%f", &p1->d, &p1->sc, &p1->pc, &p1->sale);
	while (p1->d <= 0 || p1->sc < 1 || p1->sc>4 || p1->pc < 1 || p1->pc>5)
	{
		printf("you have input the wrong data!please input the right data again!\n");
		scanf("%d%d%d%f", &p1->d, &p1->sc, &p1->pc, &p1->sale);
	}
	while (p1->sc != 0) {
		n++;
		if (n == 1) head1 = p1;
		else p2->next = p1;
		p2 = p1;
		p1 = (struct salesman*)malloc(LEN1);//开辟动态存储空间，起始地址给p1
		if (p1 == NULL) { printf("分配内存失败"); exit(-1); }
		scanf("%d%d%d%f", &p1->d, &p1->sc, &p1->pc, &p1->sale);
		while (p1->d < 0 || p1->sc < 0 || p1->sc >= 5 || p1->pc < 0 || p1->pc >= 6)
		{
			printf("you have input the wrong data!please input the right data again!\n");
			scanf("%d%d%d%f", &p1->d, &p1->sc, &p1->pc, &p1->sale);
		}
	}
	p2->next = NULL;
	return (head1);
}
//2.统计数据
void count(struct salesman* p) { //p是链表
	int i;
	struct salesman* pt = NULL, * head = p;
	pt = p;
	float a[M][5] = { 0 };//存储每天各产品的销售总金额
	//下面计算每天各产品的销售金额
	for (i = 0; pt != NULL;)
	{
		if ((pt->d) - 1 == i) {//如果和天数i对应，找到对应元素累积销售金额
			if ((pt->pc) == 1) {
				a[i][0] += pt->sale;
			}
			else if ((pt->pc) == 2) {
				a[i][1] += pt->sale;
			}
			else if ((pt->pc) == 3) {
				a[i][2] += pt->sale;
			}
			else if ((pt->pc) == 4) {
				a[i][3] += pt->sale;
			}
			else if ((pt->pc) == 5) {
				a[i][4] += pt->sale;
			}
			pt = pt->next;//读取下一个便条
		}
		else i++;//否则天数+1     
	}
	m = i;
	pt = head;
	//下面计算销售员的总销售额
	float ss[4] = { 0 };//保存1-4号员工的总产品销售金额。
	for (i = 0; i < n; i++) {
		if ((pt->sc) == 1)ss[0] += pt->sale;
		else if ((pt->sc) == 2)ss[1] += pt->sale;
		else if ((pt->sc) == 3)ss[2] += pt->sale;
		else if ((pt->sc) == 4)ss[3] += pt->sale;
		pt = pt->next;//指向下一个结点
	}
	//最后保存到报表文件中
	FILE* fp;
	if ((fp = fopen("Count Statement.txt", "w+")) == NULL) {
		printf("can't open file!\n");
		exit(0);
	}
	fprintf(fp, "***每天各商品的销售金额报表***\n");
	for (i = 0; a[i][0] || a[i][1] || a[i][2] || a[i][3] || a[i][4]; i++) //每天各商品的销售金额报表
		fprintf(fp, "第%d天销售额 产品1 %f\t产品2 %f\t产品3 %f\t产品4 %f\t产品5 %f\n", i + 1, a[i][0], a[i][1], a[i][2], a[i][3], a[i][4]);//将数据录入报表文件中
	fprintf(fp, "******************************\n");
	fprintf(fp, "***销售员总销售额报表***\n");
	for (i = 0; i < 4; i++)//销售员总销售额的报表
		fprintf(fp, "销售员%d号的总销售额为：%f\n", i + 1, ss[i]);
	fprintf(fp, "************************\n");
	fclose(fp);//关闭文件
}
//3.查询数据
void check(struct salesman* p) {
	struct salesman* pt = NULL, * head = p;
	int d;
	printf("请输入您要查询的天数：");
	scanf("%d", &d);
	pt = p;
	int i, j, k;
	float t1, t2;
	//查询每种产品销售员当天的销售额表
	float s[5][4][2] = { 0,1,0,2,0,3,0,4 , 0,1,0,2,0,3,0,4, 0,1,0,2,0,3,0,4, 0,1,0,2,0,3,0,4, 0,1,0,2,0,3,0,4 };
	while (pt != NULL) {
		if (pt->d == d) {//找到符合天数的便条
			switch (pt->pc) {//按产品分
			case 1:switch (pt->sc) {//按销售员的代号区分
			case 1: {s[0][0][0] = pt->sale; break; }
			case 2: {s[0][1][0] = pt->sale; break; }
			case 3: {s[0][2][0] = pt->sale; break; }
			case 4: {s[0][3][0] = pt->sale; break; }
			}break;                                                                     //下面的依次类推
			case 2:switch (pt->sc) {                                                   //产品2
			case 1: {s[1][0][0] = pt->sale;  break; }
			case 2: {s[1][1][0] = pt->sale;  break; }
			case 3: {s[1][2][0] = pt->sale;  break; }
			case 4: {s[1][3][0] = pt->sale;  break; }
			}break;
			case 3:switch (pt->sc) {                                                   //产品3
			case 1: {s[2][0][0] = pt->sale;  break; }
			case 2: {s[2][1][0] = pt->sale;  break; }
			case 3: {s[2][2][0] = pt->sale;  break; }
			case 4: {s[2][3][0] = pt->sale;  break; }
			}break;
			case 4:switch (pt->sc) {                                                  //产品4
			case 1: {s[3][0][0] = pt->sale;  break; }
			case 2: {s[3][1][0] = pt->sale;  break; }
			case 3: {s[3][2][0] = pt->sale;  break; }
			case 4: {s[3][3][0] = pt->sale;  break; }
			}break;
			case 5:switch (pt->sc) {                                                 //产品5
			case 1: {s[4][0][0] = pt->sale;  break; }
			case 2: {s[4][1][0] = pt->sale;  break; }
			case 3: {s[4][2][0] = pt->sale;  break; }
			case 4: {s[4][3][0] = pt->sale;  break; }
			}break;
			}
		}
		pt = pt->next;//指向下一个结点
	}
	for (k = 0; k < 5; k++)
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3 - i; j++)
				if (s[k][j][0] > s[k][j + 1][0]) {
					t1 = s[k][j][0];
					t2 = s[k][j][1];
					s[k][j][0] = s[k][j + 1][0];
					s[k][j][1] = s[k][j + 1][1];
					s[k][j + 1][0] = t1;
					s[k][j + 1][1] = t2;
				}
	//在输出报表的同时将报表存储在新文件中
	printf("***每种产品销售员当天的销售额表***\n");
	for (i = 0; i < 5; i++) {
		printf("%d号产品:\n", i + 1);
		for (j = 0; j < 4; j++)
			printf("销售员%d\t销售金额%f\n", (int)s[i][j][1], s[i][j][0]);
	}
	printf("**********************************\n");
	//查询销售员当天的产品任务表
	pt = head;
	float c[4][5][2] = { 0,1,0,2,0,3,0,4,0,5 , 0,1,0,2,0,3,0,4,0,5 , 0,1,0,2,0,3,0,4,0,5 , 0,1,0,2,0,3,0,4,0,5 };
	while (pt != NULL) {
		if (pt->d == d) {
			switch (pt->sc) {//按销售员代号分类
			case 1:
				switch (pt->pc) {
				case 1:c[0][0][0] += pt->sale; break;
				case 2:c[0][1][0] += pt->sale; break;
				case 3:c[0][2][0] += pt->sale; break;
				case 4:c[0][3][0] += pt->sale; break;
				case 5:c[0][4][0] += pt->sale; break;
				} break;                                                                 //按产品代号分别进行存储
			case 2:
				switch (pt->pc) {
				case 1:c[1][0][0] += pt->sale; break;
				case 2:c[1][1][0] += pt->sale; break;
				case 3:c[1][2][0] += pt->sale; break;
				case 4:c[1][3][0] += pt->sale; break;
				case 5:c[1][4][0] += pt->sale; break;
				} break;
			case 3:switch (pt->pc) {
			case 1:c[2][0][0] += pt->sale; break;
			case 2:c[2][1][0] += pt->sale; break;
			case 3:c[2][2][0] += pt->sale; break;
			case 4:c[2][3][0] += pt->sale; break;
			case 5:c[2][4][0] += pt->sale; break;
			} break;
			case 4:
				switch (pt->pc) {
				case 1:c[3][0][0] += pt->sale; break;
				case 2:c[3][1][0] += pt->sale; break;
				case 3:c[3][2][0] += pt->sale; break;
				case 4:c[3][3][0] += pt->sale; break;
				case 5:c[3][4][0] += pt->sale; break;
				} break;
			}
		}
		pt = pt->next;//指向下一个结点
	}
	for (k = 0; k < 4; k++)
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4 - i; j++)
				if (c[k][j][0] > c[k][j + 1][0]) {
					t1 = c[k][j][0];
					t2 = c[k][j][1];
					c[k][j][0] = c[k][j + 1][0];
					c[k][j][1] = c[k][j + 1][1];
					c[k][j + 1][0] = t1;
					c[k][j + 1][1] = t2;
				}
	printf("***销售员当天的产品任务表***\n");
	for (i = 0; i < 4; i++) {
		printf("%d号销售员:\n", i + 1);
		for (j = 0; j < 5; j++)
			printf("产品%d\n", (int)c[i][j][1]);
	}
	printf("****************************\n");
	//产品当天的销量表
	pt = head;
	float b[5][2] = { 0,1,0,2,0,3,0,4,0,5 };
	while (pt != NULL) {
		if ((pt->d) == d)
			switch (pt->pc) {//按照产品的代号分别进行存储
			case 1:b[0][0] += pt->sale; break;
			case 2:b[1][0] += pt->sale; break;
			case 3:b[2][0] += pt->sale; break;
			case 4:b[3][0] += pt->sale; break;
			case 5:b[4][0] += pt->sale; break;
			}
		pt = pt->next;//指向下一个结点
	}
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4 - i; j++)
			if (b[j][0] > b[j + 1][0]) {
				t1 = b[j][0];
				t2 = b[j][1];
				b[j][0] = b[j + 1][0];
				b[j][1] = b[j + 1][1];
				b[j + 1][0] = t1;
				b[j + 1][1] = t2;
			}

	printf("***产品当天的销量表***\n");
	for (i = 0; i < 5; i++) {
		printf("产品%d 销售额%f\n", (int)b[i][1], b[i][0]);
	}
	printf("**********************\n");
	//存入文档中
	FILE* fp;
	if ((fp = fopen("Check Statement.txt", "w+")) == NULL) {//开新的文件，用来存储check中的报表
		printf("can't open file!\n");
		exit(0);
	}
	fprintf(fp, "***每种产品销售员当天的销售额表***\n");
	for (i = 0; i < 5; i++) {
		fprintf(fp, "%d号产品:\n", i + 1);
		for (j = 0; j < 4; j++)
			fprintf(fp, "销售员 % d\t销售金额 %f\n", (int)s[i][j][1], s[i][j][0]);
	}
	fprintf(fp, "**********************************\n");
	fprintf(fp, "***销售员当天的产品任务表***\n");
	for (i = 0; i < 4; i++) {
		fprintf(fp, "%d号销售员:\n", i + 1);
		for (j = 0; j < 5; j++)
			fprintf(fp, "产品%d\n", (int)c[i][j][1]);
	}
	fprintf(fp, "****************************\n");
	fprintf(fp, "***产品当天的销量表***\n");
	for (i = 0; i < 5; i++) {
		fprintf(fp, "产品%d 销售额%f\n", (int)b[i][1], b[i][0]);
	}
	fprintf(fp, "**********************\n");
	fclose(fp);//关闭文件
}

//4.历史数据存储
void historydata(struct salesman* p) {
	FILE* fp;
	if ((fp = fopen("data.txt", "w+")) == NULL) {
		printf("can't open file!\n");
		exit(0);
	}
	while (p != NULL) {
		fprintf(fp, "%d %d %d %f\n", p->d, p->sc, p->pc, p->sale);//将数据录入到文件data中存储
		p = p->next;//指向下一个结点
	}
	fclose(fp);//关闭文件
}
//5.历史数据查询
void historycheck(struct salesman* p) {
	struct salesman* pt = p, * head = p;
	int i, t = 0, j, k, t1, t2;
	//统计一周每种产品销量表
	float a[M][5][2] = { 0 };
	FILE* fp;
	if ((fp = fopen("file1.txt", "w+")) == NULL) {
		printf("can't open file!\n");
		exit(0);
	}
	for (i = 0; pt != NULL; ) {
		if (pt->d <= 7 * (i + 1) && pt->d > 7 * i)//一周内
		{
			a[i][0][1] = 1;
			a[i][1][1] = 2;
			a[i][2][1] = 3;
			a[i][3][1] = 4;
			a[i][4][1] = 5;
			switch (pt->pc) {                       //按照产品的代号进行分类，分别累积金额
			case 1:a[i][0][0] += pt->sale; break;
			case 2:a[i][1][0] += pt->sale; break;
			case 3:a[i][2][0] += pt->sale; break;
			case 4:a[i][3][0] += pt->sale; break;
			case 5:a[i][4][0] += pt->sale; break;
			}
			pt = pt->next;						  //指向下一结点
		}
		else i++;
	}
	t = i + 1;//记录多少个周
	for (i = 0; i < t; i++)
		for (j = 0; j < 4; j++)
			for (k = 0; k < 4 - j; k++)
				if (a[i][k][0] > a[i][k + 1][0]) {
					t1 = a[i][k][0];
					t2 = a[i][k][1];
					a[i][k][0] = a[i][k + 1][0];
					a[i][k][1] = a[i][k + 1][1];
					a[i][k + 1][0] = t1;
					a[i][k + 1][1] = t2;
				}
	//在输出的同时将一周每种产品销量表录入文件中
	printf("***每一周每种产品销量表***\n");
	fprintf(fp, "***每一周每种产品销量表***\n");
	for (i = 0; i < t; i++) {
		printf("         *第%d周*         \n", i + 1);
		fprintf(fp, "         *第%d周*         \n", i + 1);
		for (j = 0; j < 5; j++) {
			printf("产品%d\t销售金额%f\n", (int)a[i][j][1], a[i][j][0]);
			fprintf(fp, "产品%d\t销售金额%f\n", (int)a[i][j][1], a[i][j][0]);
		}
	}
	printf("**************************\n");
	fprintf(fp, "**************************\n");
	//统计销售员的产品销售任务表
	pt = head;
	float b[4][5][2] = { 0,1,0,2,0,3,0,4,0,5,  0,1,0,2,0,3,0,4,0,5,  0,1,0,2,0,3,0,4,0,5 ,0,1,0,2,0,3,0,4,0,5 };//用来存储产品代号和产品销售总金额
	for (i = 0; i < n; i++) {
		switch (pt->sc) {                                        //按照销售员代号分类，累积产品销售总金额
		case 1:b[0][(pt->pc) - 1][0] += pt->sale; break;
		case 2:b[1][(pt->pc) - 1][0] += pt->sale; break;
		case 3:b[2][(pt->pc) - 1][0] += pt->sale; break;
		case 4:b[3][(pt->pc) - 1][0] += pt->sale; break;
		}
		pt = pt->next;                                           //指向下一个结点
	}
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			for (k = 0; k < 4 - j; k++)
				if (b[i][k][0] > b[i][k + 1][0]) {
					t1 = b[i][k][0];
					t2 = b[i][k][1];
					b[i][k][0] = b[i][k + 1][0];
					b[i][k][1] = b[i][k + 1][1];
					b[i][k + 1][0] = t1;
					b[i][k + 1][1] = t2;
				}
	//在输出的同时将销售员的产品销售任务表录入文件中
	printf("***销售员的产品销售任务表***\n");
	fprintf(fp, "***销售员的产品销售任务表***\n");
	for (i = 0; i < 4; i++)
	{
		printf("%d号销售员\n", i + 1);
		fprintf(fp, "%d号销售员\n", i + 1);
		for (j = 0; j < 5; j++) {
			printf("产品%d\t销售金额%f\n", (int)b[i][j][1], b[i][j][0]);
			fprintf(fp, "产品%d\t销售金额%f\n", (int)b[i][j][1], b[i][j][0]);
		}
	}
	printf("****************************\n");
	fprintf(fp, "****************************\n");
	fclose(fp);//关闭文件
}
//6.历史数据统计
void historycount(struct salesman* p) {
	struct salesman* pt = p, * head = p;
	int i, j, t = 0;
	FILE* fp;
	if ((fp = fopen("file2.txt", "w+")) == NULL) {
		printf("can't open file!\n");
		exit(0);
	}
	//统计一周每种商品的销售额
	float a[M][5][2] = { 0 };
	for (i = 0; pt != NULL; ) {
		if (pt->d <= 7 * (i + 1) && pt->d > 7 * i)//一周内
		{
			a[i][0][1] = 1;
			a[i][1][1] = 2;
			a[i][2][1] = 3;
			a[i][3][1] = 4;
			a[i][4][1] = 5;
			switch (pt->pc) {                       //按照产品的代号进行分类，分别累积金额
			case 1:a[i][0][0] += pt->sale; break;
			case 2:a[i][1][0] += pt->sale; break;
			case 3:a[i][2][0] += pt->sale; break;
			case 4:a[i][3][0] += pt->sale; break;
			case 5:a[i][4][0] += pt->sale; break;
			}
			pt = pt->next;						  //指向下一结点
		}
		else i++;
	}
	t = i + 1;
	fprintf(fp, "***一周每种商品的销售额***\n");
	for (i = 0; i < t; i++) {
		fprintf(fp, "***第%d周***\n", i + 1);
		for (j = 0; j < 5; j++)
			fprintf(fp, "产品%d 销售额%f\n", (int)a[i][j][1], a[i][j][0]);
	}
	fprintf(fp, "**************************\n");
	//统计销售员的产品销售任务表
	pt = head;
	float b[4][5][2] = { 0,1,0,2,0,3,0,4,0,5,  0,1,0,2,0,3,0,4,0,5,  0,1,0,2,0,3,0,4,0,5 ,0,1,0,2,0,3,0,4,0,5 };//用来存储产品代号和产品销售总金额
	for (i = 0; i < n; i++) {
		switch (pt->sc) {                                        //按照销售员代号分类，累积产品销售总金额
		case 1:b[0][(pt->pc) - 1][0] += pt->sale; break;
		case 2:b[1][(pt->pc) - 1][0] += pt->sale; break;
		case 3:b[2][(pt->pc) - 1][0] += pt->sale; break;
		case 4:b[3][(pt->pc) - 1][0] += pt->sale; break;
		}
		pt = pt->next;                                           //指向下一个结点
	}
	fprintf(fp, "***销售员的产品销售任务表***\n");
	for (i = 0; i < 4; i++) {
		fprintf(fp, "%d号销售员\n", i + 1);
		for (j = 0; j < 5; j++)
			fprintf(fp, "产品%d\t销售金额%f\n", (int)b[i][j][1], b[i][j][0]);
	}
	fprintf(fp, "****************************\n");
	fclose(fp);//关闭文件
}
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}
void HideCursor()
{
	HANDLE fd = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cinfo;
	cinfo.bVisible = 0;
	cinfo.dwSize = 1;
	SetConsoleCursorInfo(fd, &cinfo);
}
//高亮光标
void show(int line) {//高亮的部分
	gotoxy(0, 0);
	mainMenu();
	gotoxy(0, line);
	if (line == 1)
		printf("\033[1;34;45m*           1.录入信息         *\n\033[0m");
	if (line == 2)
		printf("\033[1;34;45m*           2.统计功能         *\n\033[0m");
	if (line == 3)
		printf("\033[1;34;45m*           3.查询功能         *\n\033[0m");
	if (line == 4)
		printf("\033[1;34;45m*           4.历史数据         *\n\033[0m");
	if (line == 5)
		printf("\033[1;34;45m*           5.历史数据查询     *\n\033[0m");
	if (line == 6)
		printf("\033[1;34;45m*           6.历史数据统计     *\n\033[0m");
	if (line == 7)
		printf("\033[1;34;45m*           7.退出             *\n\033[0m");
}
//菜单页面设计
void menu(struct salesman* p) {
	char b, d, ch;
	int l, sec;
	long long j;
	time_t t;
	struct tm* l_t;
	time(&t);
	l_t = localtime(&t);
	sec = l_t->tm_sec;
	printf("TIME:%d/%d/%d %d %d:%d:\n", l_t->tm_year + 1900, l_t->tm_mon, l_t->tm_wday, l_t->tm_hour, l_t->tm_min, l_t->tm_sec);	//获取当地时间
	while (1) {
		system("cls");                                                     //清屏
		system("color 1F");                                                //调色
		HideCursor();
		mainMenu();
		l = 1;                                                           //初始时位置是功能的第一行
		gotoxy(0, l);
		printf("\033[1;34;45m*           1.录入信息         *\n\033[0m");//初始时高亮
		while ((b = _getch()) != '\r') {//判断是否为回车，如果是则不进行该循环
			if (b == -32) {
				d = _getch();          //去掉输入的回车
				ch = d;                //将输入的箭头字符存在ch中
			}
			if (ch == uk && l != 1) { //判断输入的方向是上键还是下键，同时判断光标的位置（首尾），改变l的值同时调用show函数，使得光标只能在七个功能之中跳动
				l--;
				show(l);
				continue;
			}
			else if (ch == dk && l != 7) {
				l++;
				show(l);
				continue;
			}
			else if (ch == uk && l == 1) {
				l = 6;
				show(l);
				continue;
			}
			else if (ch == dk && l == 7) {
				l = 1;
				show(l);
				continue;
			}
		}
		//判断行数的位置实现相对应的功能。
		if (l == 1) {
			system("cls");
			gotoxy(0, 0);
			p = creat();
		}
		else if (l == 2) {
			system("cls");
			gotoxy(0, 0);
			count(p);
		}
		else if (l == 3) {
			system("cls");
			gotoxy(0, 0);
			check(p);
		}
		else if (l == 4) {
			system("cls");
			gotoxy(0, 0);
			historydata(p);
		}
		else if (l == 5) {
			system("cls");
			gotoxy(0, 0);
			historycheck(p);
		}
		else if (l == 6) {
			system("cls");
			gotoxy(0, 0);
			historycount(p);
		}
		else if (l == 7) {
			system("cls");
			gotoxy(0, 0);
			exit(0);
		}
		do {                     //调用时间函数，延时界面
			j = pow(10, 10);
			while (j--);
			time(&t);
			l_t = localtime(&t);
			j = l_t->tm_sec - sec;
			if (j < 0)j = j + 60;
		} while (j < 5);
		sec = l_t->tm_sec;
	}
}
int main() {
	struct salesman* p = NULL;
	//p = creat();
	//check(p);
	menu(p);         //调用菜单函数
	return 0;
}