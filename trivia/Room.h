#pragma once
#include <iostream>
#include <vector>
#include "LoginManager.h"

struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
}typedef RoomData;

class Room
{
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
public:
	Room();
	Room(LoggedUser logged_user, RoomData room_data);
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();
	RoomData getRoomData();
};

