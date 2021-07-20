#include "JsonResponsePacketSerializer.h"

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse err)
{
    std::string final_msg = err.message;

    std::string bitSTR = "";

    for (std::size_t i = 0; i < final_msg.size(); ++i)
    {
        bitSTR += std::bitset<8>(final_msg.c_str()[i]).to_string();
        bitSTR += " ";
    }

    std::string r_string = std::bitset<8>(ERROR).to_string() + "$" + std::bitset<8>(bitSTR.size()).to_string() +"$" + bitSTR;

    std::vector<unsigned char> vec(r_string.begin(), r_string.end());

    return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse log)
{
    std::string final_username = log.username;
    std::string final_password = log.password;

    std::string bitSTR = "";

    for (std::size_t i = 0; i < final_username.size(); ++i)
    {
        bitSTR += std::bitset<8>(final_username.c_str()[i]).to_string();
    }
    bitSTR += "$";
    for (std::size_t i = 0; i < final_password.size(); ++i)
    {
        bitSTR += std::bitset<8>(final_password.c_str()[i]).to_string();
    }

    std::string r_string = std::bitset<8>(LOGIN).to_string() + "$" + std::bitset<8>(bitSTR.size()).to_string() + "$" + bitSTR;

    std::vector<unsigned char> vec(r_string.begin(), r_string.end());

    std::string s(vec.begin(), vec.end());
    std::cout << s;

    return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse signup)
{
    std::string final_username = signup.username;
    std::string final_password = signup.password;
    std::string final_email = signup.email;

    std::string bitSTR = "";

    for (std::size_t i = 0; i < final_username.size(); ++i)
    {
        bitSTR += std::bitset<8>(final_username.c_str()[i]).to_string();
    }
    bitSTR += "$";
    for (std::size_t i = 0; i < final_password.size(); ++i)
    {
        bitSTR += std::bitset<8>(final_password.c_str()[i]).to_string();
    }
    bitSTR += "$";
    for (std::size_t i = 0; i < final_email.size(); ++i)
    {
        bitSTR += std::bitset<8>(final_email.c_str()[i]).to_string();
    }

    std::string r_string = std::bitset<8>(SIGNUP).to_string() + "$" + std::bitset<8>(bitSTR.size()).to_string() + "$" + bitSTR;

    std::vector<unsigned char> vec(r_string.begin(), r_string.end());

    std::string s(vec.begin(), vec.end());
    std::cout << s;

    return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LogoutRespone logout)
{
    std::string bitSTR = "";

    bitSTR = logout.status;

    bitSTR += "$";

    std::string r_string = std::bitset<8>(Logout_Response).to_string() + "$" + std::bitset<8>(bitSTR.size()).to_string() + "$" + bitSTR;

    std::vector<unsigned char> vec(r_string.begin(), r_string.end());

    std::string s(vec.begin(), vec.end());

    return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomRespone room)
{
    std::string bitSTR = "";

    std::vector<RoomData> rooms = room.rooms;

    for (std::vector<RoomData>::iterator it = rooms.begin(); it != rooms.end(); ++it) {
        bitSTR += "$";
        bitSTR += std::to_string(it->id) + "*";
        for (std::size_t i = 0; i < it->name.size(); ++i)
        {
            bitSTR += std::bitset<8>(it->name.c_str()[i]).to_string();
        }
        bitSTR += "*" + std::to_string(it->maxPlayers);
        bitSTR += "*" + std::to_string(it->numOfQuestionsInGame);
        bitSTR += "*" + std::to_string(it->timePerQuestion);
        //bitSTR += "*" + it->isActive;
    }
    std::string r_string = std::bitset<8>(Get_Room_Response).to_string() + "$" + std::bitset<8>(bitSTR.size()).to_string() + bitSTR;

    std::vector<unsigned char> vec(r_string.begin(), r_string.end());

    std::string s(vec.begin(), vec.end());

    return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomRespone players_in_room)
{
    std::string bitSTR = "";

    std::vector<std::string> players = players_in_room.players;

    for (std::vector<std::string>::iterator it = players.begin(); it != players.end(); ++it) {
        for (std::size_t i = 0; i < it->size(); ++i)
        {
            bitSTR += std::bitset<8>(it->c_str()[i]).to_string();
        }
        bitSTR += "$";
    }
    std::string r_string = std::bitset<8>(Get_PlayersInRoom_Response).to_string() + "$" + std::bitset<8>(bitSTR.size()).to_string() + "$" + bitSTR;

    std::vector<unsigned char> vec(r_string.begin(), r_string.end());

    std::string s(vec.begin(), vec.end());

    return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse joinRoom)
{
    std::string bitSTR = "";

    bitSTR = joinRoom.status;

    bitSTR += "$";

    std::string r_string = std::bitset<8>(Join_Room_Response).to_string() + "$" + std::bitset<8>(bitSTR.size()).to_string() + "$" + bitSTR;

    std::vector<unsigned char> vec(r_string.begin(), r_string.end());

    std::string s(vec.begin(), vec.end());

    return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoom)
{
    std::string bitSTR = "";

    bitSTR = std::to_string(createRoom.status);

    std::string r_string = std::bitset<8>(Create_Room_Response).to_string() + "$" + std::bitset<8>(bitSTR.size()).to_string() + "$" + bitSTR;

    std::vector<unsigned char> vec(r_string.begin(), r_string.end());

    std::string s(vec.begin(), vec.end());

    return vec;
}