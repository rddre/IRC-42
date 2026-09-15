#ifndef REPLIES_HPP
#define REPLIES_HPP

#include <string>

class Client;
class Channel;

/**
 * @class Replies
 * @brief Centralise les messages et codes IRC envoyés au client.
 *
 * Cette classe ne dépend pas du réseau brut : elle ne fait que produire le
 * texte de réponse IRC, ce qui permet de tester la logique métier sans avoir
 * à démarrer un vrai socket. La couche réseau A se chargera ensuite de
 * convertir ces réponses en send().
 */
class Replies
{
public:
	Replies(void);
	~Replies(void);

	static void sendWelcome(Client *client);
	static void sendChannelJoin(Client *client, Channel *channel);
	static void sendPrivateMessage(Client *sender, Client *target, const std::string &message);
	static void sendChannelMessage(Client *sender, Channel *channel, const std::string &message);
	static void sendError(Client *client, const std::string &code, const std::string &message);
	static void sendNumeric(Client *client, const std::string &code, const std::string &message);
};

#endif
