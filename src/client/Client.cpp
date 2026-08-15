#include "Client.hpp"
#include "../channel/Channel.hpp"

Client::Client(int fd)
	: _fd(fd), _nickname(""), _username(""), _realname(""), _hostname(""),
	  _passwordValid(false), _authenticated(false)
{
}

Client::~Client(void)
{
}

int Client::getFd(void) const
{
	return _fd;
}

std::string Client::getNickname(void) const
{
	return _nickname;
}

std::string Client::getUsername(void) const
{
	return _username;
}

std::string Client::getRealname(void) const
{
	return _realname;
}

std::string Client::getHostname(void) const
{
	return _hostname;
}

bool Client::isAuthenticated(void) const
{
	return _authenticated;
}

bool Client::isPasswordValid(void) const
{
	return _passwordValid;
}

bool Client::isNicknameSet(void) const
{
	return !_nickname.empty();
}

bool Client::isUserRegistered(void) const
{
	return !_username.empty() && !_realname.empty();
}

std::vector<Channel *> Client::getChannels(void) const
{
	return _channels;
}

void Client::setNickname(const std::string &nickname)
{
	_nickname = nickname;
}

void Client::setUsername(const std::string &username)
{
	_username = username;
}

void Client::setRealname(const std::string &realname)
{
	_realname = realname;
}

void Client::setHostname(const std::string &hostname)
{
	_hostname = hostname;
}

void Client::setPasswordValid(bool valid)
{
	_passwordValid = valid;
}

void Client::setAuthenticated(bool auth)
{
	_authenticated = auth;
}

void Client::addChannel(Channel *channel)
{
	if (channel != NULL)
	{
		for (size_t i = 0; i < _channels.size(); ++i)
		{
			if (_channels[i] == channel)
				return;
		}
		_channels.push_back(channel);
	}
}

void Client::removeChannel(Channel *channel)
{
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i] == channel)
		{
			_channels.erase(_channels.begin() + i);
			return;
		}
	}
}

bool Client::isInChannel(Channel *channel) const
{
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i] == channel)
			return true;
	}
	return false;
}

void Client::appendToRecvBuffer(const std::string &data)
{
	_recvBuffer += data;
}

std::string Client::getRecvBuffer(void) const
{
	return _recvBuffer;
}

void Client::clearRecvBuffer(void)
{
	_recvBuffer.clear();
}

void Client::appendToSendBuffer(const std::string &data)
{
	_sendBuffer += data;
}

std::string Client::getSendBuffer(void) const
{
	return _sendBuffer;
}

void Client::clearSendBuffer(void)
{
	_sendBuffer.clear();
}
