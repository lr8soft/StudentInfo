#pragma once
#ifndef _features_
#define _features_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SInfo_basicfunc.h"
#endif
int addNewStudent(sqlite3 *db,char *name,char *address,int uuid,double grade) {
	InfoStruct temp = {0,uuid,name,address,grade};
	int ret = addToDatabase(db,temp);
	return ret;
}
InfoStruct *getStudentInfo(sqlite3 *db,int uuid) {
	char name[0xff] = { 0 }, address[0xff] = {0};
	static InfoStruct temp = {0,0,name,address,0};
	char uuid_char[0xff] = { 0 };
	sprintf(uuid_char,"%d",uuid);
	//temp = (InfoStruct*)malloc(sizeof(InfoStruct));
	int ret=inquireBySection(db,"uuid",uuid_char);
	if (ret==1) {
		memcpy(&temp,&infoTemp,sizeof(infoTemp)*sizeof(infoTemp));
		printf("[学号:%d 姓名:%s 住址:%s 总评:%lf]\n", infoTemp.uuid, infoTemp.name, infoTemp.address, infoTemp.grade);
		infoInit();
		return &temp; 
	}
	else {
		return NULL;
	}
}
int updateGradeByUuid(sqlite3 *db,int uuid,double grade) {
	char grade_char[0xff] = {0};
	sprintf(grade_char,"%lf",grade);
	int ret = updataInfoByUuid(db,uuid,"grade",grade_char);
	return ret;
}
int updateNameByUuid(sqlite3 *db, int uuid,const char *name) {
	int ret = updataInfoByUuid(db, uuid, "name",name);
	return ret;
}
int updateAddressByUuid(sqlite3 *db, int uuid, const char *address) {
	int ret = updataInfoByUuid(db, uuid, "address", address);
	return ret;
}
int deleteStudentByUuid(sqlite3 *db,int uuid) {
	int ret = deleteByUuid(db,uuid);
	return ret;
}