
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
void Menu_updateStudentInfo() {
	int uuid = 0,type=0,ret=0;double grade = 0;
	printf("输入1修改姓名，2修改家庭住址，3更新成绩:");
	scanf("%d",&type);
	printf("输入该生学号：");
	scanf("%d",&uuid);
	switch (type) {
		case 1:
			char name[10];
			printf("输入该生新姓名：");
			scanf("%s",name);
			ret = updateNameByUuid(SInfoDB,uuid,name);
			if (ret) {
				printf("修改成功！\n"); 
			}
			else {
				printf("修改失败！\n"); 
			}
			break;
		case 2:
			char address[10];
			printf("输入该生新住址：");
			scanf("%s", address);
			ret = updateAddressByUuid(SInfoDB, uuid, address);
			if (ret) {
				printf("修改成功！\n");
			}
			else {
				printf("修改失败！\n");
			}
			break;
		case 3:
			printf("输入该生总评成绩：");
			scanf("%lf", &grade);
			ret = updateGradeByUuid(SInfoDB, uuid, grade);
			if (ret) {
				printf("修改成功！\n");
			}
			else {
				printf("修改失败！\n");
			}
			break;
		default:
			printf("无效选项！\n");
			break;
	}
}
void Menu_showStudentInfo() {
	int uuid = 0; InfoStruct *temp=NULL;
	printf("输入该生学号:");
	scanf("%d",&uuid);
	temp = getStudentInfo(SInfoDB,uuid);
	if (temp!=NULL) {
	//	printf("[学号:%d 姓名:%s 住址:%s 总评:%lf]\n",temp->uuid,temp->name,temp->address,temp->grade);
	}
	//ret=geti
}
void Menu_deleteStudent() {
	int uuid = 0,ret=0;
	printf("输入该生学号:");
	scanf("%d",&uuid);
	ret = deleteByUuid(SInfoDB,uuid);
	if (ret) {
		printf("删除成功！\n");
	}
	else {
		printf("删除失败！\n");
	}
}
void Menu_showAllInfo() {
	showAllInfo(SInfoDB);
}
void Menu_changeSetting() {
	FILE *fp,*set;
	char path[0xff] = {0};
	printf("输入新数据库的地址：");
	scanf("%s",path);
	set = fopen("data.dat","wb");
	fp = fopen(path, "rb");
	if (fp != NULL) {
		fwrite(path,sizeof(path),1,set);
		fclose(fp); 
		fclose(set);
		printf("写入完成，重启程序后生效！\n");
	}
	else {
		printf("无效地址！\n");
		fclose(set);
	}
}
void SInfo_Menu() {
	int input;
	while (1) {
		printf("-------------------------------\n");
		printf("|      学生信息管理系统       |\n");
		printf("|1.添加信息        5.查看所有 |\n");
		printf("|2.修改数据        6.更改设置 |\n");
		printf("|3.查看内容        7.退出系统 |\n");
		printf("|4.删除数据        8.关于系统 |\n");
		printf("|     Powered by LT_lrsoft    |\n");
		printf("-------------------------------\n");
	linput:
		printf("输入操作数：");
		scanf("%d", &input);
		switch (input) {
			case 1:
				Menu_addNewStudent(); break;
			case 2:
				Menu_updateStudentInfo(); break;
			case 3:
				Menu_showStudentInfo(); break;
			case 4:
				Menu_deleteStudent(); break;
			case 5:
				Menu_showAllInfo(); break;
			case 6:
				Menu_changeSetting(); break;
			case 7:
				exit(1); sqlite3_close(SInfoDB);break;
			case 8:
				printf("Github https://github.com/lr8soft/StudentInfo\n"); break;
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