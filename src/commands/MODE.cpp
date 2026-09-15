#include "../commands/CommandHandler.hpp"
#include "../client/Client.hpp"
#include "../channel/Channel.hpp"
#include "../server/Server.hpp"
#include "../replies/Replies.hpp"

/**
 * @brief Commande MODE - Changer les modes de l'utilisateur ou du canal
 * 
 * Syntaxe: MODE <target> [<modestring> [<mode arguments>]]
 * 
 * Description:
 * - Change les modes du canal ou de l'utilisateur
 * - Les modes de canal implémentés:
 *   - i: Set/remove Invite-only channel
 *   - t: Set/remove restrictions of the TOPIC command to channel operators
 *   - k: Set/remove the channel key (password)
 *   - o: Give/take channel operator privilege
 *   - l: Set/remove the user limit to channel
 * 
 * - Les chaînes de mode commencent par '+' ou '-' suivi des codes de mode
 * - Les arguments (+/-) varient selon le mode
 */
int CommandHandler::cmd_mode(Client *client, const Parser::Command &cmd)
{
	if (cmd.params.size() < 2)
	{
		// ERR_NEEDMOREPARAMS
		return -1;
	}

	if (client == NULL)
		return -1;

	// TODO: Implement MODE command
	// 1. Valider les paramètres
	// 2. Déterminer si c'est un mode utilisateur ou un mode canal
	// 3. Pour les modes canal:
	//    - Vérifier que le client est dans le canal et est opérateur
	//    - Parser la chaîne de mode
	//    - Appliquer les changements (+i, +t, +k, +o, +l)
	//    - Notifier tous les utilisateurs du canal des changements
	// 4. Gérer les arguments supplémentaires selon le mode

	return 0;
}
