#pragma once
#ifndef _basicfunc_
#define _basicfunc
#pragma comment(lib,"sqlite/sqlite3.lib")
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite/sqlite3.h"
#endif
typedef struct {
	int id;
	int uuid;
	char *name;
	char *address;
	double grade;
}InfoStruct;
char charTemp[10] = { 0 };
extern InfoStruct infoTemp = {0,0,charTemp,charTemp,0};
sqlite3 *loadDatabase(sqlite3 *db, const char *path);
void setConfig(int std) {
	FILE *fp;
	char path[0xff] = {0};
	memset(path,0,sizeof(path));
	if (!std) {
		printf("Enter the path of database:");
		scanf("%s", path);
		fp = fopen("data.dat","wb");
		fwrite(path,sizeof(path),1,fp);
		fclose(fp);
	}
	else if (std) {
		fp = fopen("data.dat", "wb");
		fwrite("database\\database.db", sizeof(path), 1, fp);
		fclose(fp);
	}
}
sqlite3 *readConfig(sqlite3 *db) {
	FILE *fp;
	char path[0xfff] = {0};
	fp = fopen("data.dat","rb");
	if (fp==NULL) {
		return NULL;
	}
	else {
		fread(path,sizeof(path),1,fp);
		fclose(fp);
		return loadDatabase(db,path);
	}
}
void infoInit() {
	infoTemp.id = 0;
	memset(infoTemp.name,0,sizeof(infoTemp.name));
	memset(infoTemp.address, 0, sizeof(infoTemp.address));
	infoTemp.uuid = 0;
	infoTemp.grade = 0;
}
sqlite3 *loadDatabase(sqlite3 *db,const char *path) {
	sqlite3 *temp;
	int ret = sqlite3_open(path,&temp);
	if (ret!=SQLITE_OK) {
		printf("Can\'t load \'%s\'!\n",path);
		sqlite3_close(db);
		return NULL;
	}
	else {
		db = temp;
		return db;
	}
}
int databaseInit(sqlite3 *db) {
	if (db == NULL) return -1;
	char *err_log=NULL;
	char command[] = "CREATE TABLE IF NOT EXISTS student (\
                [id] INTEGER PRIMARY KEY AUTOINCREMENT,\
                [name] TXT,\
				[address] TXT,\
                [grade] DOUBLE,\
                [uuid] INTEGER,\
                UNIQUE([uuid])\
                );";
	int ret = sqlite3_exec(db,command,0,0,&err_log);
	if (ret!=SQLITE_OK) {
		printf("\nCan\'t init database!\nError Info:%s\n",err_log);
		sqlite3_close(db);
		return 0;
	}
	else {
		return 1;
	}
}
int addToDatabase(sqlite3 *db,InfoStruct info) {
	char sql[0xfff] = {0};
	char grade[0xff],uuid[0xff],id[0xff];
	char *err_log = NULL;
	sprintf(grade,"%lf",info.grade);
	sprintf(uuid,"%d",info.uuid);
	sprintf(sql,"INSERT INTO student (name,address,grade,uuid)\n\
VALUES (\'%s\',\'%s\',%s,%s);",info.name,info.address,grade,uuid);
	int ret = sqlite3_exec(db,sql,0,0,&err_log);
	if (ret!=SQLITE_OK) {
		printf("\nCan\'t add new data!\nError Info:%s\n",err_log);
		return 0;
	}
	else {
		return 1;
	}
}
int inquireCallBack(void *data,int nline,char **value,char **title) {
	infoInit();
	if (nline==5) {
		infoTemp.id = atoi(value[0]);//atoi:char*->int
		infoTemp.name = (char*)malloc(sizeof(value[1]));
		infoTemp.address = (char*)malloc(sizeof(value[2]));
		strcpy(infoTemp.name , value[1]);
		strcpy(infoTemp.address , value[2]);
	//	memcpy(infoTemp.name, value[1],sizeof(value[1]));
	//	memcpy(infoTemp.address, value[2], sizeof(value[2]));
		infoTemp.grade = strtod(value[3],NULL);//strtod:char*->double
		infoTemp.uuid = atoi(value[4]);
	//	printf("[学号:%d 姓名:%s 住址:%s 总评:%lf]\n", infoTemp.uuid, infoTemp.name, infoTemp.address, infoTemp.grade);
	}
	else {
		printf("\nData format error!\n");
	}
	return 0;
}
int inquireBySection(sqlite3 *db,const char *type, const char *info) {
	char sql[0xfff] = { 0 };//"SELECT * FROM student WHERE uuid=";
	char *error = NULL;
	if (info == NULL || type == NULL) return 0;
//	strcat(sql,uuid_char);
	sprintf(sql,"SELECT * FROM student WHERE %s=%s",type,info);
	int ret=sqlite3_exec(db,sql,inquireCallBack,0,&error);
	if (ret!=SQLITE_OK) {
		printf("\nCan\'t search those info!\nError Info:%s\n",error);
		return 0;
	}else if (infoTemp.id==0) {
		printf("\nUncorrect info!Can\'t search the data!\n");
		return 0;
	}else {
		return 1;
	}
}
int deleteByUuid(sqlite3 *db,int uuid) {
	char sql[0xfff] = "DELETE from student WHERE uuid=";
	char char_uuid[0xff],*error=NULL;
	sprintf(char_uuid,"%d",uuid);
	strcat(sql,char_uuid);
	int ret = sqlite3_exec(db,sql,0,0,&error);
	if (ret!=SQLITE_OK) {
		printf("\nCan\'t delete info!\nError Info:%s\n",error);
		return 0;
	}
	else {
		return 1;
	}
}
int updataInfoByUuid(sqlite3 *db,int uuid,const char *type,const char *info) {
	char sql[0xfff] = { 0 }, uuid_char[20] = {0},*error=NULL;
	sprintf(uuid_char,"%d",uuid);
	if (info == NULL || type == NULL) return 0;
	if (strcmp(type,"name")==0|| strcmp(type, "address") == 0) {
		sprintf(sql, "UPDATE student SET %s=\'%s\' WHERE uuid=%s",type,info,uuid_char);
	}else {
		sprintf(sql, "UPDATE student SET %s=%s WHERE uuid=%s",type, info, uuid_char);
	}
//	printf("%s\n",sql);
	int ret = sqlite3_exec(db,sql,0,0,&error);
	if (ret!=SQLITE_OK) {
		printf("\nCan\'t update info!\nError Info:%s\n", error);
		return 0;
	}
	else {
		return 1;
	}
}
int showAllCallback(void *data, int nline, char **value, char **title) {
	int i,j=1;
	for (i = 0; i < nline;i++) {
		printf("[%s=%s]",title[i],value[i]);
		if (j==5) printf("\n"),j=0;
		j++;
	}
	return 0;
}
void showAllInfo(sqlite3 *db) {
	char sql[] = "SELECT * FROM student";
	sqlite3_exec(db,sql,showAllCallback,0,NULL);
}
