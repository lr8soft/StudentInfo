
#include "pch.h"
#include "SInfo_basicfunc.h"
void main()
{
	sqlite3 *db=NULL;
	db = loadDatabase(db,"database\\database.db");
	databaseInit(db);
	inquireByUuid(db,23333);
	printf("[Id:%d Uuid:%d Grade:%lf Name:%s]",infoTemp.id,infoTemp.uuid,infoTemp.grade,infoTemp.name);
	deleteByUuid(db,23333);
}