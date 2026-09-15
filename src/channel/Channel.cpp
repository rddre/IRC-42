#include "Channel.hpp"
#include "../client/Client.hpp"

/**
 * Constructeur du canal.
 *
 * Un canal est identifié par son nom. Les règles de validation et les
 * clients associés seront ajoutés plus tard selon les commandes IRC.
 */
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

/**
 * Vérifie si un client est opérateur du canal.
 *
 * Les commandes sensibles comme KICK, MODE, TOPIC ou INVITE doivent
 * vérifier cette règle avant d'autoriser l'action.
 */
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

/**
 * Ajoute un client au canal.
 *
 * Cette méthode est la base de la logique de JOIN. Elle empêche les doublons
 * et garde la liste des membres cohérente.
 */
void Channel::addClient(Client *client)
{
	if (!containsClient(client))
		_clients.push_back(client);
}

void Channel::addUser(Client *client)
{
	addClient(client);
}

/**
 * Retire un client du canal.
 *
 * On le supprime aussi des opérateurs si nécessaire pour préserver l'état du
 * salon lors d'un KICK ou d'une déconnexion.
 */
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

void Channel::removeUser(Client *client)
{
	removeClient(client);
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

void Channel::setOperator(Client *client)
{
	promoteToOperator(client);
}

void Channel::removeMode(const std::string &mode)
{
	if (mode == "i")
		_mode.invite_only = false;
	else if (mode == "t")
		_mode.topic_restricted = false;
	else if (mode == "k")
		setKey("");
	else if (mode == "l")
	{
		_mode.user_limit = false;
		_mode.max_users = 0;
	}
}

bool Channel::isClientOperator(Client *client) const
{
	return isOperator(client);
}

/**
 * Vérifie si le canal a atteint sa limite d'utilisateurs.
 *
 * Cette validation est appelée avant le JOIN pour empêcher un client
 * d'entrer dans un salon déjà plein.
 */
bool Channel::isFull(void) const
{
	return _mode.user_limit && _clients.size() >= static_cast<size_t>(_mode.max_users);
}

/**
 * Vérifie si le canal est protégé par une clé.
 *
 * Si le canal a un mot de passe, le client doit fournir la bonne clé
 * pour pouvoir le rejoindre.
 */
bool Channel::isKeyProtected(void) const
{
	return _mode.key_set;
}

/**
 * Valide la clé fournie par le client pour la commande JOIN.
 *
 * Si le salon n'est pas protégé, toute clé est acceptée.
 */
bool Channel::validateKey(const std::string &key) const
{
	if (!_mode.key_set)
		return true;
	return _mode.key == key;
}

/**
 * Vérifie si le canal est en mode invit-only.
 *
 * Dans ce cas, un client ne peut pas rejoindre sans invitation ou sans
 * être opérateur du canal.
 */
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
