#pragma once
#include <iostream>
#include <vector>
#include "IDatabase.h"

class StatisticManager
{
private:
	IDatabase* m_database;
public:
	std::vector<std::string> getStatistics();
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string username);
};

