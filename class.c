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
	char admin[15];			//学生登录账户
	char password[15];		//学生账户密码 
	char name[10];          //名字
	char grade[10];         //年级
	char number[20];        //学号
	char graduation[10];	//毕业状况
	int birth[3];           //生日（年月日）
	char department[20];    //院系
	float credit[4];		//学分
	float score[4];			//成绩
	float gpa[4];			//绩点
	int rank;				//排名
	struct Student* pnext;
}STU, * PSTU;
typedef struct Teacher
{
	char admin[15];			//老师登录账户
	char password[15];		//老师账户密码 
	char name[10];         //名字
	char number[20];       //学号
	char department[20];   //院系
	struct Student* pnext;
}TEA, * PTEA;
PSTU shead = NULL;
PSTU snew = NULL;
PTEA thead = NULL;
PTEA tnew = NULL;
int Count_stu = 0;  //表示学生总数
int Count_tea = 0;//表示老师总数
char UserName[15];//暂存管理员账户 
char UserWord[15];//暂存管理员密码 
char TeaName[15];//暂存老师账户
char TeaWord[15];//暂存老师密码
char TeaWord_temp[15];//通过judge_admin()查找到对应账号的密码
char StuName[15];//暂存学生账户 
char StuWord[15];//暂存学生密码 
char StuWord_temp[15];//通过judge_admin()查找到的对应账号的密码 

//*********************************************

void Menu();//菜单初始化函数
void Fimport();//导入文件函数
void Fexport();//导出文件函数
void Exit(int);//确认退出函数
void swap(PSTU stu1, PSTU stu2);//交换内容函数

//*********************************************

void master();//管理员操作界面函数
void Login_master(int);//管理员登录函数
void isLogin_master(int);//判断管理员登录函数
void appear();//显示学生信息函数
void add();//添加学生信息函数
void change();//修改学生信息函数
void Delete();//删除学生信息函数

void view_department(); //专业查询

int judge_admin(char*);//判断是否输入的账户已经存在 
int judge_number(char*);//判断是否输入的学号已经存在
int day(int, int, int);//判断生日符合函数

//********************************************* 

void stu();//学生操作界面函数
void tea();
void Login_tea(int);
void Login_stu(int);//学生登录函数 
void isLogin_stu(int);//判断学生登录函数 
void search();//查询学生信息函数
void vrank();
int irank(char);
void update_rank();
double get_score(char* num);
void insert(PSTU p);
void score();//学生总分平均分和单科平均分
float gpa(float);//学生的学科绩点
void order();//信息排序函数
void grade();//查询两个标准下的学生评级和单科或全科成绩第一的学生

