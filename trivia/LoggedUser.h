#pragma once

#include <iostream>
#include <string>

class LoggedUser
{
private:
	std::string m_username;
public:
	std::string getUsername();
};
