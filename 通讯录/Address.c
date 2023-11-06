#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>



#define MAX 1000
#define NAME_MAX 20
#define SEX_MAX 5
#define TELE_MAX 12
#define ADDR_MAX 30

//通讯录初始状态的容量大小
#define DEFAULT_SZ 3

enum Option
{
	EXIT,//0
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SORT,
	PRINT
};
enum Con
{
	ERRO,
	NAME,
	SEX,
	AGE,
	TELE,
	ADDR
};

typedef struct PeoInfo
{
	char name[NAME_MAX];
	char sex[SEX_MAX];
	int age;
	char tele[TELE_MAX];
	char addr[ADDR_MAX];
} PeoInfo;
typedef struct Contact
{
	PeoInfo* data;//可以存放1000个人的信息
	int sz;//记录通讯中已经保存的信息个数
	int capacity;//记录通讯录当前的最大容量
}Contact;
//函数的声明
//初始化通讯录
void InitContact(Contact* pc);
//销毁通讯录
void DestroyContact(Contact* pc);
//增加联系人的信息
void AddContact(Contact* pc);
//打印通讯录中的信息
void PrintContact(const Contact* pc);
//删除指定联系人
void DelContact(Contact* pc);
//查找指定联系人
void SearchContact(const Contact* pc);
//保存通讯录的信息到文件
void SaveContact(const Contact* pc);
//通讯录排序
void SortCon(Contact* pc);
void ModifyCon(Contact* pc);
#define _CRT_SECURE_NO_WARNINGS 1


void CheckCapacity(Contact* pc)
{
	//增容的代码
	if (pc->sz == pc->capacity)
	{
		PeoInfo* tmp = (PeoInfo*)realloc(pc->data, (pc->capacity + 2) * sizeof(PeoInfo));
		if (tmp != NULL)
		{
			pc->data = tmp;
		}
		else
		{
			perror("CheckCapacity::realloc");
			return;
		}
		pc->capacity += 2;
		printf("增容成功\n");
	}
}
void LoadContact(Contact* pc)
{
	//打开文件
	FILE* pf = fopen("contact.dat", "rb");
	if (pf == NULL)
	{
		perror("LoadContact::fopen");
		return;
	}
	//读文件
	PeoInfo tmp = { 0 };
	while (fread(&tmp, sizeof(PeoInfo), 1, pf))
	{
		CheckCapacity(pc);
		pc->data[pc->sz] = tmp;
		pc->sz++;
	}

	//关闭文件
	fclose(pf);
	pf = NULL;
}
//初始化通讯录 - 文件版本
void InitContact(Contact* pc)
{
	assert(pc);
	pc->sz = 0;
	pc->capacity = DEFAULT_SZ;
	pc->data = (PeoInfo*)malloc(pc->capacity * sizeof(PeoInfo));

	if (pc->data == NULL)
	{
		perror("InitContact::malloc");
		return;
	}
	memset(pc->data, 0, pc->capacity * sizeof(PeoInfo));

	//加载文件信息到通讯录中
	LoadContact(pc);
}
void DestroyContact(Contact* pc)
{
	free(pc->data);
	pc->data = NULL;
	pc->capacity = 0;
	pc->sz = 0;
	printf("销毁成功\n");
}
void AddContact(Contact* pc)
{
	assert(pc);


	//动态的版本
	CheckCapacity(pc);

	//录入信息
	printf("请输入名字:>");
	scanf("%s", pc->data[pc->sz].name);
	printf("请输入年龄:>");
	scanf("%d", &(pc->data[pc->sz].age));
	printf("请输入性别:>");
	scanf("%s", pc->data[pc->sz].sex);
	printf("请输入电话:>");
	scanf("%s", pc->data[pc->sz].tele);
	printf("请输入地址:>");
	scanf("%s", pc->data[pc->sz].addr);

	pc->sz++;
	printf("添加成功\n");
}
void PrintContact(const Contact* pc)
{
	assert(pc);

	int i = 0;
	printf("%-20s %-5s %-5s %-12s %-30s\n", "姓名", "年龄", "性别", "电话", "地址");

	for (i = 0; i < pc->sz; i++)
	{
		printf("%-20s %-5d %-5s %-12s %-30s\n", pc->data[i].name, pc->data[i].age, pc->data[i].sex, pc->data[i].tele, pc->data[i].addr);
	}
}

//找到了返回下标
//找不到返回-1
int FindByName(const Contact* pc, char name[])
{
	assert(pc);
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		if (0 == strcmp(pc->data[i].name, name))
		{
			return i;
		}
	}

	return -1;
}