/****************************************

函数名：main
功能描述：无
输入参数：无
自定参数：无
输出参数：无
返回值：无
调用函数：void Menu()

修改历史：
1.日期：2020.5.23
作者：孙嘉辉
修改内容：新生成函数

****************************************/
int main()
{
	Menu();

	return 0;
}
/****************************************

函数名：Menu
功能描述：显示主菜单界面并依照选择运行函数
输入参数：无
自定参数：1.选择参数choice
输出参数：无
返回值：无
调用函数：

修改历史：
1.日期：2020.5.23
作者：孙嘉辉
修改内容：新生成函数

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
		printf("欢迎使用学生信息管理系统！\n");
		printf("请按照下面给出的功能表进行功能选择\n");
		printf("1.学生		2.老师		3.管理员\n");
		printf("0.退出系统\n");
		fflush(stdin);
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:system("cls"); getchar(); Login_stu(0); stu(); Exit(0); break;
		case 2:system("cls"); getchar(); Login_stu(0); tea(); Exit(0); break;
		case 3:system("cls"); getchar(); Login_master(0); master(); Exit(0); break;
		case 0:system("cls"); Exit(0); break;
		default: {printf("无效指令，请重新输入"); Sleep(1000); system("cls"); break; }
		}
	}
}
/***************************************

函数名：Fimport
功能描述：导入文件函数
输入参数：无
输出参数：无
返回值：无
调用函数：无

修改历史：
1.日期：2020.05.30
作者：孙嘉辉
修改内容：新生成函数

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

函数名：Fexport
功能描述：文件导出函数
输入参数：无
输出参数：无
返回值：无
调用函数：无

修改历史：
1.日期：2020.05.30
作者：孙嘉辉
修改内容：新生成函数

***************************************/
void Fexport()
{
	FILE* fWrite = fopen("D:\\stuInformation.dat", "wb");
	if (fWrite == NULL)
	{
		system("cls");
		printf("保存失败...\n");
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

函数名：Exit
功能描述：退出程序或重新进入界面
输入参数：int x（表示当前的程序状态）
返回值：无
调用函数：Menu（），stu（），master（）

修改历史：
1.日期：2020.5.31
作者：孙嘉辉
修改内容：新生成函数

***************************************/
void Exit(int x)
{
	char ch;
	if (x == 0)
	{
		printf("\n\t\n退出请按Esc,任意键回到主界面\n");
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
			printf("\n要返回学生操作界面界面请按1\t返回系统主界面请按2\t退出并保存数据请按Esc\n");
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
				printf("无效输入！");
			system("cls");
		}
	}
	else if (x == 2)
	{
		while (1)
		{
			printf("\n\t");
			printf("\n要返回管理员操作界面界面请按1\t返回系统主界面请按2\t退出并保存数据请按Esc\n");
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
				printf("无效输入！");
			system("cls");
		}

	}
}
/****************************************

函数名：swap
功能描述：实现链表内容复制
输入参数：PSTU stu1
PSTU stu2
输出参数：无
返回值：无
调用函数：无

修改历史：
1.日期：2020.05.24
作者：孙嘉辉
修改内容：新生成函数

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

函数名：master
功能描述：管理员操作界面
输入参数：无
返回值：无
调用函数：appear（），add（），change（），Delete（），Exit（），Sleep（），system（）

修改历史：
1.日期：2020.06.29
作者：孙嘉辉
修改内容：新生成函数

****************************************/
void master()
{
	int choice;
	system("cls");
	fflush(stdin);
	printf("欢迎使用学生信息管理系统！\n");
	printf("请按照下面给出的功能表进行功能选择\n");
	printf("1.显示学生信息             2.添加学生信息\n");
	printf("3.修改学生信息             4.删除学生信息\n");
	printf("5.查询专业学生信息		  0.退出系统\n");
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
		default: {printf("无效指令，请重新输入"); Sleep(1000); system("cls"); break; }
		}

	}
}
/****************************************

函数名：Login_master
功能描述：登入系统界面
输入参数：int n
输出参数：无
返回值：无
调用函数：isLogin_master(int n)

修改历史：
1.日期：2020.5.23
作者：孙嘉辉
修改内容：新生成函数
2.日期：2021.12.29
作者：孙嘉辉
修改内容：更改了验证代码与调用逻辑，避免出现提示的错误次数异常问题

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
	printf("\n\n\t\t\t\t\t\t请输入您的账号密码:\n\n\n\n\t\t\t\t\t\t账号:");
	gets(UserName);
	printf("\n\n\t\t\t\t\t\t密码:");
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

函数名：isLogin_master
功能描述：判断是否登录成功
输入参数：无
输出参数：无
返回值：无
调用函数：Login_master（）

修改历史：
1.日期：2020.5.23
作者：孙嘉辉
修改内容：新生成函数

****************************************/
void isLogin_master(int n)
{
	int times = n;	//密码输入次数
	while (!(strcmp(UserName, MANAGER_NAME) == 0 && strcmp(UserWord, MANAGER_PASSWORD) == 0))
	{
		times++;	//密码输入错误 times++
		if (times > 3)
		{
			printf("\n\n\n\n\t\t\t\t账号或密码输入错误累计达到%d次，系统将于3秒后关闭", times);
			Sleep(1000);
			system("cls");
			char shutdown[] = { "系统将于%d秒后关闭..." };
			for (int i = 0; i < 3; i++)
			{
				printf(shutdown, 3 - i);
				Sleep(1000);
				system("cls");
			}
			exit(0);
		}
		printf("\n\n\n\n\t\t\t\t账号或密码输入错误,你还有%d次登录机会，按任意键重新登录...", 4 - times);
		getch();
		system("cls");
		Login_master(times);
	}
}
/****************************************

函数名：appear
功能描述：显示学生信息
输入参数：无
输出参数：无
返回值：无
调用函数：无

修改历史
1.日期：2020.05.23
作者：孙嘉辉
修改内容：新生成函数

****************************************/
void appear()
{
	if (shead->pnext == NULL || Count_stu == 0)
	{
		system("cls");
		printf("\n无信息\n\n");
		Sleep(1000);
		system("cls");
		return;
	}
	else
	{
		system("cls");
		PSTU pcurrent = shead->pnext;
		int index = 1;
		printf("\t\t\t*************本名单共有%d名学生******************\n\n\n", Count_stu);
		printf("序号\t学号\t\t年级\t姓名\t院系\t\t\t生日\t高数-绩点-学分\t逻辑-绩点-学分\t离散-绩点-学分\t总分-平均绩点-总学分\n\n");
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

函数名：add
功能描述：添加学生信息
输入参数：无
输出参数：无
返回值：
调用函数：judge_admin（）、judge_number（）

修改历史：
1.日期：2020.5.25
作者：孙嘉辉
修改内容：新生成函数
2.日期：2022.5.15
作者：孙嘉辉
修改内容：新增学生的账户密码，使其可以通过账号密码验证登录
***************************************/
void add()
{
	fflush(stdin);
	snew = (PSTU)malloc(sizeof(STU));
	shead = (PSTU)malloc(sizeof(STU));
	shead->pnext = NULL;
	printf("添加学生账户\n");
	printf("账户:\n");
	scanf("%s", snew->admin);
	while (judge_admin(snew->admin) == 1)
	{
		printf("该账户已经存在\n");
		printf("请重新输入账户:");
		scanf("%s", snew->admin);
	}
	printf("密码:\n");
	scanf("%s", snew->password);
	printf("添加学生信息:\n");
	printf("学号:");
	scanf("%s", snew->number);
	while (judge_number(snew->number) == 1)
	{
		printf("学号已经存在\n");
		printf("请重新输入学号:");
		scanf("%s", snew->number);
	}
	printf("\n年级:");
	scanf("%s", snew->grade);
	printf("\n姓名:");
	scanf("%s", snew->name);
	printf("\n出生日期:");
	scanf("%d", &snew->birth[0]);
	scanf("%d", &snew->birth[1]);
	scanf("%d", &snew->birth[2]);
	if (day(snew->birth[0], snew->birth[1], snew->birth[2]) != 0)
	{
		printf("\n出生日期有误，重新输入:");
		scanf("%d", &snew->birth[0]);
		scanf("%d", &snew->birth[1]);
		scanf("%d", &snew->birth[2]);
	}
	printf("\n院系:");
	scanf("%s", snew->department);
	printf("\n高等数学:");
	scanf("%f", &snew->score[0]);
	printf("\n数理逻辑:");
	scanf("%f", &snew->score[1]);
	printf("\n离散数学:");
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

函数名：change
功能描述：对学生信息进行修改
输入参数：无
输出参数：无
返回值：
调用函数：

修改历史：
1.日期：2020.5.29
作者：孙嘉辉
修改内容：新生成函数
2.日期：2020.6.4
作者：孙嘉辉
修改内容：解决了有数据运行后直接退出的问题
//无法解决修改学号至相同时的提醒（在使用judge（）判定时输入任何数字均提醒是冲突的，已禁用judge（））
****************************************/
void change()
{

	if (shead->pnext == NULL)
	{
		printf("无信息\n");
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
		printf("修改学生信息\n");
		printf("请输入学生学号：");
		scanf("%s", ID);
		while (pcurrent != NULL)
		{
			if (strcmp(pcurrent->number, ID) == 0)
			{
				printf("要修改的学生信息\n");
				printf("学号\t姓名\t生日\t院系\t高数\t逻辑\t线代\t总分\t\n");
				printf("%s\t%s\t%d.%d.%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t", pcurrent->number, pcurrent->name, pcurrent->birth[0], pcurrent->birth[1], pcurrent->birth[2], pcurrent->department, pcurrent->score[0], pcurrent->score[1], pcurrent->score[2], pcurrent->score[3]);
				printf("是否修改该学生信息(y/enter)/(n/enter):");
				fflush(stdin);
				getchar();
				operate = getchar();
				if (operate == 'y' || operate == 'Y')
				{
					printf("请输入要修改的学生信息：\n");
					printf("1.姓名\t2.年级\t3.学号\t4.院系\t5.生日\t6.高等数学\t7.数理逻辑\t8.离散数学\t9.密码\t\n");
					scanf("%d", &choice);
					flag = 1;
					switch (choice)
					{
					case 1:printf("请输入姓名"); scanf("%s", pcurrent->name); break;
					case 2:printf("请输入年级"); scanf("%s", pcurrent->grade); break;
					case 3:
					{
						printf("请输入学号");
						scanf("%s", pcurrent->number);
						break;
					}
					case 4:printf("请输入院系"); scanf("%s", pcurrent->department); break;
					case 5:
					{
						printf("请输入生日");
						scanf("%d%d%d", &pcurrent->birth[0], &pcurrent->birth[1], &pcurrent->birth[2]);
						if (day(pcurrent->birth[0], pcurrent->birth[1], pcurrent->birth[2]) != 0)
						{
							printf("\n出生日期有误，重新输入:");
							scanf("%d", &pcurrent->birth[0]);
							scanf("%d", &pcurrent->birth[1]);
							scanf("%d", &pcurrent->birth[2]);
						}
						break;
					}
					case 6:printf("请输入分数"); scanf("%f", &pcurrent->score[0]); break;
					case 7:printf("请输入分数"); scanf("%f", &pcurrent->score[1]); break;
					case 8:printf("请输入分数"); scanf("%f", &pcurrent->score[2]); break;
					case 9:
					{
						printf("请输入密码");
						scanf("%s", pcurrent->password);
						break;
					}
					default:printf("无效输入\n"); break;
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
					printf("修改失败");
					return;
				}
			}

			pcurrent = pcurrent->pnext;
		}
		if (flag == 0)
		{
			printf("未找到要查询的学生信息\n\n");
			pcurrent = NULL;
			return;
		}
	}
	return;
}
/***************************************

函数名：Delete
功能描述：删除学生信息
输入参数：无
输出参数：无
返回值：无
调用函数：无

修改历史：
1.日期：2020.5.29
作者：孙嘉辉
修改内容：新生成函数

***************************************/
void Delete()
{

	if (shead->pnext == NULL)
	{
		printf("无信息\n");
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
		printf("删除学生信息：\n");
		printf("请输入学生学号：");
		scanf("%s", ID);
		while (pcurrent->pnext != NULL)
		{
			if (strcmp(pcurrent->pnext->number, ID) == 0)
			{
				printf("要删除的学生信息\n");
				printf("请输入要删除的学生信息：\n");
				printf("学号\t\t姓名\t生日\t院系\t高数\t逻辑\t线代\t总分\t\n");
				printf("%s\t%s\t%d.%d.%d\t%s\t%f\t%f\t%f\t%f\t", pcurrent->pnext->number, pcurrent->pnext->name, pcurrent->pnext->birth[0], pcurrent->pnext->birth[1], pcurrent->pnext->birth[2], pcurrent->pnext->department, pcurrent->pnext->score[0], pcurrent->pnext->score[1], pcurrent->pnext->score[2], pcurrent->pnext->score[3]);
				printf("是否删除该学生信息(y/enter)/(n/enter)");
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
					printf("删除成功\n\n");
					flag = 1;
					return;
				}
				else if (operate == 'n' || operate == 'N')
				{
					Exit(2);
				}
				else
				{
					printf("删除失败");
					return;
				}
			}
			pcurrent = pcurrent->pnext;
		}
		if (flag == 0)
		{
			printf("未找到要删除的学生信息\n");
			return;
		}
	}
}
/***************************************
函数名：judge_admin
功能描述：判断是否输入的学号已经存在
输入参数：
返回值：int
调用函数：无

修改历史：
1.日期：2022.5.15
作者：孙嘉辉
修改内容：新生成函数
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
函数名：judge_number
功能描述：判断是否输入的学号已经存在
输入参数：
返回值：int
调用函数：无

修改历史：
1.日期：2020.6.28
作者：孙嘉辉
修改内容：新生成函数
//在修改模块中对修改有冲突，无法正常运行（已在change（）中禁用）
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

函数名：day
功能描述：判断生日是否符合标准
输入参数：int year，int month，int day
返回值：int
调用函数：无

修改历史：
1.日期：2020.5.29
作者：孙嘉辉
修改内容：新生成函数

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

函数名：stu
功能描述：学生操作界面函数
输入参数：无
调用函数：appear（），search（），score（），order（），grade（），Exit（），system（），fflush（）

修改历史：
1.日期：2020.6.29
作者：孙嘉辉
修改内容：新生成函数

****************************************/
void stu()
{
	int choice;
	system("cls");
	printf("欢迎使用学生信息管理系统！\n");
	printf("请按照下面给出的功能表进行功能选择\n");
	printf("            2.查询学生信息\n");
	printf("3.分数查询(单科及全科)     4.学生信息排序\n");
	printf("5.查询学生评级             6.查询排名\n");
	printf("0.退出系统\n");
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
		default: {printf("无效指令，请重新输入"); Sleep(1000); system("cls"); break; }
		}
	}

}
void tea()
{
	int choice;
	system("cls");
	printf("欢迎使用老师信息管理系统！\n");
	printf("请按照下面给出的功能表进行功能选择\n");
	printf("1.显示老师信息             2.查询老师信息\n");
	printf("0.退出系统\n");

	while (1)
	{
		fflush(stdin);
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:system("cls"); appear(); Exit(1); break;
		case 2:system("cls"); search(); Exit(1); break;
		case 0:Exit(1); break;
		default: {printf("无效指令，请重新输入"); Sleep(1000); system("cls"); break; }
		}
	}

}
/****************************************

函数名：login_stu
功能描述：学生登录函数
输入参数：int
输出参数：无
返回值：无
调用函数：islogin_stu

修改历史
1.日期：2022.5.15
作者：孙嘉辉
修改内容：新生成函数

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
	printf("\n\n\t\t\t\t\t\t请输入您的账号密码:\n\n\n\n\t\t\t\t\t\t账号:");
	gets(StuName);
	printf("\n\n\t\t\t\t\t\t密码:");
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

函数名：islogin_stu
功能描述：判断学生登录函数
输入参数：int
输出参数：无
返回值：无
调用函数：无

修改历史
1.日期：2022.5.15
作者：孙嘉辉
修改内容：新生成函数

****************************************/
void isLogin_stu(int n)
{
	int times = n;	//密码输入次数
	while (!(judge_admin(StuName) == 1 && strcmp(StuWord, StuWord_temp) == 0))
	{
		times++;	//账号或密码输入错误 times++
		if (times > 3)
		{
			printf("\n\n\n\n\t\t\t\t账号或密码输入错误累计达到%d次，系统将于3秒后关闭", times);
			Sleep(1000);
			system("cls");
			char shutdown[] = { "系统将于%d秒后关闭..." };
			for (int i = 0; i < 3; i++)
			{
				printf(shutdown, 3 - i);
				Sleep(1000);
				system("cls");
			}
			exit(0);
		}
		printf("\n\n\n\n\t\t\t\t账号或密码输入错误,你还有%d次登录机会，按任意键重新登录...", 4 - times);
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
	printf("\n\n\t\t\t\t\t\t请输入您的账号密码:\n\n\n\n\t\t\t\t\t\t账号:");
	gets(TeaName);
	printf("\n\n\t\t\t\t\t\t密码:");
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

函数名：search
功能描述：查询学生信息
输入参数：无
输出参数：无
返回值：无
调用函数：无

修改历史
1.日期：2020.5.23
作者：孙嘉辉
修改内容：新生成函数
2.2020.6.7
作者：孙嘉辉
修改内容：有数据状态下无法返回

****************************************/
void search()
{


	if (shead->pnext == NULL)
	{
		system("cls");
		printf("\n无信息\n\n");
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
		printf("请选择查找方式：\n\n1.再一次输入您的学号以查找\t0.返回上级\n");
		printf("输入对应数字以进行查找\n");
		fflush(stdin);
		scanf("%d", &choice);
		if (choice != 0 && choice != 1 && choice == 2)
		{
			printf("无效指令输入");
		}
		if (choice == 0)
		{
			system("cls");
			return;
		}
		if (choice == 1)
		{
			printf("请输入学号\n\n");
			scanf("%s", putnum);
			printf("\n");
			system("cls");
			while (p1 != NULL)
			{
				if (strcmp(p1->number, putnum) == 0)
				{
					printf("检测到如下符合的信息：\n\n\t姓名\t学号\t出生日期\t\t\t所在院系\t高等数学成绩\t数字逻辑成绩\t离散数学成绩\t总成绩\t排名");
					printf("\n\n\t%s\t%s\t%d\t%d\t%d\t%s\t%g\t%g\t%g\t%g\t%d", p1->name, p1->number, p1->birth[0], p1->birth[1], p1->birth[2], p1->department, p1->score[0], p1->score[1], p1->score[2], p1->score[3], p1->rank);

					return;
				}
				p1 = p1->pnext;
			}
			p1 = NULL;
			printf("未找到相关信息");
		}

		return;
	}
}
/****************************************

函数名：score
功能描述：查询学生的总分，平均分，查询每门课程的平均分
输入参数：无
输出参数：无
返回值：
调用函数：Sleep（），system（）。

修改历史：
1.日期：2020.05.23
作者：孙嘉辉
修改内容：新生成函数

****************************************/
void score()
{

	if (shead->pnext == NULL)
	{
		system("cls");
		printf("\n无信息\n\n");
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
	printf("高等数学的平均分是%g，数理逻辑的平均分是%g，离散数学的平均分是%g，总平均分是%g", average0 / count, average1 / count, average2 / count, all / count);
	return;
}
/****************************************

函数名：order
功能描述：进行信息排序
输入参数：无
输出参数：无
返回值：无
调用函数：swap（）

修改历史：
1.日期：2020.05.23
作者：孙嘉辉
修改内容：新生成函数

****************************************/
void order()
{
	if (shead->pnext == NULL)
	{
		printf("\n无信息\n\n");
		Sleep(1000);
		system("cls");
		return;
	}
	int x, x1;
	PSTU p1, p2;
	STU temp;
	p1 = shead->pnext;
	system("cls");
	printf("请选择排序方式：\n\n1.根据学号排序\t2.根据成绩排序\t0.返回上级\n");
	printf("输入对应数字以继续:\n");
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
			printf("\n无效输入，请重新输入\n\n");
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
					printf("\n\n\t姓名\t学号\t出生日期\t\t\t所在院系\t高等数学成绩\t数字逻辑成绩\t离散数学成绩\t总成绩\t");
					printf("\n\n\t%s\t%s\t%d\t%d\t%d\t%s\t%g\t%g\t%g\t%g\t", p1->name, p1->number, p1->birth[0], p1->birth[1], p1->birth[2], p1->department, p1->score[0], p1->score[1], p1->score[2], p1->score[3]);
				}
				return;
			}
			else if (x == 2)
			{
				printf("请选择你想要排序的成绩\n");
				printf("1.高等数学\t2.数理逻辑\t3.离散数学\t4.总成绩\t\n");
				printf("请输入对应数字以进行操作\n");
				while (1)
				{
					scanf("%d", &x1);
					if (x1 != 1 && x1 != 2 && x1 != 3 && x1 != 4)
						printf("\n无效输入，请重新输入\n");
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
					printf("\n\n\t姓名\t学号\t出生日期\t\t\t所在院系\t高等数学成绩\t数字逻辑成绩\t离散数学成绩\t总成绩\t");
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
	printf("请输入要查看的专业名：");
	scanf("%s", department);

	// 统计该专业学生总数
	int count = 0;
	PSTU p = shead->pnext;
	while (p != NULL) {
		if (strcmp(p->department, department) == 0) {
			count++;
		}
		p = p->pnext;
	}

	// 分配空间，存储该专业学生信息
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

	// 按总分进行排序
	for (i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			if (students[j].score[3] < students[j + 1].score[3]) {
				STU temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
		}
	}

	// 输出学生信息及总排名
	printf("\n\n\t姓名\t学号\t出生日期\t\t所在院系\t高等数学成绩\t数字逻辑成绩\t离散数学成绩\t总成绩\t排名\n\n");
	for (i = 0; i < count; i++) {
		
		printf("\t%s\t%s\t%d/%d/%d\t%s\t%g\t%g\t%g\t%g\t%d\n", students[i].name, students[i].number, students[i].birth[0], students[i].birth[1], students[i].birth[2], students[i].department, students[i].score[0], students[i].score[1], students[i].score[2], students[i].score[3], i + 1); \
			students[i].rank = i + 1;
	}
	
	free(students);
}
/****************************************

函数名：grade
功能描述：统计根据平均分和等级划分得到的评级
输入参数：无
输出参数：无
返回值：无
调用函数：无

修改历史：
1.日期：2020.05.24
作者：孙嘉辉
修改内容：新生成函数
2.日期：2022.05.13
作者：孙嘉辉
修改内容：修改了max的赋值量，避免了在某些编译器上的行为问题和空间溢出
****************************************/
void grade()
{

	if (shead->pnext == NULL)
	{
		printf("\n无信息\n\n");
		Sleep(1000);
		system("cls");
		return;
	}
	int x;
	float max, total, aver;
	int more, same, less, fail, enough, nom, good, excel;
	PSTU p1 = shead->pnext;
	system("cls");
	printf("共有%d个数据：\n", Count_stu);
	printf("请输入数字以查看总体或单科成绩\n");
	while (1)
	{
		while (1)
		{
			printf("1.高等数学2.数理逻辑3.离散数学4.总分0.返回上层");
			scanf("%d", &x);
			if (x >= 0 && x <= 4)
				break;
			else
				printf("无效指令，请重新输入");
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
		printf("共有%d个数据\n", Count_stu);
		switch (x)
		{
		case 0:printf("科目:高等数学"); break;
		case 1:printf("科目:数理逻辑"); break;
		case 2:printf("科目:离散数学"); break;
		case 3:printf("科目:总分"); break;
		}
		printf(":最高分:%.2f分\n", max);
		for (more = 0, same = 0, less = 0, fail = 0, enough = 0, nom = 0, good = 0, excel = 0, p1 = shead->pnext; p1 != NULL; p1 = p1->pnext)
		{
			if (p1->score[x] == max)
				printf("状元考生:%s  [%s]\n", p1->name, p1->number);
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
		printf("平均成绩:%.2f分\n高于平均成绩的有%d人\n等于平均成绩的有%d人\n低于平均成绩的有%d人\n", aver, more, same, less);
		if (x != 3)
		{
			printf("优秀[90~100]人数为%d人，占比为%% %.2f\n", excel, excel * 100.0 / Count_stu);
			printf("良好[80~90)人数为%d人，占比为%% %.2f\n", good, good * 100.0 / Count_stu);
			printf("中等[70~80)人数为%d人，占比为%% %.2f\n", nom, nom * 100.0 / Count_stu);
			printf("及格[60~70)人数为%d人，占比为%% %.2f\n", enough, enough * 100.0 / Count_stu);
			printf("不及格[0~60)人数为%d人，占比为%% %.2f\n", fail, fail * 100.0 / Count_stu);
		}
		printf("输入数字以进行下一步操作");
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
	printf("请输入要查询的学生学号：");
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
			printf("学生 %s 的总成绩在本专业排名第 %d 名。\n", p->name, rank);
			return;
		}
		p = p->pnext;
	}
	printf("没有找到学号为 %s 的学生。\n", number);
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
//密码加密
//界面优化	