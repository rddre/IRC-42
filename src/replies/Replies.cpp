#include "Replies.hpp"
#include "../client/Client.hpp"
#include "../channel/Channel.hpp"
#include <iostream>

Replies::Replies(void)
{
}

Replies::~Replies(void)
{
}

void Replies::sendWelcome(Client *client)
{
	if (client == NULL)
		return ;
	std::cout << ":server 001 " << client->getNickname() << " :Welcome to the IRC server" << std::endl;
}

void Replies::sendChannelJoin(Client *client, Channel *channel)
{
	if (client == NULL || channel == NULL)
		return ;
	std::cout << ":server JOIN " << channel->getName() << " :" << client->getNickname() << std::endl;
}

void Replies::sendPrivateMessage(Client *sender, Client *target, const std::string &message)
{
	if (sender == NULL || target == NULL)
		return ;
	std::cout << sender->getNickname() << " -> " << target->getNickname() << " :" << message << std::endl;
}

void Replies::sendChannelMessage(Client *sender, Channel *channel, const std::string &message)
{
	if (sender == NULL || channel == NULL)
		return ;
	std::cout << sender->getNickname() << "@" << channel->getName() << " :" << message << std::endl;
}

void Replies::sendNumeric(Client *client, const std::string &code, const std::string &message)
{
	if (client == NULL)
		return ;
	std::cout << ":server " << code << " " << client->getNickname() << " " << message << std::endl;
}

void Replies::sendError(Client *client, const std::string &code, const std::string &message)
{
	sendNumeric(client, code, message);
}
