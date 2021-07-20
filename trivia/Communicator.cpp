#include "Communicator.h"

Communicator::Communicator(RequestHandlerFactory* reqHandleFac)
{
	this->reqHandleFac = reqHandleFac;
	this->logManager = this->reqHandleFac->getLoginManager();
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::Communicator()
{
}

Communicator::~Communicator()
{
	closesocket(m_serverSocket);
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(SERVER_PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// again stepping out to the global namespace
	// Connects between the socket and the configuration (port and etc..)
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << SERVER_PORT << std::endl;

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		accept();
	}
}

void Communicator::accept()
{
	// notice that we step out to the global namespace
	// for the resolution of the function accept

	// this accepts the client and create a specific socket from server to this client
	SOCKET client_socket = ::accept(m_serverSocket, NULL, NULL);

	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;

	// the function that handle the conversation with the client
	LoginRequestHandler logReqHandler(this->logManager, this->reqHandleFac);
	this->m_clients.insert(std::pair<SOCKET,LoginRequestHandler>(client_socket, logReqHandler));
	std::thread t(&Communicator::handleNewClient, this, client_socket);
	t.detach();
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	int recbyte = 0;
	char buf[1024];
	RequestInfo1 reqInfo;
	RequestResult1 reqResult;
	int is_error = 0;

	try
	{
		send(clientSocket, "Hello Daniel, welcome to Ron's & Lior's Trivia app! Have fun", 61, 0);
		while (1)
		{
			ZeroMemory(buf, 1024);

			recbyte = recv(clientSocket, buf, 1024, 0);
			reqInfo.buffer = buf;

			if (LoginRequestHandler::isRequestRelevant(reqInfo)) // Login
			{
				std::string s = reqInfo.buffer;
				LoginRequest logReq;
				std::vector<unsigned char> v(s.begin(), s.end());
				logReq = JsonResponsePacketDeserializer::deserializeLoginRequest(v); // Deserialize the message
				is_error = this->logManager->login(logReq.username, logReq.password); // Check if the user exist in the database				
				if (is_error == 1) // Login succesfully
				{
					reqInfo.requestId = 1; 
					this->reqHandleFac->loggedUser.m_username = logReq.username;
				}
				else // Error
				{
					reqInfo.requestId = 0;
				}
				LoginRequestHandler* logReqHandler = this->reqHandleFac->createLoginRequestHandler();
				reqResult = logReqHandler->handleRequest(reqInfo);
			}
			else // Sign-up
			{
				std::string s = reqInfo.buffer;
				SignupRequest signUpReq;
				std::vector<unsigned char> v(s.begin(), s.end());
				signUpReq = JsonResponsePacketDeserializer::deserializeSignupRequest(v);  // Deserialize the message
				is_error = this->logManager->signup(signUpReq.username, signUpReq.password, signUpReq.email); // Check if the user exist in the database
				if (is_error == 1) // Signed up succesfully
				{
					reqInfo.requestId = 1;
					this->reqHandleFac->loggedUser.m_username = signUpReq.username;
				}
				else
				{
					reqInfo.requestId = 0;
				}
				LoginRequestHandler* logReqHandler = this->reqHandleFac->createLoginRequestHandler();
				reqInfo.buffer.replace(0, 8, "00000010"); // Signed in, now log in..
				reqResult = logReqHandler->handleRequest(reqInfo);
			}

			if (recbyte == SOCKET_ERROR)
			{
				std::cerr << "Quitting" << std::endl;
				break;
			}
		
			send(clientSocket, reqResult.response.c_str(), reqResult.response.length(), 0);

			if (is_error == 1) // Room menu
			{

				ZeroMemory(buf, 1024);

				recbyte = recv(clientSocket, buf, 1024, 0);
				reqInfo.buffer = buf;
						
				MenuRequestHandler* menuReqHandler = this->reqHandleFac->createMenuRequestHandler();
				reqResult = menuReqHandler->handleRequest(reqInfo);

				send(clientSocket, reqResult.response.c_str(), reqResult.response.length(), 0);

				ZeroMemory(buf, 1024);

				recbyte = recv(clientSocket, buf, 1024, 0);
				reqInfo.buffer = buf;

				menuReqHandler = this->reqHandleFac->createMenuRequestHandler();
				reqResult = menuReqHandler->handleRequest(reqInfo);

				send(clientSocket, reqResult.response.c_str(), reqResult.response.length(), 0);

				ZeroMemory(buf, 1024);

				recbyte = recv(clientSocket, buf, 1024, 0);
				reqInfo.buffer = buf;

				menuReqHandler = this->reqHandleFac->createMenuRequestHandler();
				reqResult = menuReqHandler->handleRequest(reqInfo);

				send(clientSocket, reqResult.response.c_str(), reqResult.response.length(), 0);

				//std::chrono::seconds i(3);
				//while (1)
				//{
				//	ZeroMemory(buf, 1024);

				//	recbyte = recv(clientSocket, buf, 1024, 0);
				//	reqInfo.buffer = buf;


				//	MenuRequestHandler* menuReqHandler = this->reqHandleFac->createMenuRequestHandler();
				//	reqResult = menuReqHandler->handleRequest(reqInfo);

				//	send(clientSocket, reqResult.response.c_str(), reqResult.response.length(), 0);
				//	std::this_thread::sleep_for(i);
				//}
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Error\n";
	}
}
