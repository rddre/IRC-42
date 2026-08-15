#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "../parser/Parser.hpp"

class Client;
class Channel;
class Server;

/**
 * @class CommandHandler
 * @brief Classe responsable de l'exécution des commandes IRC
 * 
 * Elle traite toutes les commandes reçues et coordonne leur exécution.
 */
class CommandHandler
{
public:
	typedef int (CommandHandler::*CommandFunc)(Client *, const Parser::Command &);

	CommandHandler(Server *server);
	~CommandHandler(void);

	/**
	 * @brief Exécute une commande parsée
	 * @param client Le client qui a envoyé la commande
	 * @param cmd La commande à exécuter
	 * @return Code de retour (0 si succès)
	 */
	int executeCommand(Client *client, const Parser::Command &cmd);

	/**
	 * @brief Enregistre une commande avec sa fonction handler
	 * @param name Nom de la commande (ex: "PRIVMSG")
	 * @param func Pointeur vers la fonction handler
	 */
	void registerCommand(const std::string &name, CommandFunc func);

private:
	Server *_server;
	std::map<std::string, CommandFunc> _commands;

	// Commandes IRC
	int cmd_pass(Client *client, const Parser::Command &cmd);
	int cmd_nick(Client *client, const Parser::Command &cmd);
	int cmd_user(Client *client, const Parser::Command &cmd);
	int cmd_quit(Client *client, const Parser::Command &cmd);
	int cmd_join(Client *client, const Parser::Command &cmd);
	int cmd_part(Client *client, const Parser::Command &cmd);
	int cmd_privmsg(Client *client, const Parser::Command &cmd);
	int cmd_notice(Client *client, const Parser::Command &cmd);
	int cmd_kick(Client *client, const Parser::Command &cmd);
	int cmd_invite(Client *client, const Parser::Command &cmd);
	int cmd_topic(Client *client, const Parser::Command &cmd);
	int cmd_mode(Client *client, const Parser::Command &cmd);
	int cmd_who(Client *client, const Parser::Command &cmd);
	int cmd_whois(Client *client, const Parser::Command &cmd);
	int cmd_list(Client *client, const Parser::Command &cmd);
	int cmd_names(Client *client, const Parser::Command &cmd);

	// Utilitaires de vérification
	bool isClientAuthenticated(Client *client) const;
	bool isClientInChannel(Client *client, Channel *channel) const;
	bool isClientOperatorInChannel(Client *client, Channel *channel) const;

	// Enregistrement des commandes
	void registerAllCommands(void);
};

#endif
