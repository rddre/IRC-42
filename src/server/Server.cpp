#include "irc.hpp"

Server::Server(std::string port, std::string password)
	: _port(port), _password(password)
{
}

Server::~Server()
{
}

void Server::run()
{
	std::cout << "Server starting on port " << _port << std::endl;

	initSocket();
	while (true)
	{
		sleep(1);
		std::cout << "Server running..." << std::endl;
	}
}

void Server::initSocket()
{
    _serverFd = socket(AF_INET, SOCK_STREAM, 0);

    if (_serverFd < 0)
    {
        std::cerr << "socket() failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Socket created (fd = " << _serverFd << ")" << std::endl;
}