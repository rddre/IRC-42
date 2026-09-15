#include "../commands/CommandHandler.hpp"
#include "../client/Client.hpp"
#include "../channel/Channel.hpp"
#include "../server/Server.hpp"
#include "../replies/Replies.hpp"

/**
 * @brief Commande TOPIC - Voir ou changer le sujet du canal
 * 
 * Syntaxe: TOPIC <channel> [:<topic>]
 * 
 * Description:
 * - Affiche ou change le sujet du canal
 * - Si le mode du canal a +t (topic-restricted), seuls les opérateurs peuvent le changer
 * - Si pas de nouveau sujet fourni, affiche le sujet actuel
 * - Si une chaîne vide est fournie, supprime le sujet
 */
int CommandHandler::cmd_topic(Client *client, const Parser::Command &cmd)
{
	if (cmd.params.empty())
	{
		// ERR_NEEDMOREPARAMS
		return -1;
	}

	if (client == NULL)
		return -1;

	// TODO: Implement TOPIC command
	// 1. Valider le paramètre du canal
	// 2. Vérifier que le canal existe
	// 3. Vérifier que le client est dans le canal
	// 4. Si un nouveau sujet est fourni:
	//    - Si le mode +t est activé, vérifier que l'utilisateur est opérateur
	//    - Changer le sujet
	//    - Notifier tous les utilisateurs du canal du changement
	// 5. Si pas de sujet fourni, afficher le sujet actuel (ou RPL_NOTOPIC)

	return 0;
}
