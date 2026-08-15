#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <poll.h>

class Client;
class Channel;
class CommandHandler;
class Parser;

/**
 * @class Server
 * @brief Classe principale du serveur IRC
 * 
 * Gère:
 * - Les connexions TCP
 * - Le polling des clients
 * - L'authentification
 * - Les canaux
 * - La distribution des messages
 */
class Server
{
public:
	Server(int port, const std::string &password);
	~Server(void);

	// Getters
	int getPort(void) const;
	std::string getPassword(void) const;
	std::vector<Client *> getClients(void) const;
	std::vector<Channel *> getChannels(void) const;
	Client *getClientByNickname(const std::string &nickname) const;
	Channel *getChannelByName(const std::string &name) const;

	// Server operations
	int start(void);
	int run(void);
	void stop(void);

	// Client management
	void addClient(Client *client);
	void removeClient(Client *client);
	Client *acceptNewClient(void);

	// Channel management
	Channel *createChannel(const std::string &name);
	void removeChannel(Channel *channel);

	// Message handling
	void broadcastMessage(const std::string &message, Client *exclude = NULL);
	void sendToClient(Client *client, const std::string &message);

	// Getters for Part B
	CommandHandler *getCommandHandler(void) const;
	Parser *getParser(void) const;

private:
	int _port;
	std::string _password;
	int _serverSocket;
	bool _running;

	std::vector<Client *> _clients;
	std::vector<Channel *> _channels;
	std::vector<pollfd> _pollFds;

	CommandHandler *_commandHandler;
	Parser *_parser;

	// Internal methods (Part A responsibility)
	int createSocket(void);
	int bindSocket(void);
	int listenSocket(void);
	int poll_events(void);
	int handleClientData(Client *client);
	int handleClientWrite(Client *client);
};

#endif
