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

int CommandHandler::cmd_pass(Client *client, const Parser::Command &cmd)
{
	(void)client;
	(void)cmd;
	if (cmd.params.empty())
		return -1;
	// TODO: Valider le mot de passe
	return 0;
}

int CommandHandler::cmd_nick(Client *client, const Parser::Command &cmd)
{
	(void)client;
	(void)cmd;
	if (cmd.params.empty())
		return -1;
	// TODO: Changer de nickname
	return 0;
}

int CommandHandler::cmd_user(Client *client, const Parser::Command &cmd)
{
	(void)client;
	(void)cmd;
	if (cmd.params.size() < 4)
		return -1;
	// TODO: Enregistrer les données utilisateur
	return 0;
}

int CommandHandler::cmd_quit(Client *client, const Parser::Command &cmd)
{
	(void)client;
	(void)cmd;
	// TODO: Déconnecter le client
	return 0;
}

int CommandHandler::cmd_join(Client *client, const Parser::Command &cmd)
{
	(void)client;
	(void)cmd;
	if (cmd.params.empty())
		return -1;
	// TODO: Joindre un canal
	return 0;
}

int CommandHandler::cmd_part(Client *client, const Parser::Command &cmd)
{
	(void)client;
	(void)cmd;
	if (cmd.params.empty())
		return -1;
	// TODO: Quitter un canal
	return 0;
}

int CommandHandler::cmd_privmsg(Client *client, const Parser::Command &cmd)
{
	(void)client;
	(void)cmd;
	if (cmd.params.size() < 2)
		return -1;
	// TODO: Envoyer un message privé
	return 0;
}

int CommandHandler::cmd_notice(Client *client, const Parser::Command &cmd)
{
	(void)client;
	(void)cmd;
	if (cmd.params.size() < 2)
		return -1;
	// TODO: Envoyer une notice
	return 0;
}

int CommandHandler::cmd_kick(Client *client, const Parser::Command &cmd)
{
	(void)client;
	(void)cmd;
	if (cmd.params.size() < 2)
		return -1;
	// TODO: Expulser un client du canal
	return 0;
}

int CommandHandler::cmd_invite(Client *client, const Parser::Command &cmd)
{
	(void)client;
	(void)cmd;
	if (cmd.params.size() < 2)
		return -1;
	// TODO: Inviter un client à un canal
	return 0;
}

int CommandHandler::cmd_topic(Client *client, const Parser::Command &cmd)
{
	(void)client;
	(void)cmd;
	if (cmd.params.empty())
		return -1;
	// TODO: Changer ou afficher le sujet du canal
	return 0;
}

int CommandHandler::cmd_mode(Client *client, const Parser::Command &cmd)
{
	(void)client;
	(void)cmd;
	if (cmd.params.size() < 2)
		return -1;
	// TODO: Changer les modes du canal ou de l'utilisateur
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
	(void)client;
	// TODO: Vérifier si le client est authentifié
	return true;
}

bool CommandHandler::isClientInChannel(Client *client, Channel *channel) const
{
	return channel != NULL && channel->containsClient(client);
}

bool CommandHandler::isClientOperatorInChannel(Client *client, Channel *channel) const
{
	return channel != NULL && channel->isOperator(client);
}
