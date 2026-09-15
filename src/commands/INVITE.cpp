#include "../commands/CommandHandler.hpp"
#include "../client/Client.hpp"
#include "../channel/Channel.hpp"
#include "../server/Server.hpp"
#include "../replies/Replies.hpp"

/**
 * @brief Commande INVITE - Inviter un utilisateur à un canal
 * 
 * Syntaxe: INVITE <nickname> <channel>
 * 
 * Description:
 * - Invite un utilisateur à joindre un canal
 * - Si le canal est en mode invite-only (+i), seuls les opérateurs peuvent inviter
 * - L'utilisateur invité reçoit une notification INVITE
 * - Si le canal n'est pas en invite-only et l'utilisateur peut rejoindre, il n'est pas obligatoire
 */
int CommandHandler::cmd_invite(Client *client, const Parser::Command &cmd)
{
	if (cmd.params.size() < 2)
	{
		// ERR_NEEDMOREPARAMS
		return -1;
	}

	if (client == NULL)
		return -1;

	// TODO: Implement INVITE command
	// 1. Valider les paramètres (utilisateur et canal)
	// 2. Vérifier que le canal existe
	// 3. Vérifier que le client est dans le canal
	// 4. Si le canal est en mode invite-only, vérifier que l'utilisateur est opérateur
	// 5. Envoyer la notification d'invitation à l'utilisateur cible
	// 6. Notifier le client de la réussite

	return 0;
}
