#include "SqliteDatabase.h"

SqliteDatabase::SqliteDatabase()
{
	int res = sqlite3_open(BD_FILE_NAME, &this->db);
	char* errMessage = nullptr;

	if (res == SQLITE_OK)
	{
		return;
	}

    
    const char* sqlStatement = "CREATE TABLE Users("
    "username TEXT PRIMARY KEY NOT NULL,"
    "password TEXT NOT NULL,"
    "email TEXT NOT NULL"
	");";

	res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, &errMessage);

	if (res != SQLITE_OK)
	{
		this->db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
	}

}

bool SqliteDatabase::doesUserExist(std::string username)
{
	int res = sqlite3_open(BD_FILE_NAME, &this->db);
	char* errMessage = nullptr;
	sqlite3_stmt* stmt;
    
	std::string sqlStatement = "SELECT * FROM Users WHERE username='" + username + "';";
	sqlite3_prepare(db, sqlStatement.c_str(), -1, &stmt, NULL);
	res = sqlite3_step(stmt);	

	if (res == SQLITE_DONE)
	{
		return false;
	}

	if (res != SQLITE_OK)
	{
		this->db = nullptr;
		std::cout << "Failed to find user" << std::endl;
		return false;
	}

	return true;
}

bool SqliteDatabase::doesPasswordMatch(std::string username, std::string password)
{
	int res = sqlite3_open(BD_FILE_NAME, &this->db);
	char* errMessage = nullptr;
	sqlite3_stmt* stmt;
    
	std::string sqlStatement = "SELECT * FROM Users WHERE username='" + username + "' AND password='" + password + "';";
	sqlite3_prepare(db, sqlStatement.c_str(), -1, &stmt, NULL);
	res = sqlite3_step(stmt);

	if (res == SQLITE_DONE)
	{
		return false;
	}
	else if(res == SQLITE_ROW)
	{
		return true;
	}

	if (res != SQLITE_OK)
	{
		this->db = nullptr;
		std::cout << "Failed to match user with password" << std::endl;
		return false;
	}

	return true;
}

void SqliteDatabase::addNewUser(std::string username, std::string password, std::string email)
{
	int res = sqlite3_open(BD_FILE_NAME, &this->db);
	char* errMessage = nullptr;

	std::string sqlStatement = "INSERT INTO Users (username, password, email) VALUES ('" + username + "', '" + password + "', '" + email + "');";

	res = sqlite3_exec(db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);

	if (res != SQLITE_OK)
	{
		this->db = nullptr;
		std::cout << "Failed to insert user" << std::endl;
	}
}

void SqliteDatabase::close()
{
	if (this->db != nullptr)
	{
		sqlite3_close(this->db);
		db = nullptr;
	}
}

