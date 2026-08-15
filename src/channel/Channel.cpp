#include "Channel.hpp"
#include "../client/Client.hpp"

Channel::Channel(const std::string &name)
	: _name(name), _topic("")
{
}

Channel::~Channel(void)
{
}

std::string Channel::getName(void) const
{
	return _name;
}

std::string Channel::getTopic(void) const
{
	return _topic;
}

Channel::ChannelMode Channel::getMode(void) const
{
	return _mode;
}

std::vector<Client *> Channel::getClients(void) const
{
	return _clients;
}

std::vector<Client *> Channel::getOperators(void) const
{
	std::vector<Client *> ops;
	for (std::set<Client *>::iterator it = _operators.begin(); it != _operators.end(); ++it)
		ops.push_back(*it);
	return ops;
}

int Channel::getClientCount(void) const
{
	return _clients.size();
}

bool Channel::isOperator(Client *client) const
{
	return _operators.find(client) != _operators.end();
}

bool Channel::containsClient(Client *client) const
{
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i] == client)
			return true;
	}
	return false;
}

void Channel::setTopic(const std::string &topic)
{
	_topic = topic;
}

void Channel::setMode(const ChannelMode &mode)
{
	_mode = mode;
}

void Channel::setTopicRestricted(bool restricted)
{
	_mode.topic_restricted = restricted;
}

void Channel::setInviteOnly(bool invite)
{
	_mode.invite_only = invite;
}

void Channel::setUserLimit(int limit)
{
	_mode.user_limit = (limit > 0);
	_mode.max_users = limit;
}

void Channel::setKey(const std::string &key)
{
	if (key.empty())
	{
		_mode.key_set = false;
		_mode.key = "";
	}
	else
	{
		_mode.key_set = true;
		_mode.key = key;
	}
}

void Channel::addClient(Client *client)
{
	if (!containsClient(client))
		_clients.push_back(client);
}

void Channel::removeClient(Client *client)
{
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i] == client)
		{
			_clients.erase(_clients.begin() + i);
			removeOperator(client);
			return;
		}
	}
}

void Channel::addOperator(Client *client)
{
	if (containsClient(client))
		_operators.insert(client);
}

void Channel::removeOperator(Client *client)
{
	_operators.erase(client);
}

void Channel::promoteToOperator(Client *client)
{
	if (containsClient(client) && !isOperator(client))
		_operators.insert(client);
}

void Channel::demoteOperator(Client *client)
{
	_operators.erase(client);
}

bool Channel::isClientOperator(Client *client) const
{
	return isOperator(client);
}

bool Channel::isFull(void) const
{
	return _mode.user_limit && _clients.size() >= static_cast<size_t>(_mode.max_users);
}

bool Channel::isKeyProtected(void) const
{
	return _mode.key_set;
}

bool Channel::validateKey(const std::string &key) const
{
	if (!_mode.key_set)
		return true;
	return _mode.key == key;
}

bool Channel::isInviteOnly(void) const
{
	return _mode.invite_only;
}

bool Channel::isTopicRestricted(void) const
{
	return _mode.topic_restricted;
}

void Channel::broadcastMessage(const std::string &message, Client *exclude)
{
	(void)message;
	(void)exclude;
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i] != exclude)
		{
			// TODO: Send message to client
		}
	}
}
