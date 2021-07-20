#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory()
{
}

RequestHandlerFactory::RequestHandlerFactory(LoginManager* m_loginManager, SqliteDatabase* m_database)
{
	this->m_database = m_database;
	this->m_loginManager = m_loginManager;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	LoginRequestHandler* log = new LoginRequestHandler(this->m_loginManager, this);
	return log;
}

LoginManager* RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{	
	return new MenuRequestHandler(this->m_RoomManager, *this);
}


RoomManager& RequestHandlerFactory::getRoomManager()
{
	return m_RoomManager;
}
