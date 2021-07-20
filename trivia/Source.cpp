#include "Server.h"
#include "JsonResponsePacketSerializer.h"

int main()
{
    try
    {       
        Server myServer;

        myServer.run();
    }
    catch (std::exception& e)
    {
        std::cout << "Error occured: " << e.what() << std::endl;
    }

	return 0;
}