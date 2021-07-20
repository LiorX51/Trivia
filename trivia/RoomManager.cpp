#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser logged_user, RoomData room_data)
{
	Room room(logged_user, room_data);
	this->m_rooms.insert(std::pair<int, Room>(room_data.id, room));
}

void RoomManager::deleteRoom(int id)
{
	this->m_rooms.erase(id);
}

unsigned int RoomManager::getRoomState(int id)
{
	auto iter = this->m_rooms.find(id);
	return iter->second.getRoomData().isActive;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> result;

	for (auto itr = this->m_rooms.begin(); itr != this->m_rooms.end(); itr++)
	{
		result.push_back(itr->second.getRoomData());
	}
	return result;
}