void DelContact(Contact* pc)
{
	assert(pc);

	if (pc->sz == 0)
	{
		printf("通讯录已空，无法删除\n");
		return;
	}
	//删除
	//1. 找到
	char name[NAME_MAX] = { 0 };
	printf("请输入要删除人的名字:>");
	scanf("%s", name);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("要删除的人不存在\n");
		return;
	}
	//2. 删除
	int j = 0;
	for (j = pos; j < pc->sz - 1; j++)
	{
		pc->data[j] = pc->data[j + 1];
	}

	pc->sz--;
	printf("删除成功\n");
}

void SearchContact(const Contact* pc)
{
	char name[NAME_MAX] = { 0 };
	printf("请输入要查找人的名字:>");
	scanf("%s", name);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("要查找的人不存在\n");
		return;
	}
	printf("%-20s %-5s %-5s %-12s %-30s\n", "姓名", "年龄", "性别", "电话", "地址");
	printf("%-20s %-5d %-5s %-12s %-30s\n", pc->data[pos].name, pc->data[pos].age, pc->data[pos].sex,
		pc->data[pos].tele, pc->data[pos].addr);
}


void SaveContact(const Contact* pc)
{
	FILE* pf = fopen("contact.dat", "wb");
	//回来本地建立一个contact.dat的记事本
	if (pf == NULL)
	{
		perror("SaveContact::fopen");
		return;
	}
	//写文件
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		fwrite(pc->data + i, sizeof(PeoInfo), 1, pf);
	}

	//关闭文件
	fclose(pf);
	pf = NULL;
}
void SortCon(Contact* pc)
{
	if (pc->sz == 0)
	{
		printf("通讯录中没有联系人\n");
	}
	else
	{
		for (int i = 0; i < pc->sz - 1; i++)
		{
			for (int j = 0; j < pc->sz - 1 - i; j++)
			{
				if ((strcmp(pc->data[j].name, pc->data[j + 1].name)) > 0)
				{
					PeoInfo temp = pc->data[j];
					pc->data[j] = pc->data[j + 1];
					pc->data[j + 1] = temp;
				}
			}
		}
		printf("排序成功！\n");
	}
}

void ModifyCon(Contact* pc)
{
	assert(pc);
	char name[NAME_MAX];
	printf("请输入需要修改信息用户的名字:>\n");
	scanf("%s", name);
	int pos = FindByName(pc, name);//pos为要寻找的人的下标
	if (pos == -1)
	{
		printf("查无此人\n");
	}
	else
	{
		int num = 0;
		do {
			printf("请输入你想修改此用户的信息\n");
			printf(" 0.退出 1.姓名 2.性别 3.年龄 4.电话 5.地址:>\n");
			scanf("%d", &num);
			switch (num)
			{
			case NAME:
				printf("请输入你想修改的姓名:>\n");
				scanf("%s", pc->data[pos].name);
				break;
			case SEX:
				printf("请输入你想修改的性别:>\n");
				scanf("%s", pc->data[pos].sex);
				break;
			case AGE:
				printf("请输入你想修改的年龄:>\n");
				scanf("%d", &(pc->data[pos].age));
				break;
			case TELE:
				printf("请输入你想修改的电话:>\n");
				scanf("%s", pc->data[pos].tele);
				break;
			case ADDR:
				printf("请输入你想修改的地址:>\n");
				scanf("%s", pc->data[pos].addr);
				break;
			case 0:
				printf("不修改退回界面\n");
				break;
			default:printf("无效操作数！\n");
			}
		} while (num);
	}
}

void menu()
{
	printf("*****************************************\n");
	printf("**** 1.增加联系人    2.删除联系人    ****\n");
	printf("**** 3.查找联系人    4.修改联系人    ****\n");
	printf("**** 5.通讯录排序    6.打印通讯录    ****\n");
	printf("****            0.退出               ****\n");
	printf("******************************************\n");
}

void test()
{
	int input = 0;
	Contact con;
	InitContact(&con);

	do
	{
		menu();
		printf("请输入你的选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			AddContact(&con);
			break;
		case DEL:
			DelContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case MODIFY:
			ModifyCon(&con);
			break;
		case SORT:
			SortCon(&con);
			break;
		case PRINT:
			PrintContact(&con);
			break;
		case EXIT:
			SaveContact(&con);
			DestroyContact(&con);
			printf("感谢使用\n");
			break;
		default:
			printf("非法输入\n");
			break;
		}
	} while (input);
}

int main()
{
	test();
	return 0;
}

