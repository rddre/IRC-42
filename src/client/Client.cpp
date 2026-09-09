#include "client/Client.hpp"

// Constructeur par defaut : on initialise un client vide, sans socket actif.
Client::Client() : _fd(-1), _nickname(""), _username(""), _buffer(""), _isRegistered(false)
{
}

// Constructeur avec un fd : on cree un client associe a un socket client.
Client::Client(int fd) : _fd(fd), _nickname(""), _username(""), _buffer(""), _isRegistered(false)
{
}

// Copie d'un client : on recopie simplement les attributs internes.
Client::Client(const Client& other)
{
	*this = other;
}

// Operateur d'affectation : on recopie les donnees d'un client dans un autre.
Client& Client::operator=(const Client& other)
{
	if (this != &other)
	{
		_fd = other._fd;
		_nickname = other._nickname;
		_username = other._username;
		_buffer = other._buffer;
		_isRegistered = other._isRegistered;
	}
	return (*this);
}

// Destructeur : rien de special pour l'instant, car le socket est gere ailleurs.
Client::~Client()
{
}

int Client::getFd() const
{
	return (_fd);
}

std::string Client::getNickname() const
{
	return (_nickname);
}

std::string Client::getUsername() const
{
	return (_username);
}

std::string Client::getBuffer() const
{
	return (_buffer);
}

bool Client::isRegistered() const
{
	return (_isRegistered);
}

void Client::setFd(int fd)
{
	_fd = fd;
}

void Client::setNickname(const std::string& nickname)
{
	_nickname = nickname;
}

void Client::setUsername(const std::string& username)
{
	_username = username;
}

void Client::setBuffer(const std::string& buffer)
{
	_buffer = buffer;
}

void Client::appendBuffer(const std::string& data)
{
	_buffer += data;
}

void Client::clearBuffer()
{
	_buffer.clear();
}

void Client::setRegistered(bool isRegistered)
{
	_isRegistered = isRegistered;
}
