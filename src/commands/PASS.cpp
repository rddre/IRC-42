#include "../commands/CommandHandler.hpp"
#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../replies/Replies.hpp"

/**
 * @brief Commande PASS - Envoyer un mot de passe
 * 
 * Syntaxe: PASS <password>
 * 
 * Description:
 * - PASS est utilisée pour définir le mot de passe du serveur
 * - Elle doit être envoyée avant les commandes NICK et USER
 * - L'échec du mot de passe termine la connexion
 */
int CommandHandler::cmd_pass(Client *client, const Parser::Command &cmd)
{
	if (cmd.params.empty())
	{
		// ERR_NEEDMOREPARAMS
		return -1;
	}

	if (client == NULL)
		return -1;

	// TODO: Implement PASS command
	// 1. Vérifier que c'est avant NICK/USER
	// 2. Valider le mot de passe avec le serveur
	// 3. Marquer le client comme ayant envoyé le bon password
	// 4. Si le password est invalide, envoyer ERR_PASSWDMISMATCH et fermer la connexion

	return 0;
}
