#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>

class Server
{
	private:
		int			_serverFd;
	    std::string _port;
	    std::string _password;

		void initSocket();
	
	public:
	    Server(std::string port, std::string password);
	    ~Server();

	    void run();
};

#endif