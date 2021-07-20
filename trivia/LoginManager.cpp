#include "LoginManager.h"

LoginManager::LoginManager(SqliteDatabase* dataBase)
{
	this->m_database = dataBase;

	std::thread t(&LoginManager::print_count_num, this);
	t.detach();
}

LoginManager::LoginManager()
{
	this->m_database->close();
}

int LoginManager::signup(std::string username, std::string password, std::string email)
{
	if (!m_database->doesUserExist(username))
	{
		m_database->addNewUser(username, password, email);
		LoggedUser new_user;
		new_user.m_username = username;
		m_looggedUsers.push_back(new_user);
		return 1;
	}
	else
	{
		std::cout << username << "is already in the database\n";
		return 0;
	}
}

int LoginManager::login(std::string username, std::string password)
{
	LoggedUser temp;
	temp.m_username = username;
	if (m_database->doesPasswordMatch(username, password))
	{
		LoggedUser new_user;
		new_user.m_username = username;
		for (int i = 0; i < this->m_looggedUsers.size(); i++)
		{
			if (this->m_looggedUsers[i].m_username == username)
			{
				std::cout << username << " is already logged in\n";
				return 0;
			}
		}
		m_looggedUsers.push_back(new_user);
		return 1;
	}
	std::cout << "There is no " << username << " in the database\n";
	return 0;
}

void LoginManager::print_count_num()
{
	std::chrono::seconds i(3);
	while (1)
	{
		for (int i = 0; i < m_looggedUsers.size(); i++)
		{
			std::cout << m_looggedUsers[i].m_username << ": " << m_looggedUsers[i].count_create_room << std::endl;
		}

		std::this_thread::sleep_for(i);
}
}

bool operator==(LoggedUser& user, std::string& name)
{
	return user.m_username == name;
}

void LoginManager::logout(std::string username)
{
	if(m_database->doesUserExist(username))
	{
		for(int i=0; i < m_looggedUsers.size(); i++)
		{
			if(m_looggedUsers[i].m_username == username)
			{
				m_looggedUsers.erase(m_looggedUsers.begin() + i);
			}
		}

	}
	else
	{
		std::cout << "There is no " << username << "in the database\n";
	}
}

SqliteDatabase* LoginManager::getDatabase()
{
	return this->m_database;
}

std::string LoggedUser::getUsername()
{
	return this->m_username;
}
