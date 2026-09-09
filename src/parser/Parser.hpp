#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

// Le Parser sert a decomposer une ligne IRC recu du reseau en pieces plus simples.
// Par exemple : "JOIN #general" devient ["JOIN", "#general"].
class Parser
{
	public:
		Parser();
		~Parser();

		std::vector<std::string> parse(const std::string& line) const;
};

#endif