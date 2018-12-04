
#include "pch.h"
#include "SInfo_basicfunc.h"
#include "SInfo_features.h"
sqlite3 *SInfoDB = NULL;
void readInit() {
head:
	SInfoDB = readConfig(SInfoDB);
	while (SInfoDB == NULL) {
		setConfig(1);
		SInfoDB = readConfig(SInfoDB);
	}
	int ret = databaseInit(SInfoDB);
	if (!ret) goto head;
}
void Menu_addNewStudent() {
	char name[20], address[0xff];int uuid=0; double grade=0;
	printf("请输入学生姓名，地址，学号与总成绩，用空格分隔：");
	scanf("%s %s %d %lf",name,address,&uuid,&grade);
	int ret = addNewStudent(SInfoDB,name,address,uuid,grade);
	if (ret) {
		printf("\n添加成功!\n");
	}
	else {
		printf("\n无法添加至数据库！\n");
	}
}
void Menu_showAllInfo() {
	showAllInfo(SInfoDB);
}
void SInfo_Menu() {
	int input;
	while (1) {
		printf("------------------------------\n");
		printf("|      学生信息管理系统       |\n");
		printf("|1.添加信息        5.查看所有 |\n");
		printf("|2.修改数据        6.更改设置 |\n");
		printf("|3.查看内容        7.退出系统 |\n");
		printf("|4.删除数据        8.退出系统 |\n");
		printf("|     Powered by LT_lrsoft    |\n");
		printf("------------------------------\n");
	linput:
		printf("输入操作数：");
		scanf("%d", &input);
		switch (input) {
			case 1:
				Menu_addNewStudent(); break;
			case 5:
				Menu_showAllInfo(); break;
			case 8:
				exit(1); sqlite3_close(SInfoDB);break;
			default:
				goto linput;
		}
	}
}
void main()
{
	readInit();
	SInfo_Menu();
}