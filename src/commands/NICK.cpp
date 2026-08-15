#include "../commands/CommandHandler.hpp"
#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../replies/Replies.hpp"

/**
 * @brief Commande NICK - Changer le nickname
 * 
 * Syntaxe: NICK <nickname>
 * 
 * Description:
 * - Envoie ou change le NICKNAME du client
 * - Doit être le premier message envoyé après la connexion
 * - Les changements de NICKNAME peuvent être envoyés ultérieurement
 * - Les nicknames doivent être uniques sur le serveur
 */
int CommandHandler::cmd_nick(Client *client, const Parser::Command &cmd)
{
	if (cmd.params.empty())
	{
		// ERR_NONICKNAMEGIVEN
		return -1;
	}

	if (client == NULL)
		return -1;

	// TODO: Implement NICK command
	// 1. Valider le format du nickname
	// 2. Vérifier que le nickname n'est pas déjà utilisé
	// 3. Si changement, notifier tous les canaux du client
	// 4. Mettre à jour le nickname du client

	return 0;
}
