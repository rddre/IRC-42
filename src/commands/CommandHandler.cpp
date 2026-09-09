#include "commands/CommandHandler.hpp"
#include <iostream>

CommandHandler::CommandHandler()
{
}

CommandHandler::~CommandHandler()
{
}

void CommandHandler::execute(const std::string& line)
{
	std::cout << "CommandHandler: executing -> " << line << std::endl;
}
