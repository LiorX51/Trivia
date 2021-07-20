#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RoomManager& roomM, RequestHandlerFactory& reqHandler) : m_roomManager(roomM), m_handleFactory(reqHandler)
{
    m_user.m_username = reqHandler.loggedUser.getUsername();
    m_user.count_create_room = 0;
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo1 reqInfo)
{
    return (reqInfo.buffer.find(std::bitset<8>(MENU).to_string()) != std::string::npos);
}

RequestResult1 MenuRequestHandler::handleRequest(RequestInfo1 reqInfo)
{
    RequestResult1 req_res;

    if (reqInfo.buffer.find(std::bitset<8>(Create_Room_Request).to_string()) != std::string::npos)
    {
        std::vector<uint8_t> vec(reqInfo.buffer.begin(), reqInfo.buffer.end());
        CreateRoomRequest req = JsonResponsePacketDeserializer::deserializeCreateRoomRequest(vec);
        RoomData room_data;
        room_data.maxPlayers = req.maxUsers;
        room_data.name = req.roomName;
        room_data.numOfQuestionsInGame = req.questionCount;
        room_data.timePerQuestion = req.answerTimeout;
        if (this->m_roomManager.m_rooms.size() != 0)
            room_data.id = (this->m_roomManager.m_rooms).size();
        else
            room_data.id = 0;
        this->m_roomManager.createRoom(this->m_user, room_data);

        for (int i = 0; i < this->m_handleFactory.getLoginManager()->m_looggedUsers.size(); i++)
        {
            if (this->m_handleFactory.getLoginManager()->m_looggedUsers[i].m_username == this->m_user.m_username)
            {
                this->m_handleFactory.getLoginManager()->m_looggedUsers[i].count_create_room++;
            }
        }
            
        CreateRoomResponse response;
        response.status = room_data.id;
        vec = JsonResponsePacketSerializer::serializeResponse(response);
        std::string s(vec.begin(), vec.end());
        req_res.response = s;
    }
    else if (reqInfo.buffer.find(std::bitset<8>(Get_Room_Request).to_string()) != std::string::npos)
    {
        GetRoomRespone rooms;
        rooms.rooms = this->m_roomManager.getRooms();
        rooms.status = 1;
        std::vector<uint8_t> vec;
        vec = JsonResponsePacketSerializer::serializeResponse(rooms);
        std::string s(vec.begin(), vec.end());
        req_res.response = s;
    }
    else if (reqInfo.buffer.find(std::bitset<8>(Get_PlayersInRoom_Request).to_string()) != std::string::npos)
    {
        std::vector<uint8_t> vec(reqInfo.buffer.begin(), reqInfo.buffer.end());
        GetPlayersInRoomRequest req = JsonResponsePacketDeserializer::deserializeGetPlayersInRoomRequest(vec);
        GetPlayersInRoomRespone response;
        response.players = this->m_roomManager.m_rooms[req.roomId].getAllUsers();
        vec = JsonResponsePacketSerializer::serializeResponse(response);
        std::string s(vec.begin(), vec.end());
        req_res.response = s;
    }
    else if (reqInfo.buffer.find(std::bitset<8>(Join_Room_Request).to_string()) != std::string::npos)
    {
        JoinRoomResponse response;
        response.status = 1;
        std::vector<uint8_t> vec(reqInfo.buffer.begin(), reqInfo.buffer.end());
        JoinRoomRequest req = JsonResponsePacketDeserializer::deserializeJoinRoomRequest(vec);

        this->m_roomManager.m_rooms[req.roomId].addUser(this->m_user);
        this->m_user.count_create_room++;
        vec = JsonResponsePacketSerializer::serializeResponse(response);
        std::string s(vec.begin(), vec.end());
        req_res.response = s;
    }
    else if (reqInfo.buffer.find(std::bitset<8>(Logout_Request).to_string()) != std::string::npos)
    {
        std::map<int, Room>::iterator it;

        for (it = this->m_roomManager.m_rooms.begin(); it != this->m_roomManager.m_rooms.end(); it++)
        {
            it->second.removeUser(this->m_user);
        }
        this->m_handleFactory.getLoginManager()->logout(this->m_user.getUsername());

        LogoutRespone response;
        response.status = 1;
        std::vector<uint8_t> vec = JsonResponsePacketSerializer::serializeResponse(response);
        std::string s(vec.begin(), vec.end());
        req_res.response = s;
    }
    return req_res;
}
