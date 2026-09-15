#include "irc.hpp"

// Le constructeur initialise le serveur avec son port et son mot de passe.
// _serverFd est mis a -1 pour signifier qu'aucune socket n'est encore ouverte.
Server::Server(std::string port, std::string password)
	: _serverFd(-1), _port(port), _password(password)
{
}

// Le destructeur ferme proprement les ressources du serveur lorsqu'il disparaît.
// On ferme tout d'abord les sockets clients puis le socket d'ecoute, pour éviter
// les fuites de descripteurs et laisser le système proprement dans un etat net.
Server::~Server()
{
	std::map<std::string, Channel*>::iterator it;

	for (it = _channels.begin(); it != _channels.end(); ++it)
		delete it->second;
	_channels.clear();
	closeAllClientFds();
    if (_serverFd != -1)
    {
        close(_serverFd);
        _serverFd = -1;
    }
}

const std::string& Server::getPassword() const
{
	return (_password);
}

std::map<int, Client>& Server::getClients()
{
	return (_clients);
}

std::map<std::string, Channel*>& Server::getChannels()
{
	return (_channels);
}

Channel* Server::getChannel(const std::string& name) const
{
	std::map<std::string, Channel*>::const_iterator it = _channels.find(name);
	if (it == _channels.end())
		return (NULL);
	return (it->second);
}

Channel* Server::createChannel(const std::string& name)
{
	Channel* channel = getChannel(name);
	if (channel != NULL)
		return (channel);
	channel = new Channel(name);
	_channels.insert(std::make_pair(name, channel));
	return (channel);
}

// Cette fonction lance le cycle principal du serveur.
// On initialise la socket, on l'ecoute, puis on surveille les events avec poll().
// Quand un client se connecte, on l'accepte et on le stocke dans la map.
// Ensuite, si un client est pret a lire, on lit ses donnees et on les transforme
// en commandes IRC logiques pour la suite du projet.
void Server::run()
{
	std::cout << "Server starting on port " << _port << std::endl;

	initSocket();
	configureSocket();
	bindSocket();
	listenSocket();
	setNonBlocking(_serverFd);
	initPollFds();

	while (true)
	{
		int pollRet = poll(&_pollFds[0], _pollFds.size(), -1);

		if (pollRet == -1)
		{
			if (errno == EINTR)
				continue;
			perror("poll");
			break;
		}
		for (size_t i = 0; i < _pollFds.size(); ++i)
		{
			if (_pollFds[i].revents & POLLIN)
			{
				if (_pollFds[i].fd == _serverFd)
				{
					std::cout << "New connection detected on server socket" << std::endl;
					acceptClient();
				}
				else
				{
					std::cout << "Client socket ready to be read" << std::endl;
					receiveClientData(_pollFds[i].fd);
				}
			}
		}
	}
}
