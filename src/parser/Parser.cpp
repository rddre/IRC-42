#include "parser/Parser.hpp"

Parser::Parser()
{
}

Parser::~Parser()
{
}

std::vector<std::string> Parser::parse(const std::string& line) const
{
	std::vector<std::string> tokens;
	std::string current;
	std::string::size_type i = 0;

	while (i < line.size())
	{
		if (line[i] == ' ' || line[i] == '\t')
		{
			if (!current.empty())
			{
				tokens.push_back(current);
				current.clear();
			}
		}
		else
			current += line[i];
		i++;
	}
	if (!current.empty())
		tokens.push_back(current);
	return (tokens);
}
