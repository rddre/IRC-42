#include "irc.hpp"

// Ajoute un client dans le vector pollfd pour le surveiller dans la boucle poll().
// C'est la base du multiplexage : le serveur regarde plusieurs fd dans un seul poll().
void Server::addClientToPoll(int clientFd)
{
	struct pollfd clientPollFd;

	clientPollFd.fd = clientFd;
	clientPollFd.events = POLLIN;
	clientPollFd.revents = 0;
	_pollFds.push_back(clientPollFd);
}

// Initialise le vecteur pollfd avec le socket serveur.
// Le socket serveur est le premier element surveille, puis on ajoute ensuite les
// clients acceptes dans la meme liste.
void Server::initPollFds()
{
	struct pollfd serverPollFd;

	_pollFds.clear();
	serverPollFd.fd = _serverFd;
	serverPollFd.events = POLLIN;
	serverPollFd.revents = 0;
	_pollFds.push_back(serverPollFd);
}
