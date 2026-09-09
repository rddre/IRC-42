#include "irc.hpp"

// Cette fonction envoie un message a un client donne.
// Le serveur utilise cette methode pour repondre aux commandes IRC ou
// notifier un utilisateur. On garde cette logique dans Server pour centraliser
// toute la communication sortante.
void Server::sendToClient(int clientFd, const std::string& message)
{
	size_t totalSent;
	size_t messageSize;
	ssize_t bytesSent;

	if (clientFd < 0)
		return ;
	messageSize = message.size();
	totalSent = 0;
	while (totalSent < messageSize)
	{
		bytesSent = send(clientFd, message.c_str() + totalSent, messageSize - totalSent, 0);
		if (bytesSent == -1)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				return ;
			perror("send");
			return ;
		}
		if (bytesSent == 0)
			break ;
		totalSent += static_cast<size_t>(bytesSent);
	}
}
