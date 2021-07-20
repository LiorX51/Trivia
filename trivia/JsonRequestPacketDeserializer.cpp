#include "JsonRequestPacketDeserializer.h"
#include <algorithm>
#include <iterator>
#include <math.h>

std::string JsonResponsePacketDeserializer::bitset_to_string(std::bitset<8> bits)
{
    std::string toReturn;
    char next = 0;
    for(size_t i = 0; i < 8; ++i)
    {
        size_t index = 8 - i - 1;
        size_t pos = 8 - i - 1;

        if (bits[index])
        {
            next = (next + pow(2, i));
        }
    }
    toReturn.push_back(next);
    return toReturn;
}

LoginRequest JsonResponsePacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> login)
{
	LoginRequest r_request;

    std::string str(login.begin(), login.end());

    for(int i = 0; i < 2; i++)
    {
        str.erase(0, str.find('$') + 1);
    }
    std::cout << "\n";

    for(int i = 0; i < 2; i++)
    {
        std::string temp(str.substr(0, str.find('$')));
        for (int j = 0; j < (temp.length() - std::count(temp.begin(), temp.end(), '$')) / 8; j++)
        {
            std::string byte = temp.substr(j * 8, 8); 
            std::reverse(byte.begin(), byte.end());
            std::bitset<8> bits(byte.c_str());
            
            if (i == 0)
                r_request.username += bitset_to_string(bits);
            else
                r_request.password += bitset_to_string(bits);
        }
        
        str.erase(0, str.find('$') + 1);
    }

	return r_request;
}

SignupRequest JsonResponsePacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> signup)
{
    SignupRequest r_request;
    std::bitset<8> bits;

    std::string str(signup.begin(), signup.end());

    for (int i = 0; i < 2; i++)
    {
        str.erase(0, str.find('$') + 1);
    }
    std::cout << "\n";

    for (int i = 0; i < 3; i++)
    {
        std::string temp(str.substr(0, str.find('$')));
        for (int j = 0; j < (temp.length() - std::count(temp.begin(), temp.end(), '$')) / 8; j++)
        {
            std::string byte = temp.substr(j * 8, 8);
            std::reverse(byte.begin(), byte.end());
            std::bitset<8> bits(byte.c_str());

            if (i == 0)
                r_request.username += bitset_to_string(bits);
            else if (i == 1)
                r_request.password += bitset_to_string(bits);
            else
                r_request.email += bitset_to_string(bits);
        }

        str.erase(0, str.find('$') + 1);
    }

    return r_request;
}

GetPlayersInRoomRequest JsonResponsePacketDeserializer::deserializeGetPlayersInRoomRequest(std::vector<unsigned char> req)
{
    GetPlayersInRoomRequest r_request;
    std::bitset<8> bits;

    std::string str(req.begin(), req.end());

    for (int i = 0; i < 2; i++)
    {
        str.erase(0, str.find('$') + 1);
    }
    std::cout << "\n";

    r_request.roomId = std::stoul(str, nullptr, 0);
    std::cout << "/n" << r_request.roomId;

    return r_request;
}

JoinRoomRequest JsonResponsePacketDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> req)
{
    JoinRoomRequest r_request;
    std::bitset<8> bits;

    std::string str(req.begin(), req.end());

    for (int i = 0; i < 2; i++)
    {
        str.erase(0, str.find('$') + 1);
    }
    std::cout << "\n";

    r_request.roomId = std::stoul(str, nullptr, 0);
    std::cout << "/n" << r_request.roomId;

    return r_request;
}

CreateRoomRequest JsonResponsePacketDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> req)
{
    CreateRoomRequest r_request;
    std::bitset<8> bits;

    std::string str(req.begin(), req.end());

    for (int i = 0; i < 2; i++)
    {
        str.erase(0, str.find('$') + 1);
    }
        std::string temp(str.substr(0, str.find('$')));
        for (int j = 0; j < (temp.length() - std::count(temp.begin(), temp.end(), '$')) / 8; j++)
        {
            std::string byte = temp.substr(j * 8, 8);
            std::reverse(byte.begin(), byte.end());
            std::bitset<8> bits(byte.c_str());

            r_request.roomName += bitset_to_string(bits);
        }

        str.erase(0, str.find('$') + 1);
        temp = (str.substr(0, str.find('$')));
        r_request.maxUsers = std::stoul(temp, nullptr, 0);
        str.erase(0, str.find('$') + 1);
        temp = (str.substr(0, str.find('$')));
        r_request.questionCount = std::stoul(temp, nullptr, 0);
        str.erase(0, str.find('$') + 1);
        r_request.answerTimeout = std::stoul((str), nullptr, 0);       

    return r_request;
}
