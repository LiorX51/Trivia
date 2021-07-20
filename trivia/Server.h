#pragma once
#include "Communicator.h"
#include "RequestHandlerFactory.h"
#include "SqliteDatabase.h"

class Server
{
public:
	Server();
	void run();

private:
	SqliteDatabase* m_database;
	RequestHandlerFactory* m_handleFactory;
	Communicator m_communicator;

};

