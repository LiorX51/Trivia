#pragma once

#include <iostream>
#include <vector>
#include "json.hpp"
#include <string>
#include <bitset>
#include <algorithm>
#include "room.h"

#define ERROR 0b000001
#define LOGIN 0b000010
#define SIGNUP 0b000011
#define MENU 0b000100

#define Logout_Response 0b001000
#define Get_Room_Response 0b001001
#define Get_PlayersInRoom_Response 0b001010
#define Join_Room_Response 0b001011
#define Create_Room_Response 0b001100

using json = nlohmann::json;

struct ErrorResponse
{
	std::string message;
}typedef ErrorResponse;

struct LoginResponse
{
	std::string username;
	std::string password;
}typedef LoginResponse;

struct SignupResponse
{
	std::string username;
	std::string password;
	std::string email;
}typedef SignupResponse;

struct LogoutRespone
{
	unsigned int status;
}typedef LogoutRespone;

struct GetRoomRespone
{
	unsigned int status;
	std::vector<RoomData> rooms;
}typedef GetRoomRespone;

struct GetPlayersInRoomRespone
{
	std::vector<std::string> players;
}typedef GetPlayersInRoomRespone;

struct JoinRoomResponse
{
	unsigned int status;
}typedef JoinRoomResponse;

struct CreateRoomResponse
{
	unsigned int status;
}typedef CreateRoomResponse;

class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse err);
	static std::vector<unsigned char> serializeResponse(LoginResponse log);
	static std::vector<unsigned char> serializeResponse(SignupResponse signup);
	static std::vector<unsigned char> serializeResponse(LogoutRespone logout);
	static std::vector<unsigned char> serializeResponse(GetRoomRespone room);
	static std::vector<unsigned char> serializeResponse(GetPlayersInRoomRespone players_in_room);
	static std::vector<unsigned char> serializeResponse(JoinRoomResponse joinRoom);
	static std::vector<unsigned char> serializeResponse(CreateRoomResponse createRoom);

};
