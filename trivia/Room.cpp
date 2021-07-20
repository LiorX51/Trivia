#include "Room.h"

Room::Room()
{
}

Room::Room(LoggedUser logged_user, RoomData room_data)
{
	this->m_metadata = room_data;
	this->m_users.push_back(logged_user);
}

void Room::addUser(LoggedUser user)
{
	this->m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	//std::vector<LoggedUser>::iterator new_end;
	//new_end = remove(this->m_users.begin(), this->m_users.end(), user);
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> result;

	for (int i = 0; i < this->m_users.size(); i++)
		result.push_back(this->m_users[i].getUsername());

	return result;
}

RoomData Room::getRoomData()
{
	return this->m_metadata;
}
