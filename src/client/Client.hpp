#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

// La classe Client represente un client IRC connecte au serveur.
// Elle garde l'etat d'un utilisateur : son socket, son pseudo, son nom
// d'utilisateur, le tampon de lecture et le fait qu'il soit inscrit ou non.
class Client
{
	private:
		int _fd;
		std::string _nickname;
		std::string _username;
		std::string _buffer;
		bool _isRegistered;

	public:
		Client();
		Client(int fd);
		Client(const Client& other);
		Client& operator=(const Client& other);
		~Client();

		int getFd() const;
		std::string getNickname() const;
		std::string getUsername() const;
		std::string getBuffer() const;
		bool isRegistered() const;

		void setFd(int fd);
		void setNickname(const std::string& nickname);
		void setUsername(const std::string& username);
		void setBuffer(const std::string& buffer);
		void appendBuffer(const std::string& data);
		void clearBuffer();
		void setRegistered(bool isRegistered);
};

#endif