#include "irc.hpp"

// Cette fonction lit les donnees envoyees par un client sur son socket.
// On utilise recv() en mode non bloquant pour ne pas bloquer la boucle principale.
// Les donnees lues sont ajoutees au buffer du client, puis on tente de traiter
// les commandes completes terminees par \r\n.
void Server::receiveClientData(int clientFd)
{
	char buffer[512];
	ssize_t bytesRead;
	std::map<int, Client>::iterator it;

	it = _clients.find(clientFd);
	if (it == _clients.end())
		return ;
	while (true)
	{
		bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
		if (bytesRead == -1)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				return ;
			perror("recv");
			return ;
		}
		if (bytesRead == 0)
		{
			std::cout << "Client disconnected on fd = " << clientFd << std::endl;
			disconnectClient(clientFd);
			return ;
		}
		buffer[bytesRead] = '\0';
		it->second.appendBuffer(std::string(buffer, static_cast<size_t>(bytesRead)));
		processClientBuffer(clientFd);
		if (bytesRead < static_cast<ssize_t>(sizeof(buffer) - 1))
			break ;
	}
}

// Cette fonction traite le buffer d'un client pour extraire les lignes completes.
// Une ligne IRC est terminee par \r\n. Quand on en trouve une, on la traite comme
// une commande et on la passe a la couche de parsing / commandes.
void Server::processClientBuffer(int clientFd)
{
	std::map<int, Client>::iterator it;
	std::string buffer;
	std::string::size_type pos;

	it = _clients.find(clientFd);
	if (it == _clients.end())
		return ;
	buffer = it->second.getBuffer();
	pos = buffer.find("\r\n");
	while (pos != std::string::npos)
	{
		std::string line = buffer.substr(0, pos);
		buffer.erase(0, pos + 2);
		if (!line.empty())
			handleClientCommand(clientFd, line);
		pos = buffer.find("\r\n");
	}
	it->second.setBuffer(buffer);
}

// Cette fonction est l'interface entre la communication reseau et la logique IRC.
// On recoit une ligne complete, on la passe au Parser pour la decomposer,
// puis au CommandHandler pour l'executer.
void Server::handleClientCommand(int clientFd, const std::string& line)
{
	Parser parser;
	CommandHandler commandHandler;
	std::vector<std::string> tokens;

	(void)clientFd;
	tokens = parser.parse(line);
	if (tokens.empty())
		return ;
	std::cout << "Command received: " << line << std::endl;
	commandHandler.execute(line);
}
