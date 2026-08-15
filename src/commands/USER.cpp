#include "../commands/CommandHandler.hpp"
#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../replies/Replies.hpp"

/**
 * @brief Commande USER - Enregistrer le nom d'utilisateur et les informations réelles
 * 
 * Syntaxe: USER <user> <mode> <unused> <realname>
 * 
 * Description:
 * - Envoie les informations utilisateur au serveur
 * - Cette commande doit être envoyée après NICK
 * - Elle enregistre le nom d'utilisateur, le mode et le nom réel
 * - <mode> est généralement 0 ou 8
 */
int CommandHandler::cmd_user(Client *client, const Parser::Command &cmd)
{
	if (cmd.params.size() < 4)
	{
		// ERR_NEEDMOREPARAMS
		return -1;
	}

	if (client == NULL)
		return -1;

	// TODO: Implement USER command
	// 1. Valider les paramètres
	// 2. Enregistrer les données utilisateur (username, realname)
	// 3. Si NICK a déjà été envoyé, envoyer RPL_WELCOME
	// 4. Marquer le client comme enregistré

	return 0;
}
