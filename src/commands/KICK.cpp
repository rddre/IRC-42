#include "../commands/CommandHandler.hpp"
#include "../client/Client.hpp"
#include "../channel/Channel.hpp"
#include "../server/Server.hpp"
#include "../replies/Replies.hpp"

/**
 * @brief Commande KICK - Expulser un utilisateur du canal
 * 
 * Syntaxe: KICK <channel> <user> [<comment>]
 * 
 * Description:
 * - Expulse un utilisateur d'un canal
 * - Seuls les opérateurs de canal ou l'opérateur du serveur peuvent l'utiliser
 * - Un commentaire facultatif peut être fourni
 * - L'utilisateur expulsé reçoit une notification KICK
 */
int CommandHandler::cmd_kick(Client *client, const Parser::Command &cmd)
{
	if (cmd.params.size() < 2)
	{
		// ERR_NEEDMOREPARAMS
		return -1;
	}

	if (client == NULL)
		return -1;

	// TODO: Implement KICK command
	// 1. Valider les paramètres
	// 2. Vérifier que le client est un opérateur du canal
	// 3. Vérifier que l'utilisateur à expulser existe et est dans le canal
	// 4. Expulser l'utilisateur du canal
	// 5. Notifier tous les utilisateurs du canal de l'expulsion

	return 0;
}
