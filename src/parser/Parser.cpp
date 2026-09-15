#include "Parser.hpp"

Parser::Parser(void)
{
}

Parser::~Parser(void)
{
}

std::string Parser::trim(const std::string &str)
{
	size_t start = str.find_first_not_of(" \t\n\r\f\v");
	if (start == std::string::npos)
		return "";
	size_t end = str.find_last_not_of(" \t\n\r\f\v");
	return str.substr(start, end - start + 1);
}

std::vector<std::string> Parser::split(const std::string &str, char delimiter)
{
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string item;

	while (std::getline(ss, item, delimiter))
		result.push_back(item);
	return result;
}

Parser::Command Parser::parseMessage(const std::string &message)
{
	Command cmd;
	std::string msg = trim(message);
	size_t pos = 0;

	if (msg.empty())
		return cmd;

	// Parser le prefix si présent (commence par ':')
	if (msg[0] == ':')
	{
		pos = msg.find(' ');
		if (pos == std::string::npos)
		{
			cmd.prefix = msg.substr(1);
			return cmd;
		}
		cmd.prefix = msg.substr(1, pos - 1);
		msg = trim(msg.substr(pos));
		if (msg.empty())
			return cmd;
		pos = 0;
	}

	// Parser le nom de la commande
	pos = msg.find(' ');
	if (pos == std::string::npos)
	{
		cmd.name = msg;
		return cmd;
	}

	cmd.name = msg.substr(0, pos);
	std::string rest = trim(msg.substr(pos));

	// Parser les paramètres et le trailing
	pos = rest.find(" :");
	if (pos != std::string::npos)
	{
		std::string params_str = rest.substr(0, pos);
		cmd.trailing = rest.substr(pos + 2);

		// Parser les paramètres individuels
		std::vector<std::string> params = split(params_str, ' ');
		for (size_t i = 0; i < params.size(); ++i)
		{
			if (!params[i].empty())
				cmd.params.push_back(params[i]);
		}
	}
	else
	{
		std::vector<std::string> params = split(rest, ' ');
		for (size_t i = 0; i < params.size(); ++i)
		{
			if (!params[i].empty())
				cmd.params.push_back(params[i]);
		}
	}

	return cmd;
}

std::vector<Parser::Command> Parser::parseBuffer(const std::string &buffer)
{
	std::vector<Command> commands;
	std::string data = _incompleteBuffer + buffer;
	std::string delimiter = "\r\n";
	std::string::size_type pos = 0;
	std::string::size_type end = data.find(delimiter);

	if (end == std::string::npos && !data.empty())
	{
		end = data.find('\n');
		if (end != std::string::npos)
			delimiter = "\n";
	}

	while (end != std::string::npos)
	{
		std::string line = data.substr(pos, end - pos);
		if (!line.empty())
			commands.push_back(parseMessage(line));
		pos = end + delimiter.length();
		end = data.find(delimiter, pos);
	}

	// Garder le reste incomplet
	if (pos < data.length())
		_incompleteBuffer = data.substr(pos);
	else
		_incompleteBuffer.clear();

	return commands;
}

std::string Parser::getIncompleteCommand(void) const
{
	return _incompleteBuffer;
}

void Parser::clearIncomplete(void)
{
	_incompleteBuffer.clear();
}
