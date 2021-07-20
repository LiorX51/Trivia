#pragma once
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"

#define MENU 0b000100

#define Logout_Request 0b001000
#define Get_Room_Request 0b001001
#define Get_PlayersInRoom_Request 0b001010
#define Join_Room_Request 0b001011
#define Create_Room_Request 0b001100

class RequestHandlerFactory;
struct RequestInfo1;
struct RequestResult1;

class MenuRequestHandler: public IRequestHandler
{
private:
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handleFactory;
public:
	MenuRequestHandler(RoomManager&, RequestHandlerFactory&);
	bool isRequestRelevant(RequestInfo1 reqInfo);
	RequestResult1 handleRequest(RequestInfo1 reqInfo);
};

