#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <map>
#include <poll.h>
#include "client/Client.hpp"

// Le Serveur represente le moteur principal du programme IRC.
// Il stocke la socket d'ecoute, la liste des sockets a surveiller via poll(),
// la map des clients connectes, la logique de communication, ainsi que le
// nettoyage final des ressources. Cette structure permet de gerer plusieurs
// connexions dans un seul processus sans fork() ni thread, et de fermer proprement
// chaque fd quand le serveur s'arrete ou qu'un client se deconnecte.
class Server
{
	private:
		int _serverFd;
		std::string _port;
		std::string _password;
		std::vector<pollfd> _pollFds;
		std::map<int, Client> _clients;

		void initSocket();
		void configureSocket();
		void bindSocket();
		void listenSocket();
		void setNonBlocking(int fd);
		void initPollFds();
		void addClientToPoll(int clientFd);
		void acceptClient();
		void receiveClientData(int clientFd);
		void processClientBuffer(int clientFd);
		void handleClientCommand(int clientFd, const std::string& line);
		void sendToClient(int clientFd, const std::string& message);
		void disconnectClient(int clientFd);
		void closeAllClientFds();

	public:
		Server(std::string port, std::string password);
		~Server();

		void run();
};

#endif