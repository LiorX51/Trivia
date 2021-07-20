#pragma comment (lib, "ws2_32.lib")

#include "Server.h"

Server::Server(): m_handleFactory(new RequestHandlerFactory(new LoginManager(m_database), m_database)), m_communicator(m_handleFactory), m_database(new SqliteDatabase())
{

}

void Server::run()
{
	m_communicator.bindAndListen();
}
