#pragma once
#include "sqliteDatabase.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <mutex>

struct LoggedUser
{
	std::string m_username;
	int count_create_room;
	std::string getUsername();
}typedef LoggedUser;

class LoginManager
{
private: 
	SqliteDatabase* m_database;
public:
	std::vector<LoggedUser> m_looggedUsers;
	LoginManager(SqliteDatabase* dataBase);
	LoginManager();
	int signup(std::string, std::string, std::string);
	int login(std::string, std::string);
	void print_count_num();
	void logout(std::string);
	SqliteDatabase* getDatabase();
};

