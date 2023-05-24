#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#define AREA sizeof(struct student)
#define MANAGER_NAME "1"
#define MANAGER_PASSWORD "1"
typedef struct Student
{
	char admin[15];			//ѧ����¼�˻�
	char password[15];		//ѧ���˻����� 
	char name[10];          //����
	char grade[10];         //�꼶
	char number[20];        //ѧ��
	char graduation[10];	//��ҵ״��
	int birth[3];           //���գ������գ�
	char department[20];    //Ժϵ
	float credit[4];		//ѧ��
	float score[4];			//�ɼ�
	float gpa[4];			//����
	int rank;				//����
	struct Student* pnext;
}STU, * PSTU;
typedef struct Teacher
{
	char admin[15];			//��ʦ��¼�˻�
	char password[15];		//��ʦ�˻����� 
	char name[10];         //����
	char number[20];       //ѧ��
	char department[20];   //Ժϵ
	struct Student* pnext;
}TEA, * PTEA;
PSTU shead = NULL;
PSTU snew = NULL;
PTEA thead = NULL;
PTEA tnew = NULL;
int Count_stu = 0;  //��ʾѧ������
int Count_tea = 0;//��ʾ��ʦ����
char UserName[15];//�ݴ����Ա�˻� 
char UserWord[15];//�ݴ����Ա���� 
char TeaName[15];//�ݴ���ʦ�˻�
char TeaWord[15];//�ݴ���ʦ����
char TeaWord_temp[15];//ͨ��judge_admin()���ҵ���Ӧ�˺ŵ�����
char StuName[15];//�ݴ�ѧ���˻� 
char StuWord[15];//�ݴ�ѧ������ 
char StuWord_temp[15];//ͨ��judge_admin()���ҵ��Ķ�Ӧ�˺ŵ����� 

//*********************************************

void Menu();//�˵���ʼ������
void Fimport();//�����ļ�����
void Fexport();//�����ļ�����
void Exit(int);//ȷ���˳�����
void swap(PSTU stu1, PSTU stu2);//�������ݺ���

//*********************************************

void master();//����Ա�������溯��
void Login_master(int);//����Ա��¼����
void isLogin_master(int);//�жϹ���Ա��¼����
void appear();//��ʾѧ����Ϣ����
void add();//���ѧ����Ϣ����
void change();//�޸�ѧ����Ϣ����
void Delete();//ɾ��ѧ����Ϣ����

void view_department(); //רҵ��ѯ

int judge_admin(char*);//�ж��Ƿ�������˻��Ѿ����� 
int judge_number(char*);//�ж��Ƿ������ѧ���Ѿ�����
int day(int, int, int);//�ж����շ��Ϻ���

//********************************************* 

void stu();//ѧ���������溯��
void tea();
void Login_tea(int);
void Login_stu(int);//ѧ����¼���� 
void isLogin_stu(int);//�ж�ѧ����¼���� 
void search();//��ѯѧ����Ϣ����
void vrank();
int irank(char);
void update_rank();
double get_score(char* num);
void insert(PSTU p);
void score();//ѧ���ܷ�ƽ���ֺ͵���ƽ����
float gpa(float);//ѧ����ѧ�Ƽ���
void order();//��Ϣ������
void grade();//��ѯ������׼�µ�ѧ�������͵��ƻ�ȫ�Ƴɼ���һ��ѧ��

