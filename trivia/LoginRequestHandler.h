#pragma once
#include <string>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"

class RequestHandlerFactory;

#define LOGIN 0b0000010

struct RequestResult1
{
	std::string response;
	IRequestHandler newHandler;
}typedef RequestResult1;

struct RequestInfo1
{
	int requestId;
	std::string buffer;
}typedef RequestInfo1;

struct LoginResponse1
{
	unsigned int status;
}typedef LoginResponse1;

class LoginRequestHandler
{
public:
	static RequestResult1 handleRequest(RequestInfo1 reqInfo);
	LoginRequestHandler(LoginManager* m_loginManager, RequestHandlerFactory* m_handleFactory);
	static bool isRequestRelevant(RequestInfo1 reqInfo);
private:
	LoginManager* m_loginManager;
	RequestHandlerFactory* m_handleFactory;
	
};