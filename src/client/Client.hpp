#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>
#include <vector>

class Channel;

/**
 * @class Client
 * @brief Représente un client IRC connecté au serveur
 * 
 * Cette classe gère les informations du client, son état de connexion,
 * et ses canaux.
 */
class Client
{
public:
	Client(int fd);
	~Client(void);

	// Getters
	int getFd(void) const;
	std::string getNickname(void) const;
	std::string getUsername(void) const;
	std::string getRealname(void) const;
	std::string getHostname(void) const;
	
	bool isAuthenticated(void) const;
	bool isPasswordValid(void) const;
	bool isNicknameSet(void) const;
	bool isUserRegistered(void) const;

	std::vector<Channel *> getChannels(void) const;

	// Setters
	void setNickname(const std::string &nickname);
	void setUsername(const std::string &username);
	void setRealname(const std::string &realname);
	void setHostname(const std::string &hostname);
	void setPasswordValid(bool valid);
	void setAuthenticated(bool auth);

	// Channel management
	void addChannel(Channel *channel);
	void removeChannel(Channel *channel);
	bool isInChannel(Channel *channel) const;

	// I/O buffer management
	void appendToRecvBuffer(const std::string &data);
	std::string getRecvBuffer(void) const;
	void clearRecvBuffer(void);
	
	void appendToSendBuffer(const std::string &data);
	std::string getSendBuffer(void) const;
	void clearSendBuffer(void);

private:
	int _fd;
	std::string _nickname;
	std::string _username;
	std::string _realname;
	std::string _hostname;
	
	bool _passwordValid;
	bool _authenticated;
	
	std::vector<Channel *> _channels;
	
	std::string _recvBuffer;
	std::string _sendBuffer;
};

#endif
