#pragma once

#include <iostream>
#include <vector>
#include "json.hpp"
#include <string>
#include <bitset>
#include <climits>

#define ERROR 0b0000001
#define LOGIN 0b0000010
#define SIGNUP 0b0000011

//using json = nlohmann::json;

struct LoginRequest
{
	std::string username;
	std::string password;
}typedef LoginRequest;

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
}typedef SignupRequest;

struct GetPlayersInRoomRequest
{
	unsigned int roomId;
}typedef GetPlayersInRoomRequest;

struct JoinRoomRequest
{
	unsigned int roomId;
}typedef JoinRoomRequest;

struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;

}typedef CreateRoomRequest;

class JsonResponsePacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> log);
	static SignupRequest deserializeSignupRequest(std::vector<unsigned char> signup);

	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(std::vector<unsigned char> req);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<unsigned char> req);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<unsigned char> req);

private:
	static std::string bitset_to_string(std::bitset<8> bits);
};

