#include "irc.hpp"

// Cette fonction nettoie proprement un client qui s'est deconnecte.
// On ferme son socket, on le retire de la map _clients et on le supprime aussi
// de _pollFds pour ne plus le surveiller dans poll().
void Server::disconnectClient(int clientFd)
{
	std::map<int, Client>::iterator it;
	std::vector<pollfd>::iterator pollIt;

	it = _clients.find(clientFd);
	if (it != _clients.end())
		_clients.erase(it);
	for (pollIt = _pollFds.begin(); pollIt != _pollFds.end(); ++pollIt)
	{
		if (pollIt->fd == clientFd)
		{
			_pollFds.erase(pollIt);
			break ;
		}
	}
	if (clientFd >= 0)
		close(clientFd);
	std::cout << "Client disconnected on fd = " << clientFd << std::endl;
}

// Cette fonction ferme tous les sockets clients encore actifs quand le serveur
// est detruit. Elle permet de tester plusieurs clients et de s'assurer que rien
// ne reste ouvert lorsqu'on quitte proprement le programme.
void Server::closeAllClientFds()
{
	std::map<int, Client>::iterator it;

	for (it = _clients.begin(); it != _clients.end(); ++it)
		close(it->first);
	_clients.clear();
	_pollFds.clear();
}
