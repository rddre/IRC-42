#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

class Client;

/**
 * @class Channel
 * @brief Représente un canal IRC et ses règles de validation.
 *
 * Cette classe centralise tout ce qui concerne la vie d'un salon :
 * les clients présents, l'opérateur du canal, le topic, les modes,
 * la limite d'utilisateurs et la clé du salon. Elle contient aussi les
 * vérifications utiles pour les commandes IRC comme JOIN, KICK, TOPIC,
 * MODE ou INVITE.
 */
class Channel
{
public:
	/**
	 * @struct ChannelMode
	 * @brief Structure représentant les modes du canal
	 */
	struct ChannelMode
	{
		bool invite_only;		// Mode 'i'
		bool topic_restricted;	// Mode 't'
		bool key_set;			// Mode 'k'
		std::string key;
		bool user_limit;		// Mode 'l'
		int max_users;

		ChannelMode(void)
			: invite_only(false), topic_restricted(false), 
			  key_set(false), user_limit(false), max_users(0)
		{}
	};

	Channel(const std::string &name);
	~Channel(void);

	// Getters
	std::string getName(void) const;
	std::string getTopic(void) const;
	ChannelMode getMode(void) const;
	std::vector<Client *> getClients(void) const;
	std::vector<Client *> getOperators(void) const;
	int getClientCount(void) const;
	bool isOperator(Client *client) const;
	bool containsClient(Client *client) const;

	// Vérifications IRC : ces méthodes servent à valider les accès aux canaux.
	// Elles sont utilisées par JOIN, KICK, MODE, TOPIC et INVITE.

	// Setters
	void setTopic(const std::string &topic);
	void setMode(const ChannelMode &mode);
	void setTopicRestricted(bool restricted);
	void setInviteOnly(bool invite);
	void setUserLimit(int limit);
	void setKey(const std::string &key);

	// Gestion des clients
	void addClient(Client *client);
	void removeClient(Client *client);
	void addUser(Client *client);
	void removeUser(Client *client);
	void addOperator(Client *client);
	void removeOperator(Client *client);
	void promoteToOperator(Client *client);
	void demoteOperator(Client *client);
	void setOperator(Client *client);
	void removeMode(const std::string &mode);

	// Utilitaires
	bool isClientOperator(Client *client) const;
	bool isFull(void) const;
	bool isKeyProtected(void) const;
	bool validateKey(const std::string &key) const;
	bool isInviteOnly(void) const;
	bool isTopicRestricted(void) const;

	// Broadcasting
	void broadcastMessage(const std::string &message, Client *exclude = NULL);

private:
	std::string _name;
	std::string _topic;
	ChannelMode _mode;
	std::vector<Client *> _clients;
	std::set<Client *> _operators;
};

#endif
