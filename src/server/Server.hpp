#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>

class Server
{
	private:
	    std::string _port;
	    std::string _password;

	public:
	    Server(std::string port, std::string password);
	    ~Server();

	    void run();
};

#endif