#include "../commands/CommandHandler.hpp"
#include "../client/Client.hpp"
#include "../channel/Channel.hpp"
#include "../server/Server.hpp"
#include "../replies/Replies.hpp"

/**
 * @brief Commande JOIN - Joindre un ou plusieurs canaux
 * 
 * Syntaxe: JOIN <channels> [<keys>]
 * 
 * Description:
 * - Ajoute le client spécifié au canal fourni
 * - Les canaux multiples sont séparés par des virgules
 * - Les clés multiples sont délimitées par des virgules
 * - Affiche la liste des utilisateurs du canal et le sujet
 */
int CommandHandler::cmd_join(Client *client, const Parser::Command &cmd)
{
	if (cmd.params.empty())
	{
		// ERR_NEEDMOREPARAMS
		return -1;
	}

	if (client == NULL)
		return -1;

	// TODO: Implement JOIN command
	// 1. Valider les paramètres
	// 2. Vérifier les canaux demandés (créer s'ils n'existent pas)
	// 3. Vérifier les droits d'accès (clé, invite-only, limite d'utilisateurs)
	// 4. Ajouter le client au canal
	// 5. Envoyer la liste des utilisateurs et le sujet du canal
	// 6. Notifier tous les utilisateurs du canal que le client a rejoint

	return 0;
}
