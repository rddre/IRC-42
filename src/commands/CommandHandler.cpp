#include "CommandHandler.hpp"
#include "../client/Client.hpp"
#include "../channel/Channel.hpp"
#include "../server/Server.hpp"

CommandHandler::CommandHandler(Server *server)
	: _server(server)
{
	registerAllCommands();
}

CommandHandler::~CommandHandler(void)
{
}

void CommandHandler::registerAllCommands(void)
{
	_commands["PASS"] = &CommandHandler::cmd_pass;
	_commands["NICK"] = &CommandHandler::cmd_nick;
	_commands["USER"] = &CommandHandler::cmd_user;
	_commands["QUIT"] = &CommandHandler::cmd_quit;
	_commands["JOIN"] = &CommandHandler::cmd_join;
	_commands["PART"] = &CommandHandler::cmd_part;
	_commands["PRIVMSG"] = &CommandHandler::cmd_privmsg;
	_commands["NOTICE"] = &CommandHandler::cmd_notice;
	_commands["KICK"] = &CommandHandler::cmd_kick;
	_commands["INVITE"] = &CommandHandler::cmd_invite;
	_commands["TOPIC"] = &CommandHandler::cmd_topic;
	_commands["MODE"] = &CommandHandler::cmd_mode;
	_commands["WHO"] = &CommandHandler::cmd_who;
	_commands["WHOIS"] = &CommandHandler::cmd_whois;
	_commands["LIST"] = &CommandHandler::cmd_list;
	_commands["NAMES"] = &CommandHandler::cmd_names;
}

void CommandHandler::registerCommand(const std::string &name, CommandFunc func)
{
	_commands[name] = func;
}

int CommandHandler::executeCommand(Client *client, const Parser::Command &cmd)
{
	if (client == NULL)
		return -1;

	std::map<std::string, CommandFunc>::iterator it = _commands.find(cmd.name);
	
	if (it != _commands.end())
		return (this->*it->second)(client, cmd);
	
	return -1; // Commande inconnue
}

// Implémentations des commandes
// TODO: Compléter ces implémentations

/**
 * Gestion du mot de passe du serveur.
 *
 * Le client ne peut pas se connecter si le mot de passe ne correspond pas
 * à celui du serveur. Cette vérification est une des premières étapes
 * de l'authentification IRC.
 */
int CommandHandler::cmd_pass(Client *client, const Parser::Command &cmd)
{
	if (client == NULL || _server == NULL || cmd.params.empty())
		return -1;
	if (client->isRegistered())
		return -1;
	if (cmd.params[0] != _server->getPassword())
		return -1;
	return 0;
}

/**
 * Gestion du pseudo du client.
 *
 * Un nickname doit être unique sur le serveur. S'il est déjà utilisé par
 * un autre client, la commande est refusée.
 */
int CommandHandler::cmd_nick(Client *client, const Parser::Command &cmd)
{
	std::map<int, Client>& clients = _server->getClients();
	std::map<int, Client>::iterator it;

	if (client == NULL || _server == NULL || cmd.params.empty())
		return -1;
	for (it = clients.begin(); it != clients.end(); ++it)
	{
		if (&it->second != client && it->second.getNickname() == cmd.params[0])
			return -1;
	}
	client->setNickname(cmd.params[0]);
	if (!client->getUsername().empty() && !client->getNickname().empty())
		client->setRegistered(true);
	return 0;
}

/**
 * Enregistrement du nom d'utilisateur.
 *
 * Cette commande complète l'authentification avec le pseudo et le
 * username du client.
 */
int CommandHandler::cmd_user(Client *client, const Parser::Command &cmd)
{
	if (client == NULL || _server == NULL || cmd.params.size() < 4)
		return -1;
	client->setUsername(cmd.params[0]);
	if (!client->getUsername().empty() && !client->getNickname().empty())
		client->setRegistered(true);
	return 0;
}

int CommandHandler::cmd_quit(Client *client, const Parser::Command &cmd)
{
	(void)cmd;
	if (client == NULL)
		return -1;
	return 0;
}

/**
 * Join d'un client dans un canal.
 *
 * Avant d'ajouter le client, on vérifie :
 * - canal plein
 * - mot de passe du canal
 * - mode invite-only
 * - permissions d'opérateur si le canal existe déjà
 *
 * Le premier client à rejoindre un canal devient opérateur du salon.
 */
