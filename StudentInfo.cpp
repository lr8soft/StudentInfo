
#include "pch.h"
#include "SInfo_basicfunc.h"
void main()
{
	sqlite3 *db=NULL;
	db = loadDatabase(db,"database\\database.db");
	databaseInit(db);
}