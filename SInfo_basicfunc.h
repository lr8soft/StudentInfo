#pragma once
#ifndef _basicfunc_
#define _basicfunc
#pragma comment(lib,"sqlite/sqlite3.lib")
#include <stdio.h>
#include <stdlib.h>
#include "sqlite/sqlite3.h"
#endif
typedef struct {
	const char *name;
	double grade;
	int uuid;
}InfoStruct;
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
	return 1;
}