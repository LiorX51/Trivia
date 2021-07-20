#pragma once
#include "LoginRequestHandler.h"
#include "RoomManager.h"
#include "StatisticManager.h"
#include "MenuRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory();
	RequestHandlerFactory(LoginManager* m_loginManager, SqliteDatabase* m_database);
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager* getLoginManager();
	MenuRequestHandler* createMenuRequestHandler();
	RoomManager& getRoomManager();
	LoggedUser loggedUser;
private:
	LoginManager* m_loginManager;
	SqliteDatabase* m_database;
	RoomManager m_RoomManager;
};

