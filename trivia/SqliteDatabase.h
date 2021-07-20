#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#define BD_FILE_NAME "MyDB.sqlite"


class SqliteDatabase : public IDatabase
{
private:
	
	sqlite3* db;

public: 
	SqliteDatabase();
	bool doesUserExist(std::string);
	bool doesPasswordMatch(std::string, std::string);
	void addNewUser(std::string, std::string, std::string);
	void close();
};

