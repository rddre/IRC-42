#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include <string>

// Le CommandHandler prend une commande IRC parsee et l'execule.
// C'est ici qu'on appellera les fonctions de traitement, par exemple JOIN, NICK,
// USER, PRIVMSG, etc.
class CommandHandler
{
	public:
		CommandHandler();
		~CommandHandler();

		void execute(const std::string& line);
};

#endif