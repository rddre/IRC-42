#include "irc.hpp"

// Cette methode est la base pour accepter un client entrant.
// En pratique, elle cree un socket client dedie, le met en non bloquant,
// puis l'ajoute a la map et au vector pollfd pour que le serveur le surveille.
void Server::acceptClient()
{
	int clientFd;
	Client client;

	clientFd = accept(_serverFd, NULL, NULL);
	if (clientFd == -1)
	{
		perror("accept");
		return ;
	}
	if (fcntl(clientFd, F_SETFL, O_NONBLOCK) == -1)
	{
		perror("fcntl");
		close(clientFd);
		return ;
	}
	client.setFd(clientFd);
	_clients.insert(std::make_pair(clientFd, client));
	addClientToPoll(clientFd);
	std::cout << "Client accepted on fd = " << clientFd << std::endl;
}
