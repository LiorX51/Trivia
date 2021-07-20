#include "LoginRequestHandler.h"
#include <bitset>

bool LoginRequestHandler::isRequestRelevant(RequestInfo1 reqInfo)
{
	return (reqInfo.buffer.find(std::bitset<8>(LOGIN).to_string()) != std::string::npos);
}

RequestResult1 LoginRequestHandler::handleRequest(RequestInfo1 reqInfo)
{
	if (isRequestRelevant(reqInfo))
	{
		RequestResult1 res;
		
		
		ErrorResponse er;
		if (reqInfo.requestId == 1)
		{
			er.message = "Logged in successfully";
		}
		else
		{
			er.message = "Can't log in";
		}
		std::vector<unsigned char> a = JsonResponsePacketSerializer::serializeResponse(er);

		std::string s(a.begin(), a.end());

		res.response = s;

		res.newHandler = IRequestHandler();
		return res;
	}
}

LoginRequestHandler::LoginRequestHandler(LoginManager* m_loginManager, RequestHandlerFactory* m_handleFactory)
{
	this->m_handleFactory = m_handleFactory;
	this->m_loginManager = m_loginManager;
}