/****************************************

��������main
������������
�����������
�Զ���������
�����������
����ֵ����
���ú�����void Menu()

�޸���ʷ��
1.���ڣ�2020.5.23
���ߣ���λ�
�޸����ݣ������ɺ���

****************************************/
int main()
{
	Menu();

	return 0;
}
/****************************************

��������Menu
������������ʾ���˵����沢����ѡ�����к���
�����������
�Զ�������1.ѡ�����choice
�����������
����ֵ����
���ú�����

�޸���ʷ��
1.���ڣ�2020.5.23
���ߣ���λ�
�޸����ݣ������ɺ���

****************************************/
void Menu()
{
	int choice;
	if (shead == NULL)
	{
		shead = (PSTU)malloc(sizeof(STU));
		shead->pnext = NULL;
		Fimport();
	}
	system("cls");
	while (1)
	{
		printf("��ӭʹ��ѧ����Ϣ����ϵͳ��\n");
		printf("�밴����������Ĺ��ܱ���й���ѡ��\n");
		printf("1.ѧ��		2.��ʦ		3.����Ա\n");
		printf("0.�˳�ϵͳ\n");
		fflush(stdin);
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:system("cls"); getchar(); Login_stu(0); stu(); Exit(0); break;
		case 2:system("cls"); getchar(); Login_stu(0); tea(); Exit(0); break;
		case 3:system("cls"); getchar(); Login_master(0); master(); Exit(0); break;
		case 0:system("cls"); Exit(0); break;
		default: {printf("��Чָ�����������"); Sleep(1000); system("cls"); break; }
		}
	}
}
/***************************************

��������Fimport
���������������ļ�����
�����������
�����������
����ֵ����
���ú�������

�޸���ʷ��
1.���ڣ�2020.05.30
���ߣ���λ�
�޸����ݣ������ɺ���

***************************************/
void Fimport()
{
	FILE* fRead = fopen("D:\\stuInformation.dat", "rb");
	if (fRead == NULL)
	{
		Fexport();
		return;
	}
	rewind(fRead);
	while (1)
	{
		snew = (PSTU)malloc(sizeof(STU));
		fread(snew, sizeof(STU), 1, fRead);
		if (feof(fRead)) break;
		snew->pnext = shead->pnext;
		shead->pnext = snew;
		snew = NULL;
		Count_stu++;
	}
	fclose(fRead);

	FILE* fReads = fopen("D:\\teaInformation.dat", "rb");
	if (fReads == NULL)
	{
		Fexport();
		return;
	}
	rewind(fReads);
	while (1)
	{
		snew = (PTEA)malloc(sizeof(TEA));
		fread(tnew, sizeof(TEA), 1, fReads);
		if (feof(fReads)) break;
		tnew->pnext = thead->pnext;
		thead->pnext = tnew;
		tnew = NULL;
		Count_tea++;
	}
	fclose(fReads);
}
/***************************************

��������Fexport
�����������ļ���������
�����������
�����������
����ֵ����
���ú�������

�޸���ʷ��
1.���ڣ�2020.05.30
���ߣ���λ�
�޸����ݣ������ɺ���

***************************************/
void Fexport()
{
	FILE* fWrite = fopen("D:\\stuInformation.dat", "wb");
	if (fWrite == NULL)
	{
		system("cls");
		printf("����ʧ��...\n");
		Sleep(1000);
		exit(0);
	}
	PSTU pCurrent = shead->pnext;
	while (pCurrent != NULL)
	{
		fwrite(pCurrent, sizeof(STU), 1, fWrite);
		pCurrent = pCurrent->pnext;
	}
	pCurrent = NULL;
	fclose(fWrite);
}
/***************************************

��������Exit
�����������˳���������½������
���������int x����ʾ��ǰ�ĳ���״̬��
����ֵ����
���ú�����Menu������stu������master����

�޸���ʷ��
1.���ڣ�2020.5.31
���ߣ���λ�
�޸����ݣ������ɺ���

***************************************/
void Exit(int x)
{
	char ch;
	if (x == 0)
	{
		printf("\n\t\n�˳��밴Esc,������ص�������\n");
		ch = getch();
		if (ch == 0x1b)
		{
			Fexport();
			exit(0);
		}
		Menu();
	}
	else if (x == 1)
	{

		while (1)
		{
			printf("\n\t");
			printf("\nҪ����ѧ��������������밴1\t����ϵͳ�������밴2\t�˳������������밴Esc\n");
			ch = getch();
			if (ch == 0x1b)
			{
				Fexport();
				exit(0);
			}
			else if (ch == '1')
				stu();
			else if (ch == '2')
				Menu();
			else
				printf("��Ч���룡");
			system("cls");
		}
	}
	else if (x == 2)
	{
		while (1)
		{
			printf("\n\t");
			printf("\nҪ���ع���Ա������������밴1\t����ϵͳ�������밴2\t�˳������������밴Esc\n");
			ch = getch();
			if (ch == 0x1b)
			{
				Fexport();
				exit(0);
			}
			else if (ch == '1')
				master();
			else if (ch == '2')
				Menu();
			else
				printf("��Ч���룡");
			system("cls");
		}

	}
}
/****************************************

��������swap
����������ʵ���������ݸ���
���������PSTU stu1
PSTU stu2
�����������
����ֵ����
���ú�������

�޸���ʷ��
1.���ڣ�2020.05.24
���ߣ���λ�
�޸����ݣ������ɺ���

****************************************/
void swap(PSTU stu1, PSTU stu2)
{
	strcpy(stu1->admin, stu2->admin);
	strcpy(stu1->password, stu2->password);
	strcpy(stu1->name, stu2->name);
	strcpy(stu1->grade, stu2->grade);
	strcpy(stu1->number, stu2->number);
	stu1->birth[0] = stu2->birth[0];
	stu1->birth[1] = stu2->birth[1];
	stu1->birth[2] = stu2->birth[2];
	strcpy(stu1->department, stu2->department);
	stu1->score[0] = stu2->score[0];
	stu1->score[1] = stu2->score[1];
	stu1->score[2] = stu2->score[2];
	stu1->score[3] = stu2->score[3];
	stu1->gpa[0] = stu2->gpa[0];
	stu1->gpa[1] = stu2->gpa[1];
	stu1->gpa[2] = stu2->gpa[2];
	stu1->gpa[3] = stu2->gpa[3];
}
/****************************************

��������master
��������������Ա��������
�����������
����ֵ����
���ú�����appear������add������change������Delete������Exit������Sleep������system����

�޸���ʷ��
1.���ڣ�2020.06.29
���ߣ���λ�
�޸����ݣ������ɺ���

****************************************/
void master()
{
	int choice;
	system("cls");
	fflush(stdin);
	printf("��ӭʹ��ѧ����Ϣ����ϵͳ��\n");
	printf("�밴����������Ĺ��ܱ���й���ѡ��\n");
	printf("1.��ʾѧ����Ϣ             2.���ѧ����Ϣ\n");
	printf("3.�޸�ѧ����Ϣ             4.ɾ��ѧ����Ϣ\n");
	printf("5.��ѯרҵѧ����Ϣ		  0.�˳�ϵͳ\n");
	fflush(stdin);
	scanf("%d", &choice);
	while (1)
	{
		switch (choice)
		{
		case 1:system("cls"); appear(); Exit(2); break;
		case 2:system("cls"); add(); Exit(2); break;
		case 3:system("cls"); change(); Exit(2); break;
		case 4:system("cls"); Delete(); Exit(2); break;
		case 5:system("cls"); view_department(); Exit(2); break;

		case 0:Exit(2); break;
		default: {printf("��Чָ�����������"); Sleep(1000); system("cls"); break; }
		}

	}
}
/****************************************

��������Login_master
��������������ϵͳ����
���������int n
�����������
����ֵ����
���ú�����isLogin_master(int n)

�޸���ʷ��
1.���ڣ�2020.5.23
���ߣ���λ�
�޸����ݣ������ɺ���
2.���ڣ�2021.12.29
���ߣ���λ�
�޸����ݣ���������֤����������߼������������ʾ�Ĵ�������쳣����

****************************************/
void Login_master(int n)
{
	int c, i;
	char ch;
	char xing[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" };
	c = strlen(xing);
	for (i = 0; i < c; i++)
	{
		printf("%c", xing[i]);
		Sleep(10);
	}
	printf("\n\n\t\t\t\t\t\t�����������˺�����:\n\n\n\n\t\t\t\t\t\t�˺�:");
	gets(UserName);
	printf("\n\n\t\t\t\t\t\t����:");
	//gets(UserWord);
	i = 0;
	while (1)
	{
		ch = getch();
		if (ch == '\r')
			break;
		if (ch == '\b')
		{
			if (i > 0)
			{
				i--;
				printf("\b \b");
				ch = '\0';
				continue;
			}
		}
		else
		{
			printf("*");
			UserWord[i] = ch;
			if (i < 20) i++;
		}
	}
	UserWord[i] = '\0';
	isLogin_master(n);
}
/****************************************

��������isLogin_master
�����������ж��Ƿ��¼�ɹ�
�����������
�����������
����ֵ����
���ú�����Login_master����

�޸���ʷ��
1.���ڣ�2020.5.23
���ߣ���λ�
�޸����ݣ������ɺ���

****************************************/
void isLogin_master(int n)
{
	int times = n;	//�����������
	while (!(strcmp(UserName, MANAGER_NAME) == 0 && strcmp(UserWord, MANAGER_PASSWORD) == 0))
	{
		times++;	//����������� times++
		if (times > 3)
		{
			printf("\n\n\n\n\t\t\t\t�˺Ż�������������ۼƴﵽ%d�Σ�ϵͳ����3���ر�", times);
			Sleep(1000);
			system("cls");
			char shutdown[] = { "ϵͳ����%d���ر�..." };
			for (int i = 0; i < 3; i++)
			{
				printf(shutdown, 3 - i);
				Sleep(1000);
				system("cls");
			}
			exit(0);
		}
		printf("\n\n\n\n\t\t\t\t�˺Ż������������,�㻹��%d�ε�¼���ᣬ����������µ�¼...", 4 - times);
		getch();
		system("cls");
		Login_master(times);
	}
}
/****************************************

��������appear
������������ʾѧ����Ϣ
�����������
�����������
����ֵ����
���ú�������

�޸���ʷ
1.���ڣ�2020.05.23
���ߣ���λ�
�޸����ݣ������ɺ���

****************************************/
void appear()
{
	if (shead->pnext == NULL || Count_stu == 0)
	{
		system("cls");
		printf("\n����Ϣ\n\n");
		Sleep(1000);
		system("cls");
		return;
	}
	else
	{
		system("cls");
		PSTU pcurrent = shead->pnext;
		int index = 1;
		printf("\t\t\t*************����������%d��ѧ��******************\n\n\n", Count_stu);
		printf("���\tѧ��\t\t�꼶\t����\tԺϵ\t\t\t����\t����-����-ѧ��\t�߼�-����-ѧ��\t��ɢ-����-ѧ��\t�ܷ�-ƽ������-��ѧ��\n\n");
		while (index <= Count_stu)
		{
			printf("%d\t%s\t%s\t%s\t%-18s\t%d%d%d\t%g-%g-%g\t\t%g-%g-%g\t\t%g-%g-%g\t\t%g-%.2g-%g\t\n", index, pcurrent->number, pcurrent->grade, pcurrent->name, pcurrent->department, pcurrent->birth[0], pcurrent->birth[1], pcurrent->birth[2], pcurrent->score[0], pcurrent->gpa[0], pcurrent->credit[0],pcurrent->score[1], pcurrent->gpa[1], pcurrent->credit[1], pcurrent->score[2], pcurrent->gpa[2], pcurrent->credit[2],pcurrent->score[3], pcurrent->gpa[3], pcurrent->credit[3]);
			pcurrent = pcurrent->pnext;
			index++;
		}
		pcurrent = NULL;
		
		return;
	}
}
/****************************************

��������add
�������������ѧ����Ϣ
�����������
�����������
����ֵ��
���ú�����judge_admin������judge_number����

�޸���ʷ��
1.���ڣ�2020.5.25
���ߣ���λ�
�޸����ݣ������ɺ���
2.���ڣ�2022.5.15
���ߣ���λ�
�޸����ݣ�����ѧ�����˻����룬ʹ�����ͨ���˺�������֤��¼
***************************************/
void add()
{
	fflush(stdin);
	snew = (PSTU)malloc(sizeof(STU));
	shead = (PSTU)malloc(sizeof(STU));
	shead->pnext = NULL;
	printf("���ѧ���˻�\n");
	printf("�˻�:\n");
	scanf("%s", snew->admin);
	while (judge_admin(snew->admin) == 1)
	{
		printf("���˻��Ѿ�����\n");
		printf("�����������˻�:");
		scanf("%s", snew->admin);
	}
	printf("����:\n");
	scanf("%s", snew->password);
	printf("���ѧ����Ϣ:\n");
	printf("ѧ��:");
	scanf("%s", snew->number);
	while (judge_number(snew->number) == 1)
	{
		printf("ѧ���Ѿ�����\n");
		printf("����������ѧ��:");
		scanf("%s", snew->number);
	}
	printf("\n�꼶:");
	scanf("%s", snew->grade);
	printf("\n����:");
	scanf("%s", snew->name);
	printf("\n��������:");
	scanf("%d", &snew->birth[0]);
	scanf("%d", &snew->birth[1]);
	scanf("%d", &snew->birth[2]);
	if (day(snew->birth[0], snew->birth[1], snew->birth[2]) != 0)
	{
		printf("\n��������������������:");
		scanf("%d", &snew->birth[0]);
		scanf("%d", &snew->birth[1]);
		scanf("%d", &snew->birth[2]);
	}
	printf("\nԺϵ:");
	scanf("%s", snew->department);
	printf("\n�ߵ���ѧ:");
	scanf("%f", &snew->score[0]);
	printf("\n�����߼�:");
	scanf("%f", &snew->score[1]);
	printf("\n��ɢ��ѧ:");
	scanf("%f", &snew->score[2]);
	snew->score[3] = snew->score[0] + snew->score[1] + snew->score[2];
	snew->gpa[0] = gpa(snew->score[0]);
	snew->gpa[1] = gpa(snew->score[1]);
	snew->gpa[2] = gpa(snew->score[2]);
	snew->gpa[3] = snew->gpa[0] + snew->gpa[1] + snew->gpa[2];
	snew->gpa[3] = snew->gpa[3] / 3;
	if (snew->gpa[0] != 0)
	{
		snew->credit[0] = 3.0;
	}
	else if (snew->gpa[0] == 0)
	{
		snew->credit[0] = 0;
	}
	if (snew->gpa[1] != 0)
	{
		snew->credit[1] = 2.0;
	}
	else if (snew->gpa[1] == 0)
	{
		snew->credit[1] = 0;
	}
	if (snew->gpa[2] != 0)
	{
		snew->credit[2] = 4.0;
	}
	else if (snew->gpa[2] == 0)
	{
		snew->credit[2] = 0;
	}
	snew->credit[3] = snew->credit[0] + snew->credit[1] + snew->credit[2];
	snew->rank = irank(snew->number);
	insert(snew);

	Count_stu++;
	
	PSTU p = shead->pnext;
	while (p != NULL)
	{
		PSTU q = p;
		p = p->pnext;
		free(q);
	}
	free(shead);
	snew->pnext = shead->pnext;
	shead->pnext = snew;
	snew = NULL;
	update_rank();
	return;
}
/***************************************

��������change
������������ѧ����Ϣ�����޸�
�����������
�����������
����ֵ��
���ú�����

�޸���ʷ��
1.���ڣ�2020.5.29
���ߣ���λ�
�޸����ݣ������ɺ���
2.���ڣ�2020.6.4
���ߣ���λ�
�޸����ݣ���������������к�ֱ���˳�������
//�޷�����޸�ѧ������ͬʱ�����ѣ���ʹ��judge�����ж�ʱ�����κ����־������ǳ�ͻ�ģ��ѽ���judge������
****************************************/
void change()
{

	if (shead->pnext == NULL)
	{
		printf("����Ϣ\n");
		Sleep(1000);
		system("cls");
		return;
	}
	else
	{
		char ID[20];
		char operate;
		PSTU pcurrent = shead->pnext;
		PSTU p1;
		int choice;
		int flag = 0;
		printf("�޸�ѧ����Ϣ\n");
		printf("������ѧ��ѧ�ţ�");
		scanf("%s", ID);
		while (pcurrent != NULL)
		{
			if (strcmp(pcurrent->number, ID) == 0)
			{
				printf("Ҫ�޸ĵ�ѧ����Ϣ\n");
				printf("ѧ��\t����\t����\tԺϵ\t����\t�߼�\t�ߴ�\t�ܷ�\t\n");
				printf("%s\t%s\t%d.%d.%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t", pcurrent->number, pcurrent->name, pcurrent->birth[0], pcurrent->birth[1], pcurrent->birth[2], pcurrent->department, pcurrent->score[0], pcurrent->score[1], pcurrent->score[2], pcurrent->score[3]);
				printf("�Ƿ��޸ĸ�ѧ����Ϣ(y/enter)/(n/enter):");
				fflush(stdin);
				getchar();
				operate = getchar();
				if (operate == 'y' || operate == 'Y')
				{
					printf("������Ҫ�޸ĵ�ѧ����Ϣ��\n");
					printf("1.����\t2.�꼶\t3.ѧ��\t4.Ժϵ\t5.����\t6.�ߵ���ѧ\t7.�����߼�\t8.��ɢ��ѧ\t9.����\t\n");
					scanf("%d", &choice);
					flag = 1;
					switch (choice)
					{
					case 1:printf("����������"); scanf("%s", pcurrent->name); break;
					case 2:printf("�������꼶"); scanf("%s", pcurrent->grade); break;
					case 3:
					{
						printf("������ѧ��");
						scanf("%s", pcurrent->number);
						break;
					}
					case 4:printf("������Ժϵ"); scanf("%s", pcurrent->department); break;
					case 5:
					{
						printf("����������");
						scanf("%d%d%d", &pcurrent->birth[0], &pcurrent->birth[1], &pcurrent->birth[2]);
						if (day(pcurrent->birth[0], pcurrent->birth[1], pcurrent->birth[2]) != 0)
						{
							printf("\n��������������������:");
							scanf("%d", &pcurrent->birth[0]);
							scanf("%d", &pcurrent->birth[1]);
							scanf("%d", &pcurrent->birth[2]);
						}
						break;
					}
					case 6:printf("���������"); scanf("%f", &pcurrent->score[0]); break;
					case 7:printf("���������"); scanf("%f", &pcurrent->score[1]); break;
					case 8:printf("���������"); scanf("%f", &pcurrent->score[2]); break;
					case 9:
					{
						printf("����������");
						scanf("%s", pcurrent->password);
						break;
					}
					default:printf("��Ч����\n"); break;
					}
					pcurrent->score[3] = pcurrent->score[0] + pcurrent->score[1] + pcurrent->score[2];
		
					snew->gpa[0] = gpa(pcurrent->score[0]);
					pcurrent->gpa[1] = gpa(pcurrent->score[1]);
					pcurrent->gpa[2] = gpa(pcurrent->score[2]);
					pcurrent->gpa[3] = pcurrent->gpa[0] + pcurrent->gpa[1] + pcurrent->gpa[2];
					pcurrent->gpa[3] = pcurrent->gpa[3] / 3;
					if (pcurrent->gpa[0] != 0)
					{
						pcurrent->credit[0] = 3.0;
					}
					else if (pcurrent->gpa[0] == 0)
					{
						pcurrent->credit[0] = 0;
					}
					if (pcurrent->gpa[1] != 0)
					{
						pcurrent->credit[1] = 2.0;
					}
					else if (pcurrent->gpa[1] == 0)
					{
						pcurrent->credit[1] = 0;
					}
					if (pcurrent->gpa[2] != 0)
					{
						pcurrent->credit[2] = 4.0;
					}
					else if (pcurrent->gpa[2] == 0)
					{
						pcurrent->credit[2] = 0;
					}
					pcurrent->credit[3] = pcurrent->credit[0] + pcurrent->credit[1] + pcurrent->credit[2];
					pcurrent = NULL;
					return;
				}
				else if (operate == 'n' || operate == 'N')
					Exit(2);
				else
				{
					printf("�޸�ʧ��");
					return;
				}
			}

			pcurrent = pcurrent->pnext;
		}
		if (flag == 0)
		{
			printf("δ�ҵ�Ҫ��ѯ��ѧ����Ϣ\n\n");
			pcurrent = NULL;
			return;
		}
	}
	return;
}
/***************************************

��������Delete
����������ɾ��ѧ����Ϣ
�����������
�����������
����ֵ����
���ú�������

�޸���ʷ��
1.���ڣ�2020.5.29
���ߣ���λ�
�޸����ݣ������ɺ���

***************************************/
void Delete()
{

	if (shead->pnext == NULL)
	{
		printf("����Ϣ\n");
		Sleep(1000);
		system("cls");
		return;
	}
	else
	{
		char ID[20];
		char operate;
		int flag = 0;
		PSTU pcurrent = shead;
		printf("ɾ��ѧ����Ϣ��\n");
		printf("������ѧ��ѧ�ţ�");
		scanf("%s", ID);
		while (pcurrent->pnext != NULL)
		{
			if (strcmp(pcurrent->pnext->number, ID) == 0)
			{
				printf("Ҫɾ����ѧ����Ϣ\n");
				printf("������Ҫɾ����ѧ����Ϣ��\n");
				printf("ѧ��\t\t����\t����\tԺϵ\t����\t�߼�\t�ߴ�\t�ܷ�\t\n");
				printf("%s\t%s\t%d.%d.%d\t%s\t%f\t%f\t%f\t%f\t", pcurrent->pnext->number, pcurrent->pnext->name, pcurrent->pnext->birth[0], pcurrent->pnext->birth[1], pcurrent->pnext->birth[2], pcurrent->pnext->department, pcurrent->pnext->score[0], pcurrent->pnext->score[1], pcurrent->pnext->score[2], pcurrent->pnext->score[3]);
				printf("�Ƿ�ɾ����ѧ����Ϣ(y/enter)/(n/enter)");
				fflush(stdin);
				getchar();
				operate = getchar();
				if (operate == 'y' || operate == 'Y' || operate == 13)
				{
					PSTU ptemp = pcurrent->pnext;
					pcurrent->pnext = ptemp->pnext;
					/*update_rank();*/
					free(ptemp);
					Count_stu--;
					printf("ɾ���ɹ�\n\n");
					flag = 1;
					return;
				}
				else if (operate == 'n' || operate == 'N')
				{
					Exit(2);
				}
				else
				{
					printf("ɾ��ʧ��");
					return;
				}
			}
			pcurrent = pcurrent->pnext;
		}
		if (flag == 0)
		{
			printf("δ�ҵ�Ҫɾ����ѧ����Ϣ\n");
			return;
		}
	}
}
/***************************************
��������judge_admin
�����������ж��Ƿ������ѧ���Ѿ�����
���������
����ֵ��int
���ú�������

�޸���ʷ��
1.���ڣ�2022.5.15
���ߣ���λ�
�޸����ݣ������ɺ���
***************************************/
int judge_admin(char* c)
{
	PSTU p = shead->pnext;
	for (; p != NULL; p = p->pnext)
		if (strcmp(c, p->admin) == 0)
		{
			strcpy(StuWord_temp, p->password);
			return 1;
		}

	return 0;
}
/***************************************
��������judge_number
�����������ж��Ƿ������ѧ���Ѿ�����
���������
����ֵ��int
���ú�������

�޸���ʷ��
1.���ڣ�2020.6.28
���ߣ���λ�
�޸����ݣ������ɺ���
//���޸�ģ���ж��޸��г�ͻ���޷��������У�����change�����н��ã�
***************************************/
int judge_number(char* c)
{
	PSTU p = shead->pnext;
	for (; p != NULL; p = p->pnext)
		if (strcmp(c, p->number) == 0)
			return 1;
	return 0;
}
/***************************************

��������day
�����������ж������Ƿ���ϱ�׼
���������int year��int month��int day
����ֵ��int
���ú�������

�޸���ʷ��
1.���ڣ�2020.5.29
���ߣ���λ�
�޸����ݣ������ɺ���

***************************************/
int day(int year, int month, int day)
{
	int a[2][13] = {
		{0,31,28,31,30,31,30,31,31,30,31,30,31},
		{0,31,29,31,30,31,30,31,31,30,31,30,31}
	};
	int flag = 0;
	if ((year % 4 == 0 && year % 100 != 0) || (year % 100 == 0))
		flag = 1;
	if ((year >= 2020) || (day > a[flag][month]))
		return 1;
	return 0;
}
/****************************************

��������stu
����������ѧ���������溯��
�����������
���ú�����appear������search������score������order������grade������Exit������system������fflush����

�޸���ʷ��
1.���ڣ�2020.6.29
���ߣ���λ�
�޸����ݣ������ɺ���

****************************************/
void stu()
{
	int choice;
	system("cls");
	printf("��ӭʹ��ѧ����Ϣ����ϵͳ��\n");
	printf("�밴����������Ĺ��ܱ���й���ѡ��\n");
	printf("            2.��ѯѧ����Ϣ\n");
	printf("3.������ѯ(���Ƽ�ȫ��)     4.ѧ����Ϣ����\n");
	printf("5.��ѯѧ������             6.��ѯ����\n");
	printf("0.�˳�ϵͳ\n");
	while (1)
	{
		fflush(stdin);
		scanf("%d", &choice);
		switch (choice)
		{
		
		case 2:system("cls"); search(); Exit(1); break;
		case 3:system("cls"); score(); Exit(1); break;
		case 4:system("cls"); order(); Exit(1); break;
		case 5:system("cls"); grade(); Exit(1); break;
		case 6:system("cls"); vrank(); Exit(1); break;
	
		case 0:Exit(1); break;
		default: {printf("��Чָ�����������"); Sleep(1000); system("cls"); break; }
		}
	}

}
void tea()
{
	int choice;
	system("cls");
	printf("��ӭʹ����ʦ��Ϣ����ϵͳ��\n");
	printf("�밴����������Ĺ��ܱ���й���ѡ��\n");
	printf("1.��ʾ��ʦ��Ϣ             2.��ѯ��ʦ��Ϣ\n");
	printf("0.�˳�ϵͳ\n");

	while (1)
	{
		fflush(stdin);
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:system("cls"); appear(); Exit(1); break;
		case 2:system("cls"); search(); Exit(1); break;
		case 0:Exit(1); break;
		default: {printf("��Чָ�����������"); Sleep(1000); system("cls"); break; }
		}
	}

}
/****************************************

��������login_stu
����������ѧ����¼����
���������int
�����������
����ֵ����
���ú�����islogin_stu

�޸���ʷ
1.���ڣ�2022.5.15
���ߣ���λ�
�޸����ݣ������ɺ���

****************************************/
void Login_stu(int n)
{
	int c, i;
	char ch;
	char xing[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" };
	c = strlen(xing);
	for (i = 0; i < c; i++)
	{
		printf("%c", xing[i]);
		Sleep(10);
	}
	printf("\n\n\t\t\t\t\t\t�����������˺�����:\n\n\n\n\t\t\t\t\t\t�˺�:");
	gets(StuName);
	printf("\n\n\t\t\t\t\t\t����:");
	//gets(UserWord);
	i = 0;
	while (1)
	{
		ch = getch();
		if (ch == '\r')
			break;
		if (ch == '\b')
		{
			if (i > 0)
			{
				i--;
				printf("\b \b");
				ch = '\0';
				continue;
			}
		}
		else
		{
			printf("*");
			StuWord[i] = ch;
			if (i < 20) i++;
		}
	}
	StuWord[i] = '\0';
	isLogin_stu(n);
}
/****************************************

��������islogin_stu
�����������ж�ѧ����¼����
���������int
�����������
����ֵ����
���ú�������

�޸���ʷ
1.���ڣ�2022.5.15
���ߣ���λ�
�޸����ݣ������ɺ���

****************************************/
void isLogin_stu(int n)
{
	int times = n;	//�����������
	while (!(judge_admin(StuName) == 1 && strcmp(StuWord, StuWord_temp) == 0))
	{
		times++;	//�˺Ż������������ times++
		if (times > 3)
		{
			printf("\n\n\n\n\t\t\t\t�˺Ż�������������ۼƴﵽ%d�Σ�ϵͳ����3���ر�", times);
			Sleep(1000);
			system("cls");
			char shutdown[] = { "ϵͳ����%d���ر�..." };
			for (int i = 0; i < 3; i++)
			{
				printf(shutdown, 3 - i);
				Sleep(1000);
				system("cls");
			}
			exit(0);
		}
		printf("\n\n\n\n\t\t\t\t�˺Ż������������,�㻹��%d�ε�¼���ᣬ����������µ�¼...", 4 - times);
		getch();
		system("cls");
		Login_stu(times);
	}
}
void Login_tea(int n)
{
	int c, i;
	char ch;
	char xing[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " };
	c = strlen(xing);
	for (i = 0; i < c; i++)
	{
		printf("%c", xing[i]);
		Sleep(10);
	}
	printf("\n\n\t\t\t\t\t\t�����������˺�����:\n\n\n\n\t\t\t\t\t\t�˺�:");
	gets(TeaName);
	printf("\n\n\t\t\t\t\t\t����:");
	//gets(UserWord);
	i = 0;
	while (1)
	{
		ch = getch();
		if (ch == '\r')
			break;
		if (ch == '\b')
		{
			if (i > 0)
			{
				i--;
				printf("\b \b");
				ch = '\0';
				continue;
			}
		}
		else
		{
			printf("*");
			TeaWord[i] = ch;
			if (i < 20) i++;
		}
	}
	TeaWord[i] = '\0';
	isLogin_stu(n);
}
/****************************************

��������search
������������ѯѧ����Ϣ
�����������
�����������
����ֵ����
���ú�������

�޸���ʷ
1.���ڣ�2020.5.23
���ߣ���λ�
�޸����ݣ������ɺ���
2.2020.6.7
���ߣ���λ�
�޸����ݣ�������״̬���޷�����

****************************************/
void search()
{


	if (shead->pnext == NULL)
	{
		system("cls");
		printf("\n����Ϣ\n\n");
		Sleep(1000);
		system("cls");
		return;
	}
	else
	{
		int choice, num;
		char putnum[20];
		char putname[20];
		PSTU p1 = shead->pnext;
		num = 0;
		system("cls");
		printf("��ѡ����ҷ�ʽ��\n\n1.��һ����������ѧ���Բ���\t0.�����ϼ�\n");
		printf("�����Ӧ�����Խ��в���\n");
		fflush(stdin);
		scanf("%d", &choice);
		if (choice != 0 && choice != 1 && choice == 2)
		{
			printf("��Чָ������");
		}
		if (choice == 0)
		{
			system("cls");
			return;
		}
		if (choice == 1)
		{
			printf("������ѧ��\n\n");
			scanf("%s", putnum);
			printf("\n");
			system("cls");
			while (p1 != NULL)
			{
				if (strcmp(p1->number, putnum) == 0)
				{
					printf("��⵽���·��ϵ���Ϣ��\n\n\t����\tѧ��\t��������\t\t\t����Ժϵ\t�ߵ���ѧ�ɼ�\t�����߼��ɼ�\t��ɢ��ѧ�ɼ�\t�ܳɼ�\t����");
					printf("\n\n\t%s\t%s\t%d\t%d\t%d\t%s\t%g\t%g\t%g\t%g\t%d", p1->name, p1->number, p1->birth[0], p1->birth[1], p1->birth[2], p1->department, p1->score[0], p1->score[1], p1->score[2], p1->score[3], p1->rank);

					return;
				}
				p1 = p1->pnext;
			}
			p1 = NULL;
			printf("δ�ҵ������Ϣ");
		}

		return;
	}
}
/****************************************

��������score
������������ѯѧ�����ܷ֣�ƽ���֣���ѯÿ�ſγ̵�ƽ����
�����������
�����������
����ֵ��
���ú�����Sleep������system������

�޸���ʷ��
1.���ڣ�2020.05.23
���ߣ���λ�
�޸����ݣ������ɺ���

****************************************/
void score()
{

	if (shead->pnext == NULL)
	{
		system("cls");
		printf("\n����Ϣ\n\n");
		Sleep(1000);
		system("cls");
		return;
	}
	float all, average0, average1, average2;
	int count = 0;
	all = average0 = average1 = average2 = 0;
	PSTU p1;
	p1 = shead->pnext;
	for (; p1 != NULL; p1 = p1->pnext)
	{
		printf("%s is %f\n", p1->name, p1->score[3]);
		all += p1->score[3];
		average0 += p1->score[0];
		average1 += p1->score[1];
		average2 += p1->score[2];
		count++;
	}
	printf("�ߵ���ѧ��ƽ������%g�������߼���ƽ������%g����ɢ��ѧ��ƽ������%g����ƽ������%g", average0 / count, average1 / count, average2 / count, all / count);
	return;
}
/****************************************

��������order
����������������Ϣ����
�����������
�����������
����ֵ����
���ú�����swap����

�޸���ʷ��
1.���ڣ�2020.05.23
���ߣ���λ�
�޸����ݣ������ɺ���

****************************************/
void order()
{
	if (shead->pnext == NULL)
	{
		printf("\n����Ϣ\n\n");
		Sleep(1000);
		system("cls");
		return;
	}
	int x, x1;
	PSTU p1, p2;
	STU temp;
	p1 = shead->pnext;
	system("cls");
	printf("��ѡ������ʽ��\n\n1.����ѧ������\t2.���ݳɼ�����\t0.�����ϼ�\n");
	printf("�����Ӧ�����Լ���:\n");
	fflush(stdin);
	while (1)
	{
		scanf("%d", &x);

		if (x == 0)
		{
			return;
			system("cls");
		}
		if (x != 0 && x != 1 && x != 2)
		{
			printf("\n��Ч���룬����������\n\n");
			continue;
		}
		else
		{
			if (x == 1)
			{
				for (p1 = shead->pnext; p1 != NULL; p1 = p1->pnext)
				{
					for (p2 = p1->pnext; p2 != NULL; p2 = p2->pnext)
					{
						if (strcmp(p1->number, p2->number) < 0)
						{
							swap(&temp, p1);
							swap(p1, p2);
							swap(p2, &temp);
						}
					}
				}
				for (p1 = shead->pnext; p1 != NULL; p1 = p1->pnext)
				{
					printf("\n\n\t����\tѧ��\t��������\t\t\t����Ժϵ\t�ߵ���ѧ�ɼ�\t�����߼��ɼ�\t��ɢ��ѧ�ɼ�\t�ܳɼ�\t");
					printf("\n\n\t%s\t%s\t%d\t%d\t%d\t%s\t%g\t%g\t%g\t%g\t", p1->name, p1->number, p1->birth[0], p1->birth[1], p1->birth[2], p1->department, p1->score[0], p1->score[1], p1->score[2], p1->score[3]);
				}
				return;
			}
			else if (x == 2)
			{
				printf("��ѡ������Ҫ����ĳɼ�\n");
				printf("1.�ߵ���ѧ\t2.�����߼�\t3.��ɢ��ѧ\t4.�ܳɼ�\t\n");
				printf("�������Ӧ�����Խ��в���\n");
				while (1)
				{
					scanf("%d", &x1);
					if (x1 != 1 && x1 != 2 && x1 != 3 && x1 != 4)
						printf("\n��Ч���룬����������\n");
					else
						break;
				}
				for (p1 = shead->pnext; p1 != NULL; p1 = p1->pnext)
				{
					for (p2 = p1->pnext; p2 != NULL; p2 = p2->pnext)
					{
						if (p1->score[x1 - 1] < p2->score[x1 - 1])
						{
							swap(&temp, p1);
							swap(p1, p2);
							swap(p2, &temp);
						}
					}
				}
				for (p1 = shead->pnext; p1 != NULL; p1 = p1->pnext)
				{
					printf("\n\n\t����\tѧ��\t��������\t\t\t����Ժϵ\t�ߵ���ѧ�ɼ�\t�����߼��ɼ�\t��ɢ��ѧ�ɼ�\t�ܳɼ�\t");
					printf("\n\n\t%s\t%s\t%d\t%d\t%d\t%s\t%g\t%g\t%g\t%g\t", p1->name, p1->number, p1->birth[0], p1->birth[1], p1->birth[2], p1->department, p1->score[0], p1->score[1], p1->score[2], p1->score[3]);
				}
				return;
			}
		}
		return;
	}
}
void view_department()
{
	char department[20];
	printf("������Ҫ�鿴��רҵ����");
	scanf("%s", department);

	// ͳ�Ƹ�רҵѧ������
	int count = 0;
	PSTU p = shead->pnext;
	while (p != NULL) {
		if (strcmp(p->department, department) == 0) {
			count++;
		}
		p = p->pnext;
	}

	// ����ռ䣬�洢��רҵѧ����Ϣ
	STU* students = (STU*)malloc(sizeof(STU) * count);
	int i = 0;
	p = shead->pnext;
	while (p != NULL) {
		if (strcmp(p->department, department) == 0) {
			students[i] = *p;
			i++;
		}
		p = p->pnext;
	}

	// ���ֽܷ�������
	for (i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			if (students[j].score[3] < students[j + 1].score[3]) {
				STU temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
		}
	}

	// ���ѧ����Ϣ��������
	printf("\n\n\t����\tѧ��\t��������\t\t����Ժϵ\t�ߵ���ѧ�ɼ�\t�����߼��ɼ�\t��ɢ��ѧ�ɼ�\t�ܳɼ�\t����\n\n");
	for (i = 0; i < count; i++) {
		
		printf("\t%s\t%s\t%d/%d/%d\t%s\t%g\t%g\t%g\t%g\t%d\n", students[i].name, students[i].number, students[i].birth[0], students[i].birth[1], students[i].birth[2], students[i].department, students[i].score[0], students[i].score[1], students[i].score[2], students[i].score[3], i + 1); \
			students[i].rank = i + 1;
	}
	
	free(students);
}
/****************************************

��������grade
����������ͳ�Ƹ���ƽ���ֺ͵ȼ����ֵõ�������
�����������
�����������
����ֵ����
���ú�������

�޸���ʷ��
1.���ڣ�2020.05.24
���ߣ���λ�
�޸����ݣ������ɺ���
2.���ڣ�2022.05.13
���ߣ���λ�
�޸����ݣ��޸���max�ĸ�ֵ������������ĳЩ�������ϵ���Ϊ����Ϳռ����
****************************************/
void grade()
{

	if (shead->pnext == NULL)
	{
		printf("\n����Ϣ\n\n");
		Sleep(1000);
		system("cls");
		return;
	}
	int x;
	float max, total, aver;
	int more, same, less, fail, enough, nom, good, excel;
	PSTU p1 = shead->pnext;
	system("cls");
	printf("����%d�����ݣ�\n", Count_stu);
	printf("�����������Բ鿴����򵥿Ƴɼ�\n");
	while (1)
	{
		while (1)
		{
			printf("1.�ߵ���ѧ2.�����߼�3.��ɢ��ѧ4.�ܷ�0.�����ϲ�");
			scanf("%d", &x);
			if (x >= 0 && x <= 4)
				break;
			else
				printf("��Чָ�����������");
		}
		if (x == 0)
		{
			system("cls");
			return;
		}
		else
			x--;
		for (total = 0, p1 = shead->pnext, max = 0; p1 != NULL; p1 = p1->pnext)
		{
			if (p1->score[x] > max)
				max = p1->score[x];
			total += p1->score[x];
		}
		aver = total / Count_stu;
		system("cls");
		printf("����%d������\n", Count_stu);
		switch (x)
		{
		case 0:printf("��Ŀ:�ߵ���ѧ"); break;
		case 1:printf("��Ŀ:�����߼�"); break;
		case 2:printf("��Ŀ:��ɢ��ѧ"); break;
		case 3:printf("��Ŀ:�ܷ�"); break;
		}
		printf(":��߷�:%.2f��\n", max);
		for (more = 0, same = 0, less = 0, fail = 0, enough = 0, nom = 0, good = 0, excel = 0, p1 = shead->pnext; p1 != NULL; p1 = p1->pnext)
		{
			if (p1->score[x] == max)
				printf("״Ԫ����:%s  [%s]\n", p1->name, p1->number);
			if (p1->score[x] > aver)
				more++;
			if (p1->score[x] == aver)
				same++;
			if (p1->score[x] < aver)
				less++;
			if (x != 3)
			{
				if (p1->score[x] >= 90.0)
					excel++;
				if (p1->score[x] >= 80.0 && p1->score[x] < 90.0)
					good++;
				if (p1->score[x] >= 70.0 && p1->score[x] < 80.0)
					nom++;
				if (p1->score[x] >= 60.0 && p1->score[x] < 70.0)
					enough++;
				if (p1->score[x] < 60)
					fail++;

			}
		}
		printf("ƽ���ɼ�:%.2f��\n����ƽ���ɼ�����%d��\n����ƽ���ɼ�����%d��\n����ƽ���ɼ�����%d��\n", aver, more, same, less);
		if (x != 3)
		{
			printf("����[90~100]����Ϊ%d�ˣ�ռ��Ϊ%% %.2f\n", excel, excel * 100.0 / Count_stu);
			printf("����[80~90)����Ϊ%d�ˣ�ռ��Ϊ%% %.2f\n", good, good * 100.0 / Count_stu);
			printf("�е�[70~80)����Ϊ%d�ˣ�ռ��Ϊ%% %.2f\n", nom, nom * 100.0 / Count_stu);
			printf("����[60~70)����Ϊ%d�ˣ�ռ��Ϊ%% %.2f\n", enough, enough * 100.0 / Count_stu);
			printf("������[0~60)����Ϊ%d�ˣ�ռ��Ϊ%% %.2f\n", fail, fail * 100.0 / Count_stu);
		}
		printf("���������Խ�����һ������");
	}
}
float gpa(float score) {
	if (score < 60) {
		return 0.0;
	}
	else if (score == 100) {
		return 5.0;
	}
	else {
		return (score - 50) / 10.0;
	}
}
void vrank()
{
	char number[20];
	printf("������Ҫ��ѯ��ѧ��ѧ�ţ�");
	scanf("%s", number);

	// Search for the student in the linked list
	PSTU p = shead;
	while (p != NULL) {
		if (strcmp(p->number, number) == 0) {
			// Calculate the rank of the student within their department
			int rank = 1;
			PSTU q = shead;
			while (q != NULL) {
				if (strcmp(q->department, p->department) == 0 && q->score[3] > p->score[3]) {
					rank++;
				}
				q = q->pnext;
			}
			printf("ѧ�� %s ���ܳɼ��ڱ�רҵ������ %d ����\n", p->name, rank);
			return;
		}
		p = p->pnext;
	}
	printf("û���ҵ�ѧ��Ϊ %s ��ѧ����\n", number);
	return;
}
int irank(char* num)
{
	PSTU p = shead->pnext;
	int rank = 1;
	while (p != NULL)
	{
		if (strcmp(p->number, num) != 0 && p->score[3] > get_score(num))
		{
			rank++;
		}
		p = p->pnext;
	}
	return rank;
}
void update_rank()
{
	PSTU p = shead->pnext;
	while (p != NULL)
	{
		p->rank = irank(p->number);
		p = p->pnext;
	}
}
double get_score(char* num)
{
	PSTU p = shead->pnext;
	while (p != NULL)
	{
		if (strcmp(p->number, num) == 0)
		{
			return p->score[0] + p->score[1] + p->score[2];
		}
		p = p->pnext;
	}
	return 0;
}

void insert(PSTU p)
{
	PSTU pre = shead;
	PSTU cur = shead->pnext;
	while (cur != NULL && cur->score[3] > p->score[3])
	{
		pre = cur;
		cur = cur->pnext;
	}
	p->pnext = cur;
	pre->pnext = p;
}
//�������
//�����Ż�	