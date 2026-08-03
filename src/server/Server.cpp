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
}
