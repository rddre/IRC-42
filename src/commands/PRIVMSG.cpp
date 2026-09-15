#include "../commands/CommandHandler.hpp"
#include "../client/Client.hpp"
#include "../channel/Channel.hpp"
#include "../server/Server.hpp"
#include "../replies/Replies.hpp"

/**
 * @brief Commande PRIVMSG - Envoyer un message privé ou à un canal
 * 
 * Syntaxe: PRIVMSG <target> :<message>
 * 
 * Description:
 * - Envoie un message à un utilisateur spécifique ou à un canal
 * - Si la cible commence par '#', c'est un message de canal
 * - Sinon, c'est un message privé
 * - Le message est transmis à tous les utilisateurs de la cible
 */
int CommandHandler::cmd_privmsg(Client *client, const Parser::Command &cmd)
{
	if (cmd.params.size() < 2 || cmd.trailing.empty())
	{
		// ERR_NEEDMOREPARAMS ou ERR_NOTEXTTOSEND
		return -1;
	}

	if (client == NULL)
		return -1;

	// TODO: Implement PRIVMSG command
	// 1. Valider les paramètres
	// 2. Déterminer si la cible est un canal ou un utilisateur
	// 3. Si canal, vérifier que le client est dans le canal
	// 4. Envoyer le message à tous les utilisateurs de la cible
	// 5. Gérer les cas où la cible n'existe pas

	return 0;
}
