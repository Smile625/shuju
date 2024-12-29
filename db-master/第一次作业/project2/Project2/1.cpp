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
	int d;//����day
	int sc;//����Ա����salesman code 1-4
	int pc;//��Ʒ����product code 1-5
	float sale;//��Ʒ���۶�
	struct salesman* next;
};
int n = 0;//��¼��������Ŀ
int m = 0;//��¼¼�����ݵ�����
void mainMenu() {
	printf("**********���۹���ϵͳ**********\n");
	printf("*           1.¼����Ϣ         *\n");
	printf("*           2.ͳ�ƹ���         *\n");
	printf("*           3.��ѯ����         *\n");
	printf("*           4.��ʷ����         *\n");
	printf("*           5.��ʷ���ݲ�ѯ     *\n");
	printf("*           6.��ʷ����ͳ��     *\n");
	printf("*           7.�˳�             *\n");
	printf("********************************\n");
	//��ʾ�û�ѡ��
	printf("�����������������Ҫʵ�ֵĹ��ܽ��档");
}
//1.¼����Ϣ
struct salesman* creat(void) {
	struct salesman* p1, * p2;
	struct salesman* head1;
	head1 = NULL;
	printf("Please input the sale information.\nfor examlpe :\n1\n1\n4\n100.05\n");
	p1 = p2 = (struct salesman*)malloc(LEN1);
	if (p1 == NULL) { printf("�����ڴ�ʧ��"); exit(-1); }
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
		p1 = (struct salesman*)malloc(LEN1);//���ٶ�̬�洢�ռ䣬��ʼ��ַ��p1
		if (p1 == NULL) { printf("�����ڴ�ʧ��"); exit(-1); }
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
//2.ͳ������
void count(struct salesman* p) { //p������
	int i;
	struct salesman* pt = NULL, * head = p;
	pt = p;
	float a[M][5] = { 0 };//�洢ÿ�����Ʒ�������ܽ��
	//�������ÿ�����Ʒ�����۽��
	for (i = 0; pt != NULL;)
	{
		if ((pt->d) - 1 == i) {//���������i��Ӧ���ҵ���ӦԪ���ۻ����۽��
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
			pt = pt->next;//��ȡ��һ������
		}
		else i++;//��������+1     
	}
	m = i;
	pt = head;
	//�����������Ա�������۶�
	float ss[4] = { 0 };//����1-4��Ա�����ܲ�Ʒ���۽�
	for (i = 0; i < n; i++) {
		if ((pt->sc) == 1)ss[0] += pt->sale;
		else if ((pt->sc) == 2)ss[1] += pt->sale;
		else if ((pt->sc) == 3)ss[2] += pt->sale;
		else if ((pt->sc) == 4)ss[3] += pt->sale;
		pt = pt->next;//ָ����һ�����
	}
	//��󱣴浽�����ļ���
	FILE* fp;
	if ((fp = fopen("Count Statement.txt", "w+")) == NULL) {
		printf("can't open file!\n");
		exit(0);
	}
	fprintf(fp, "***ÿ�����Ʒ�����۽���***\n");
	for (i = 0; a[i][0] || a[i][1] || a[i][2] || a[i][3] || a[i][4]; i++) //ÿ�����Ʒ�����۽���
		fprintf(fp, "��%d�����۶� ��Ʒ1 %f\t��Ʒ2 %f\t��Ʒ3 %f\t��Ʒ4 %f\t��Ʒ5 %f\n", i + 1, a[i][0], a[i][1], a[i][2], a[i][3], a[i][4]);//������¼�뱨���ļ���
	fprintf(fp, "******************************\n");
	fprintf(fp, "***����Ա�����۶��***\n");
	for (i = 0; i < 4; i++)//����Ա�����۶�ı���
		fprintf(fp, "����Ա%d�ŵ������۶�Ϊ��%f\n", i + 1, ss[i]);
	fprintf(fp, "************************\n");
	fclose(fp);//�ر��ļ�
}
//3.��ѯ����
void check(struct salesman* p) {
	struct salesman* pt = NULL, * head = p;
	int d;
	printf("��������Ҫ��ѯ��������");
	scanf("%d", &d);
	pt = p;
	int i, j, k;
	float t1, t2;
	//��ѯÿ�ֲ�Ʒ����Ա��������۶��
	float s[5][4][2] = { 0,1,0,2,0,3,0,4 , 0,1,0,2,0,3,0,4, 0,1,0,2,0,3,0,4, 0,1,0,2,0,3,0,4, 0,1,0,2,0,3,0,4 };
	while (pt != NULL) {
		if (pt->d == d) {//�ҵ����������ı���
			switch (pt->pc) {//����Ʒ��
			case 1:switch (pt->sc) {//������Ա�Ĵ�������
			case 1: {s[0][0][0] = pt->sale; break; }
			case 2: {s[0][1][0] = pt->sale; break; }
			case 3: {s[0][2][0] = pt->sale; break; }
			case 4: {s[0][3][0] = pt->sale; break; }
			}break;                                                                     //�������������
			case 2:switch (pt->sc) {                                                   //��Ʒ2
			case 1: {s[1][0][0] = pt->sale;  break; }
			case 2: {s[1][1][0] = pt->sale;  break; }
			case 3: {s[1][2][0] = pt->sale;  break; }
			case 4: {s[1][3][0] = pt->sale;  break; }
			}break;
			case 3:switch (pt->sc) {                                                   //��Ʒ3
			case 1: {s[2][0][0] = pt->sale;  break; }
			case 2: {s[2][1][0] = pt->sale;  break; }
			case 3: {s[2][2][0] = pt->sale;  break; }
			case 4: {s[2][3][0] = pt->sale;  break; }
			}break;
			case 4:switch (pt->sc) {                                                  //��Ʒ4
			case 1: {s[3][0][0] = pt->sale;  break; }
			case 2: {s[3][1][0] = pt->sale;  break; }
			case 3: {s[3][2][0] = pt->sale;  break; }
			case 4: {s[3][3][0] = pt->sale;  break; }
			}break;
			case 5:switch (pt->sc) {                                                 //��Ʒ5
			case 1: {s[4][0][0] = pt->sale;  break; }
			case 2: {s[4][1][0] = pt->sale;  break; }
			case 3: {s[4][2][0] = pt->sale;  break; }
			case 4: {s[4][3][0] = pt->sale;  break; }
			}break;
			}
		}
		pt = pt->next;//ָ����һ�����
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
	//����������ͬʱ������洢�����ļ���
	printf("***ÿ�ֲ�Ʒ����Ա��������۶��***\n");
	for (i = 0; i < 5; i++) {
		printf("%d�Ų�Ʒ:\n", i + 1);
		for (j = 0; j < 4; j++)
			printf("����Ա%d\t���۽��%f\n", (int)s[i][j][1], s[i][j][0]);
	}
	printf("**********************************\n");
	//��ѯ����Ա����Ĳ�Ʒ�����
	pt = head;
	float c[4][5][2] = { 0,1,0,2,0,3,0,4,0,5 , 0,1,0,2,0,3,0,4,0,5 , 0,1,0,2,0,3,0,4,0,5 , 0,1,0,2,0,3,0,4,0,5 };
	while (pt != NULL) {
		if (pt->d == d) {
			switch (pt->sc) {//������Ա���ŷ���
			case 1:
				switch (pt->pc) {
				case 1:c[0][0][0] += pt->sale; break;
				case 2:c[0][1][0] += pt->sale; break;
				case 3:c[0][2][0] += pt->sale; break;
				case 4:c[0][3][0] += pt->sale; break;
				case 5:c[0][4][0] += pt->sale; break;
				} break;                                                                 //����Ʒ���ŷֱ���д洢
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
		pt = pt->next;//ָ����һ�����
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
	printf("***����Ա����Ĳ�Ʒ�����***\n");
	for (i = 0; i < 4; i++) {
		printf("%d������Ա:\n", i + 1);
		for (j = 0; j < 5; j++)
			printf("��Ʒ%d\n", (int)c[i][j][1]);
	}
	printf("****************************\n");
	//��Ʒ�����������
	pt = head;
	float b[5][2] = { 0,1,0,2,0,3,0,4,0,5 };
	while (pt != NULL) {
		if ((pt->d) == d)
			switch (pt->pc) {//���ղ�Ʒ�Ĵ��ŷֱ���д洢
			case 1:b[0][0] += pt->sale; break;
			case 2:b[1][0] += pt->sale; break;
			case 3:b[2][0] += pt->sale; break;
			case 4:b[3][0] += pt->sale; break;
			case 5:b[4][0] += pt->sale; break;
			}
		pt = pt->next;//ָ����һ�����
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

	printf("***��Ʒ�����������***\n");
	for (i = 0; i < 5; i++) {
		printf("��Ʒ%d ���۶�%f\n", (int)b[i][1], b[i][0]);
	}
	printf("**********************\n");
	//�����ĵ���
	FILE* fp;
	if ((fp = fopen("Check Statement.txt", "w+")) == NULL) {//���µ��ļ��������洢check�еı���
		printf("can't open file!\n");
		exit(0);
	}
	fprintf(fp, "***ÿ�ֲ�Ʒ����Ա��������۶��***\n");
	for (i = 0; i < 5; i++) {
		fprintf(fp, "%d�Ų�Ʒ:\n", i + 1);
		for (j = 0; j < 4; j++)
			fprintf(fp, "����Ա % d\t���۽�� %f\n", (int)s[i][j][1], s[i][j][0]);
	}
	fprintf(fp, "**********************************\n");
	fprintf(fp, "***����Ա����Ĳ�Ʒ�����***\n");
	for (i = 0; i < 4; i++) {
		fprintf(fp, "%d������Ա:\n", i + 1);
		for (j = 0; j < 5; j++)
			fprintf(fp, "��Ʒ%d\n", (int)c[i][j][1]);
	}
	fprintf(fp, "****************************\n");
	fprintf(fp, "***��Ʒ�����������***\n");
	for (i = 0; i < 5; i++) {
		fprintf(fp, "��Ʒ%d ���۶�%f\n", (int)b[i][1], b[i][0]);
	}
	fprintf(fp, "**********************\n");
	fclose(fp);//�ر��ļ�
}

//4.��ʷ���ݴ洢
void historydata(struct salesman* p) {
	FILE* fp;
	if ((fp = fopen("data.txt", "w+")) == NULL) {
		printf("can't open file!\n");
		exit(0);
	}
	while (p != NULL) {
		fprintf(fp, "%d %d %d %f\n", p->d, p->sc, p->pc, p->sale);//������¼�뵽�ļ�data�д洢
		p = p->next;//ָ����һ�����
	}
	fclose(fp);//�ر��ļ�
}
//5.��ʷ���ݲ�ѯ
void historycheck(struct salesman* p) {
	struct salesman* pt = p, * head = p;
	int i, t = 0, j, k, t1, t2;
	//ͳ��һ��ÿ�ֲ�Ʒ������
	float a[M][5][2] = { 0 };
	FILE* fp;
	if ((fp = fopen("file1.txt", "w+")) == NULL) {
		printf("can't open file!\n");
		exit(0);
	}
	for (i = 0; pt != NULL; ) {
		if (pt->d <= 7 * (i + 1) && pt->d > 7 * i)//һ����
		{
			a[i][0][1] = 1;
			a[i][1][1] = 2;
			a[i][2][1] = 3;
			a[i][3][1] = 4;
			a[i][4][1] = 5;
			switch (pt->pc) {                       //���ղ�Ʒ�Ĵ��Ž��з��࣬�ֱ��ۻ����
			case 1:a[i][0][0] += pt->sale; break;
			case 2:a[i][1][0] += pt->sale; break;
			case 3:a[i][2][0] += pt->sale; break;
			case 4:a[i][3][0] += pt->sale; break;
			case 5:a[i][4][0] += pt->sale; break;
			}
			pt = pt->next;						  //ָ����һ���
		}
		else i++;
	}
	t = i + 1;//��¼���ٸ���
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
	//�������ͬʱ��һ��ÿ�ֲ�Ʒ������¼���ļ���
	printf("***ÿһ��ÿ�ֲ�Ʒ������***\n");
	fprintf(fp, "***ÿһ��ÿ�ֲ�Ʒ������***\n");
	for (i = 0; i < t; i++) {
		printf("         *��%d��*         \n", i + 1);
		fprintf(fp, "         *��%d��*         \n", i + 1);
		for (j = 0; j < 5; j++) {
			printf("��Ʒ%d\t���۽��%f\n", (int)a[i][j][1], a[i][j][0]);
			fprintf(fp, "��Ʒ%d\t���۽��%f\n", (int)a[i][j][1], a[i][j][0]);
		}
	}
	printf("**************************\n");
	fprintf(fp, "**************************\n");
	//ͳ������Ա�Ĳ�Ʒ���������
	pt = head;
	float b[4][5][2] = { 0,1,0,2,0,3,0,4,0,5,  0,1,0,2,0,3,0,4,0,5,  0,1,0,2,0,3,0,4,0,5 ,0,1,0,2,0,3,0,4,0,5 };//�����洢��Ʒ���źͲ�Ʒ�����ܽ��
	for (i = 0; i < n; i++) {
		switch (pt->sc) {                                        //��������Ա���ŷ��࣬�ۻ���Ʒ�����ܽ��
		case 1:b[0][(pt->pc) - 1][0] += pt->sale; break;
		case 2:b[1][(pt->pc) - 1][0] += pt->sale; break;
		case 3:b[2][(pt->pc) - 1][0] += pt->sale; break;
		case 4:b[3][(pt->pc) - 1][0] += pt->sale; break;
		}
		pt = pt->next;                                           //ָ����һ�����
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
	//�������ͬʱ������Ա�Ĳ�Ʒ���������¼���ļ���
	printf("***����Ա�Ĳ�Ʒ���������***\n");
	fprintf(fp, "***����Ա�Ĳ�Ʒ���������***\n");
	for (i = 0; i < 4; i++)
	{
		printf("%d������Ա\n", i + 1);
		fprintf(fp, "%d������Ա\n", i + 1);
		for (j = 0; j < 5; j++) {
			printf("��Ʒ%d\t���۽��%f\n", (int)b[i][j][1], b[i][j][0]);
			fprintf(fp, "��Ʒ%d\t���۽��%f\n", (int)b[i][j][1], b[i][j][0]);
		}
	}
	printf("****************************\n");
	fprintf(fp, "****************************\n");
	fclose(fp);//�ر��ļ�
}
//6.��ʷ����ͳ��
void historycount(struct salesman* p) {
	struct salesman* pt = p, * head = p;
	int i, j, t = 0;
	FILE* fp;
	if ((fp = fopen("file2.txt", "w+")) == NULL) {
		printf("can't open file!\n");
		exit(0);
	}
	//ͳ��һ��ÿ����Ʒ�����۶�
	float a[M][5][2] = { 0 };
	for (i = 0; pt != NULL; ) {
		if (pt->d <= 7 * (i + 1) && pt->d > 7 * i)//һ����
		{
			a[i][0][1] = 1;
			a[i][1][1] = 2;
			a[i][2][1] = 3;
			a[i][3][1] = 4;
			a[i][4][1] = 5;
			switch (pt->pc) {                       //���ղ�Ʒ�Ĵ��Ž��з��࣬�ֱ��ۻ����
			case 1:a[i][0][0] += pt->sale; break;
			case 2:a[i][1][0] += pt->sale; break;
			case 3:a[i][2][0] += pt->sale; break;
			case 4:a[i][3][0] += pt->sale; break;
			case 5:a[i][4][0] += pt->sale; break;
			}
			pt = pt->next;						  //ָ����һ���
		}
		else i++;
	}
	t = i + 1;
	fprintf(fp, "***һ��ÿ����Ʒ�����۶�***\n");
	for (i = 0; i < t; i++) {
		fprintf(fp, "***��%d��***\n", i + 1);
		for (j = 0; j < 5; j++)
			fprintf(fp, "��Ʒ%d ���۶�%f\n", (int)a[i][j][1], a[i][j][0]);
	}
	fprintf(fp, "**************************\n");
	//ͳ������Ա�Ĳ�Ʒ���������
	pt = head;
	float b[4][5][2] = { 0,1,0,2,0,3,0,4,0,5,  0,1,0,2,0,3,0,4,0,5,  0,1,0,2,0,3,0,4,0,5 ,0,1,0,2,0,3,0,4,0,5 };//�����洢��Ʒ���źͲ�Ʒ�����ܽ��
	for (i = 0; i < n; i++) {
		switch (pt->sc) {                                        //��������Ա���ŷ��࣬�ۻ���Ʒ�����ܽ��
		case 1:b[0][(pt->pc) - 1][0] += pt->sale; break;
		case 2:b[1][(pt->pc) - 1][0] += pt->sale; break;
		case 3:b[2][(pt->pc) - 1][0] += pt->sale; break;
		case 4:b[3][(pt->pc) - 1][0] += pt->sale; break;
		}
		pt = pt->next;                                           //ָ����һ�����
	}
	fprintf(fp, "***����Ա�Ĳ�Ʒ���������***\n");
	for (i = 0; i < 4; i++) {
		fprintf(fp, "%d������Ա\n", i + 1);
		for (j = 0; j < 5; j++)
			fprintf(fp, "��Ʒ%d\t���۽��%f\n", (int)b[i][j][1], b[i][j][0]);
	}
	fprintf(fp, "****************************\n");
	fclose(fp);//�ر��ļ�
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
//�������
void show(int line) {//�����Ĳ���
	gotoxy(0, 0);
	mainMenu();
	gotoxy(0, line);
	if (line == 1)
		printf("\033[1;34;45m*           1.¼����Ϣ         *\n\033[0m");
	if (line == 2)
		printf("\033[1;34;45m*           2.ͳ�ƹ���         *\n\033[0m");
	if (line == 3)
		printf("\033[1;34;45m*           3.��ѯ����         *\n\033[0m");
	if (line == 4)
		printf("\033[1;34;45m*           4.��ʷ����         *\n\033[0m");
	if (line == 5)
		printf("\033[1;34;45m*           5.��ʷ���ݲ�ѯ     *\n\033[0m");
	if (line == 6)
		printf("\033[1;34;45m*           6.��ʷ����ͳ��     *\n\033[0m");
	if (line == 7)
		printf("\033[1;34;45m*           7.�˳�             *\n\033[0m");
}
//�˵�ҳ�����
void menu(struct salesman* p) {
	char b, d, ch;
	int l, sec;
	long long j;
	time_t t;
	struct tm* l_t;
	time(&t);
	l_t = localtime(&t);
	sec = l_t->tm_sec;
	printf("TIME:%d/%d/%d %d %d:%d:\n", l_t->tm_year + 1900, l_t->tm_mon, l_t->tm_wday, l_t->tm_hour, l_t->tm_min, l_t->tm_sec);	//��ȡ����ʱ��
	while (1) {
		system("cls");                                                     //����
		system("color 1F");                                                //��ɫ
		HideCursor();
		mainMenu();
		l = 1;                                                           //��ʼʱλ���ǹ��ܵĵ�һ��
		gotoxy(0, l);
		printf("\033[1;34;45m*           1.¼����Ϣ         *\n\033[0m");//��ʼʱ����
		while ((b = _getch()) != '\r') {//�ж��Ƿ�Ϊ�س���������򲻽��и�ѭ��
			if (b == -32) {
				d = _getch();          //ȥ������Ļس�
				ch = d;                //������ļ�ͷ�ַ�����ch��
			}
			if (ch == uk && l != 1) { //�ж�����ķ������ϼ������¼���ͬʱ�жϹ���λ�ã���β�����ı�l��ֵͬʱ����show������ʹ�ù��ֻ�����߸�����֮������
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
		//�ж�������λ��ʵ�����Ӧ�Ĺ��ܡ�
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
		do {                     //����ʱ�亯������ʱ����
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
	menu(p);         //���ò˵�����
	return 0;
}