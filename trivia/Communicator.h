#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <string>
#include <map>
#include <WinSock2.h>
#include "IRequestHandler.h" 
#include "WSAInitializer.h"
#include "Helper.h"
#include "LoginRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include <io.h>
#include <exception>
#include <Windows.h>
#include <chrono>


#define SERVER_PORT 666

class Communicator
{
public:
	Communicator(RequestHandlerFactory* reqHandleFac);
	Communicator();
	~Communicator();
	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
	void accept();

private:
	SOCKET m_serverSocket;
	RequestHandlerFactory* reqHandleFac;
	LoginManager* logManager;
	std::map<SOCKET, LoginRequestHandler> m_clients;
	WSAInitializer wsa;
};


