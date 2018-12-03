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
	double grade;
}InfoStruct;
char charTemp[0xff] = {0};
InfoStruct infoTemp = {0,0,charTemp,0};
void infoInit() {
	infoTemp.id = 0;
	memset(infoTemp.name,0,sizeof(infoTemp.name));
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
                [name] TXT ,\
                [grade] DOUBLE,\
                [uuid] INTEGER,\
                UNIQUE([uuid])\
                );";
	int ret = sqlite3_exec(db,command,0,0,&err_log);
	if (ret!=SQLITE_OK) {
		printf("Can\'t init database!\nError Info:%s\n",err_log);
		sqlite3_close(db);
		return 0;
	}
	else {
		return 1;
	}
}
int addToDatabase(sqlite3 *db,InfoStruct info) {
	char sql[0xfff]="INSERT INTO student (name,grade,uuid)\nVALUES (";
	char grade[0xff],uuid[0xff],id[0xff];
	char *err_log = NULL;
	sprintf(grade,"%lf",info.grade);
	sprintf(uuid,"%d",info.uuid);
	strcat(sql,"\'");
	strcat(sql,info.name);
	strcat(sql,"\',");
	strcat(sql,grade);
	strcat(sql,",");
	strcat(sql,uuid);
	strcat(sql,");");
	int ret = sqlite3_exec(db,sql,0,0,&err_log);
	if (ret!=SQLITE_OK) {
		printf("Can\'t add new data!\nError Info:%s\n",err_log);
		return 0;
	}
	else {
		return 1;
	}
}
int inquireCallBack(void *data,int nline,char **value,char **title) {
	infoInit();
	if (nline==4) {
		infoTemp.id = atoi(value[0]);//atoi:char*->int
		strcpy(infoTemp.name, value[1]);
		infoTemp.grade = strtod(value[2],NULL);//strtod:char*->double
		infoTemp.uuid = atoi(value[3]);
	}
	else {
		printf("Data format error!\n");
	}
	return 0;
}
int inquireByUuid(sqlite3 *db,int uuid) {
	char sql[0xfff] = "SELECT * FROM student WHERE uuid=";
	char *error = NULL, uuid_char[0xff];
	sprintf(uuid_char,"%d",uuid);
	strcat(sql,uuid_char);
	int ret=sqlite3_exec(db,sql,inquireCallBack,0,&error);
	if (ret!=SQLITE_OK) {
		printf("Can\'t search those info!\nError Info:%s\n",error);
	}
	else if (infoTemp.id==0) {
		printf("Uncorrect info!Can\'t search the data!\n");
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
		printf("Can\'t delete info!\nError Info:%s\n",error);
		return 0;
	}
	else {
		return 1;
	}
}