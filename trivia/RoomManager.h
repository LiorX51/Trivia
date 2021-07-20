#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "Room.h"

class RoomManager
{
public: 
	std::map<int, Room> m_rooms;
	void createRoom(LoggedUser logged_user, RoomData room_data);
	void deleteRoom(int id);
	unsigned int getRoomState(int id);
	std::vector<RoomData> getRooms();
};