int CommandHandler::cmd_join(Client *client, const Parser::Command &cmd)
{
	Channel *channel;

	if (client == NULL || _server == NULL || cmd.params.empty())
		return -1;
	channel = _server->getChannel(cmd.params[0]);
	if (channel == NULL)
		channel = _server->createChannel(cmd.params[0]);
	if (channel->isFull())
		return -1;
	if (channel->isKeyProtected())
	{
		if (cmd.params.size() < 2 || !channel->validateKey(cmd.params[1]))
			return -1;
	}
	if (channel->isInviteOnly() && channel->getClientCount() > 0 && !channel->isOperator(client))
		return -1;
	channel->addClient(client);
	if (channel->getClientCount() == 1)
		channel->addOperator(client);
	return 0;
}

int CommandHandler::cmd_part(Client *client, const Parser::Command &cmd)
{
	Channel *channel;

	if (client == NULL || _server == NULL || cmd.params.empty())
		return -1;
	channel = _server->getChannel(cmd.params[0]);
	if (channel == NULL)
		return -1;
	channel->removeClient(client);
	return 0;
}

int CommandHandler::cmd_privmsg(Client *client, const Parser::Command &cmd)
{
	Channel *channel;
	std::map<int, Client>& clients = _server->getClients();
	std::map<int, Client>::iterator it;

	if (client == NULL || _server == NULL || cmd.params.size() < 2)
		return -1;
	if (cmd.params[0][0] == '#')
	{
		channel = _server->getChannel(cmd.params[0]);
		if (channel == NULL || !channel->containsClient(client))
			return -1;
		std::cout << "[cmd_privmsg] channel message to " << cmd.params[0] << " trailing='" << cmd.trailing << "'\n";
		// Envoi du message de canal a tous les membres (sauf l'expediteur)
		for (size_t i = 0; i < channel->getClients().size(); ++i)
		{
			Client *member = channel->getClients()[i];
			if (member == NULL)
				continue;
			std::cout << "[cmd_privmsg] member fd=" << member->getFd() << " nick='" << member->getNickname() << "'\n";
			if (member == client)
				continue;
			// Format IRC: :nick PRIVMSG #channel :message\r\n
			std::string msg = ":" + client->getNickname() + " PRIVMSG " + channel->getName() + " :" + cmd.trailing + "\r\n";
			_server->sendToClient(member->getFd(), msg);
		}
		return 0;
	}
	for (it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second.getNickname() == cmd.params[0])
		{
			// Envoi d'un message prive au destinataire
			std::string msg = ":" + client->getNickname() + " PRIVMSG " + it->second.getNickname() + " :" + cmd.trailing + "\r\n";
			_server->sendToClient(it->second.getFd(), msg);
			return 0;
		}
	}
	return -1;
}

int CommandHandler::cmd_notice(Client *client, const Parser::Command &cmd)
{
	if (client == NULL || cmd.params.size() < 2)
		return -1;
	return 0;
}

/**
 * Expulsion d'un client du canal.
 *
 * Seul un opérateur du canal a le droit de kicker un autre membre.
 * Cette vérification protège les permissions du salon.
 */
int CommandHandler::cmd_kick(Client *client, const Parser::Command &cmd)
{
	Channel *channel;
	Client *target = NULL;
	std::map<int, Client>& clients = _server->getClients();
	std::map<int, Client>::iterator it;

	if (client == NULL || _server == NULL || cmd.params.size() < 2)
		return -1;
	channel = _server->getChannel(cmd.params[0]);
	if (channel == NULL || !channel->containsClient(client) || !channel->isOperator(client))
		return -1;
	for (it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second.getNickname() == cmd.params[1])
		{
			target = &it->second;
			break;
		}
	}
	if (target == NULL || !channel->containsClient(target))
		return -1;
	channel->removeClient(target);
	return 0;
}

/**
 * Invitation d'un client vers un canal.
 *
 * L'invitation est une vérification de permissions et d'accès :
 * le client doit être dans le canal et les droits d'opérateur doivent
 * être vérifiés si le salon est en mode invite-only.
 */
int CommandHandler::cmd_invite(Client *client, const Parser::Command &cmd)
{
	Channel *channel;
	Client *target = NULL;
	std::map<int, Client>& clients = _server->getClients();
	std::map<int, Client>::iterator it;

	if (client == NULL || _server == NULL || cmd.params.size() < 2)
		return -1;
	channel = _server->getChannel(cmd.params[1]);
	if (channel == NULL || !channel->containsClient(client))
		return -1;
	if (channel->isInviteOnly() && !channel->isOperator(client))
		return -1;
	for (it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second.getNickname() == cmd.params[0])
		{
			target = &it->second;
			break;
		}
	}
	if (target == NULL)
		return -1;
	return 0;
}

