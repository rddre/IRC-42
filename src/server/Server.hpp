#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <map>
#include <poll.h>
#include "client/Client.hpp"

class Channel;

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
		std::map<std::string, Channel*> _channels;

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
		void disconnectClient(int clientFd);
		void closeAllClientFds();

	public:
		void sendToClient(int clientFd, const std::string& message);
		Server(std::string port, std::string password);
		~Server();

		const std::string& getPassword() const;
		std::map<int, Client>& getClients();
		std::map<std::string, Channel*>& getChannels();
		Channel* getChannel(const std::string& name) const;
		Channel* createChannel(const std::string& name);

		void run();
};

#endif