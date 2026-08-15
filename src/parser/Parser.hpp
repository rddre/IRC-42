#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

/**
 * @class Parser
 * @brief Classe pour parser les messages IRC
 * 
 * Cette classe est responsable de traiter et analyser les messages
 * reçus du client selon le protocole IRC.
 */
class Parser
{
public:
	/**
	 * @struct Command
	 * @brief Structure représentant une commande parsée
	 */
	struct Command
	{
		std::string prefix;
		std::string name;
		std::vector<std::string> params;
		std::string trailing;
	};

	Parser(void);
	~Parser(void);

	/**
	 * @brief Parse un message IRC brut
	 * @param message Le message à parser
	 * @return Command struct avec les informations parsées
	 */
	Command parseMessage(const std::string &message);

	/**
	 * @brief Parser un buffer potentiellement partagé (plusieurs commandes)
	 * @param buffer Le buffer contenant les données reçues
	 * @return Un vecteur de Command parsées
	 */
	std::vector<Command> parseBuffer(const std::string &buffer);

	/**
	 * @brief Récupère les commandes partielles non-complètes
	 * @return Un vecteur de strings des commandes incomplètes
	 */
	std::string getIncompleteCommand(void) const;

	/**
	 * @brief Vide le cache des commandes incomplètes
	 */
	void clearIncomplete(void);

private:
	std::string _incompleteBuffer;

	/**
	 * @brief Trim les espaces au début et fin d'une string
	 * @param str La string à trimmer
	 * @return La string trimée
	 */
	std::string trim(const std::string &str);

	/**
	 * @brief Split une string par un délimiteur
	 * @param str La string à splitter
	 * @param delimiter Le délimiteur
	 * @return Un vecteur de strings
	 */
	std::vector<std::string> split(const std::string &str, char delimiter);
};

#endif
