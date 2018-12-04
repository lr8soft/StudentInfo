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
	InfoStruct *temp;
	//temp = (InfoStruct*)malloc(sizeof(InfoStruct));
	if (!(temp = (InfoStruct*)malloc(sizeof(InfoStruct)))) {
		temp->grade = infoTemp.grade;
		temp->uuid = infoTemp.uuid;
		temp->id = infoTemp.id;
		sprintf(temp->name,"%s",infoTemp.name);
		infoInit();
		return temp; 
	}
	else {
		return NULL;
	}
}
int updateGradeByUuid(sqlite3 *db,int uuid,double grade) {
	char grade_char[10] = {0};
	sprintf(grade_char,"%lf",grade);
	int ret = updataInfoByUuid(db,uuid,"grade",grade_char);
	return ret;
}
int updateNameByUuid(sqlite3 *db, int uuid,const char *name) {
	int ret = updataInfoByUuid(db, uuid, "name",name);
	return ret;
}
int deleteStudentByUuid(sqlite3 *db,int uuid) {
	int ret = deleteByUuid(db,uuid);
	return ret;
}