/**
 * Gestion du sujet du canal.
 *
 * Le topic ne peut être changé que si le client a les permissions
 * nécessaires, surtout lorsque le canal est en mode topic-restricted.
 */
int CommandHandler::cmd_topic(Client *client, const Parser::Command &cmd)
{
	Channel *channel;

	if (client == NULL || _server == NULL || cmd.params.empty())
		return -1;
	channel = _server->getChannel(cmd.params[0]);
	if (channel == NULL || !channel->containsClient(client))
		return -1;
	if (cmd.params.size() > 1)
	{
		if (channel->isTopicRestricted() && !channel->isOperator(client))
			return -1;
		channel->setTopic(cmd.params[1]);
	}
	return 0;
}

/**
 * Gestion des modes du canal.
 *
 * Les changements de mode doivent être autorisés uniquement par un
 * opérateur du canal. Cela protège les règles de sécurité du salon.
 */
/**
 * Gestion des modes du canal.
 *
 * Les changements de mode doivent être autorisés uniquement par un
 * opérateur du canal. Cette logique protège les règles de sécurité du salon.
 * Les modes supportés ici sont : +i, -i, +t, -t, +k, -k, +o, -o, +l, -l.
 */
int CommandHandler::cmd_mode(Client *client, const Parser::Command &cmd)
{
	Channel *channel;
	Client *target = NULL;
	std::map<int, Client>& clients = _server->getClients();
	std::map<int, Client>::iterator it;

	if (client == NULL || _server == NULL || cmd.params.size() < 2)
		return -1;
	channel = _server->getChannel(cmd.params[0]);
	if (channel == NULL || !channel->containsClient(client) || !channel->isOperator(client))
		return -1;
	if (cmd.params[1] == "+i")
		channel->setInviteOnly(true);
	else if (cmd.params[1] == "-i")
		channel->setInviteOnly(false);
	else if (cmd.params[1] == "+t")
		channel->setTopicRestricted(true);
	else if (cmd.params[1] == "-t")
		channel->setTopicRestricted(false);
	else if (cmd.params.size() >= 3 && cmd.params[1] == "+k")
		channel->setKey(cmd.params[2]);
	else if (cmd.params.size() >= 3 && cmd.params[1] == "-k")
		channel->setKey("");
	else if (cmd.params.size() >= 3 && (cmd.params[1] == "+o" || cmd.params[1] == "-o"))
	{
		for (it = clients.begin(); it != clients.end(); ++it)
		{
			if (it->second.getNickname() == cmd.params[2])
			{
				target = &it->second;
				break;
			}
		}
		if (target == NULL || !channel->containsClient(target))
			return -1;
		if (cmd.params[1] == "+o")
			channel->promoteToOperator(target);
		else
			channel->demoteOperator(target);
	}
	else if (cmd.params.size() >= 3 && (cmd.params[1] == "+l" || cmd.params[1] == "-l"))
	{
		if (cmd.params[1] == "+l")
		{
			int limit = atoi(cmd.params[2].c_str());
			channel->setUserLimit(limit);
		}
		else
			channel->setUserLimit(0);
	}
	return 0;
}

int CommandHandler::cmd_who(Client *client, const Parser::Command &cmd)
{
	(void)client;
	(void)cmd;
	// TODO: Lister les utilisateurs
	return 0;
}

int CommandHandler::cmd_whois(Client *client, const Parser::Command &cmd)
{
	(void)client;
	(void)cmd;
	if (cmd.params.empty())
		return -1;
	// TODO: Afficher les informations d'un utilisateur
	return 0;
}

int CommandHandler::cmd_list(Client *client, const Parser::Command &cmd)
{
	(void)client;
	(void)cmd;
	// TODO: Lister tous les canaux
	return 0;
}

int CommandHandler::cmd_names(Client *client, const Parser::Command &cmd)
{
	(void)client;
	(void)cmd;
	// TODO: Lister les noms des utilisateurs du canal
	return 0;
}

bool CommandHandler::isClientAuthenticated(Client *client) const
{
	if (client == NULL)
		return false;
	return client->isRegistered();
}

bool CommandHandler::isClientInChannel(Client *client, Channel *channel) const
{
	return channel != NULL && channel->containsClient(client);
}

bool CommandHandler::isClientOperatorInChannel(Client *client, Channel *channel) const
{
	return channel != NULL && channel->isOperator(client);
}
