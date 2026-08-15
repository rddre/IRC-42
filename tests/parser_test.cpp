#include <iostream>
#include <cassert>
#include <vector>
#include "../src/parser/Parser.hpp"

/**
 * @brief Tests unitaires pour la classe Parser
 * 
 * Ce fichier teste les fonctionnalités principales du Parser IRC:
 * - Parsing de commandes simples
 * - Parsing avec paramètres
 * - Parsing avec trailing (messages avec espaces)
 * - Handling de buffers multiples
 */

void test_parser_simple_command()
{
	std::cout << "Testing simple command parsing..." << std::endl;
	
	Parser parser;
	Parser::Command cmd = parser.parseMessage("NICK test");
	
	assert(cmd.name == "NICK");
	assert(cmd.params.size() == 1);
	assert(cmd.params[0] == "test");
	assert(cmd.prefix.empty());
	assert(cmd.trailing.empty());
	
	std::cout << "✓ Simple command test passed" << std::endl;
}

void test_parser_with_params()
{
	std::cout << "Testing command with multiple parameters..." << std::endl;
	
	Parser parser;
	Parser::Command cmd = parser.parseMessage("USER test 0 * :Test User");
	
	assert(cmd.name == "USER");
	assert(cmd.params.size() == 3);
	assert(cmd.params[0] == "test");
	assert(cmd.params[1] == "0");
	assert(cmd.params[2] == "*");
	assert(cmd.trailing == "Test User");
	
	std::cout << "✓ Command with parameters test passed" << std::endl;
}

void test_parser_with_prefix()
{
	std::cout << "Testing command with prefix..." << std::endl;
	
	Parser parser;
	Parser::Command cmd = parser.parseMessage(":server.com 001 nick :Welcome");
	
	assert(cmd.prefix == "server.com");
	assert(cmd.name == "001");
	assert(cmd.params.size() == 1);
	assert(cmd.params[0] == "nick");
	assert(cmd.trailing == "Welcome");
	
	std::cout << "✓ Prefix test passed" << std::endl;
}

void test_parser_buffer()
{
	std::cout << "Testing buffer parsing with multiple commands..." << std::endl;
	
	Parser parser;
	std::string buffer = "NICK test\r\nUSER test 0 * :Test\r\n";
	
	std::vector<Parser::Command> cmds = parser.parseBuffer(buffer);
	
	assert(cmds.size() == 2);
	assert(cmds[0].name == "NICK");
	assert(cmds[1].name == "USER");
	assert(parser.getIncompleteCommand().empty());
	
	std::cout << "✓ Buffer parsing test passed" << std::endl;
}

void test_parser_incomplete_buffer()
{
	std::cout << "Testing incomplete buffer handling..." << std::endl;
	
	Parser parser;
	std::string buffer = "NICK test\r\nUSER test 0 * :Test";
	
	std::vector<Parser::Command> cmds = parser.parseBuffer(buffer);
	
	assert(cmds.size() == 1);
	assert(cmds[0].name == "NICK");
	assert(!parser.getIncompleteCommand().empty());
	
	std::cout << "✓ Incomplete buffer test passed" << std::endl;
}

void test_parser_privmsg()
{
	std::cout << "Testing PRIVMSG command parsing..." << std::endl;
	
	Parser parser;
	Parser::Command cmd = parser.parseMessage("PRIVMSG #channel :Hello world");
	
	assert(cmd.name == "PRIVMSG");
	assert(cmd.params.size() == 1);
	assert(cmd.params[0] == "#channel");
	assert(cmd.trailing == "Hello world");
	
	std::cout << "✓ PRIVMSG test passed" << std::endl;
}

int main(void)
{
	std::cout << "========== PARSER UNIT TESTS ==========" << std::endl;
	
	try
	{
		test_parser_simple_command();
		test_parser_with_params();
		test_parser_with_prefix();
		test_parser_buffer();
		test_parser_incomplete_buffer();
		test_parser_privmsg();
		
		std::cout << std::endl << "========== ALL TESTS PASSED ==========" << std::endl;
		return 0;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Test failed with exception: " << e.what() << std::endl;
		return 1;
	}
}
