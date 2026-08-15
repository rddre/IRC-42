#include "Server.hpp"
#include "../client/Client.hpp"
#include "../channel/Channel.hpp"
#include "../commands/CommandHandler.hpp"
#include "../parser/Parser.hpp"

Server::Server(int port, const std::string &password)
	: _port(port), _password(password), _serverSocket(-1), _running(false)
{
	_commandHandler = new CommandHandler(this);
	_parser = new Parser();
}

Server::~Server(void)
{
	if (_commandHandler != NULL)
		delete _commandHandler;
	if (_parser != NULL)
		delete _parser;
	
	for (size_t i = 0; i < _clients.size(); ++i)
		delete _clients[i];
	
	for (size_t i = 0; i < _channels.size(); ++i)
		delete _channels[i];
}

int Server::getPort(void) const
{
	return _port;
}

std::string Server::getPassword(void) const
{
	return _password;
}

std::vector<Client *> Server::getClients(void) const
{
	return _clients;
}

std::vector<Channel *> Server::getChannels(void) const
{
	return _channels;
}

Client *Server::getClientByNickname(const std::string &nickname) const
{
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i]->getNickname() == nickname)
			return _clients[i];
	}
	return NULL;
}

Channel *Server::getChannelByName(const std::string &name) const
{
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i]->getName() == name)
			return _channels[i];
	}
	return NULL;
}

int Server::start(void)
{
	_running = true;
	// TODO: Part A - Implement socket creation
	return 0;
}

int Server::run(void)
{
	// TODO: Part A - Implement main server loop
	return 0;
}

void Server::stop(void)
{
	_running = false;
}

void Server::addClient(Client *client)
{
	if (client != NULL)
		_clients.push_back(client);
}

void Server::removeClient(Client *client)
{
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i] == client)
		{
			_clients.erase(_clients.begin() + i);
			delete client;
			return;
		}
	}
}

Client *Server::acceptNewClient(void)
{
	// TODO: Part A - Accept new connection
	return NULL;
}

Channel *Server::createChannel(const std::string &name)
{
	Channel *channel = getChannelByName(name);
	if (channel == NULL)
	{
		channel = new Channel(name);
		_channels.push_back(channel);
	}
	return channel;
}

void Server::removeChannel(Channel *channel)
{
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i] == channel)
		{
			_channels.erase(_channels.begin() + i);
			delete channel;
			return;
		}
	}
}

void Server::broadcastMessage(const std::string &message, Client *exclude)
{
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i] != exclude)
			sendToClient(_clients[i], message);
	}
}

void Server::sendToClient(Client *client, const std::string &message)
{
	if (client != NULL)
		client->appendToSendBuffer(message);
}

CommandHandler *Server::getCommandHandler(void) const
{
	return _commandHandler;
}

Parser *Server::getParser(void) const
{
	return _parser;
}
