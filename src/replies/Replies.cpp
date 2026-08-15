#include "Replies.hpp"
#include <sstream>
#include <iomanip>

Replies::Replies(void)
{
}

Replies::~Replies(void)
{
}

std::string Replies::formatReply(int code, const std::string &nick, 
	const std::string &params, const std::string &message)
{
	std::stringstream ss;
	ss << ":" << "irc.server.local" << " ";
	ss << std::setfill('0') << std::setw(3) << code << " ";
	ss << nick << " " << params;
	if (!message.empty())
		ss << " :" << message;
	ss << "\r\n";
	return ss.str();
}

std::string Replies::welcomeMessage(const std::string &nick, const std::string &user,
	const std::string &host)
{
	std::stringstream ss;
	ss << formatReply(RPL_WELCOME, nick, "", 
		"Welcome to the Internet Relay Chat Network " + nick + "!" + user + "@" + host);
	return ss.str();
}

std::string Replies::errorNeedMoreParams(const std::string &nick, const std::string &cmd)
{
	return formatReply(ERR_NEEDMOREPARAMS, nick, cmd, "Not enough parameters");
}

std::string Replies::errorNickNameInUse(const std::string &nick)
{
	return formatReply(ERR_NICKNAMEINUSE, nick, nick, "Nickname is already in use");
}

std::string Replies::errorNotRegistered(const std::string &nick)
{
	return formatReply(ERR_NOTREGISTERED, nick, "", "You have not registered");
}

std::string Replies::errorUnknownCommand(const std::string &nick, const std::string &cmd)
{
	return formatReply(ERR_UNKNOWNCOMMAND, nick, cmd, "Unknown command");
}

std::string Replies::errorNoSuchNick(const std::string &nick, const std::string &target)
{
	return formatReply(ERR_NOSUCHNICK, nick, target, "No such nick/channel");
}

std::string Replies::errorNoSuchChannel(const std::string &nick, const std::string &channel)
{
	return formatReply(ERR_NOSUCHCHANNEL, nick, channel, "No such channel");
}

std::string Replies::errorNotOnChannel(const std::string &nick, const std::string &channel)
{
	return formatReply(ERR_NOTONCHANNEL, nick, channel, "You're not on that channel");
}

std::string Replies::errorUserNotInChannel(const std::string &nick, const std::string &user,
	const std::string &channel)
{
	std::stringstream ss;
	ss << formatReply(ERR_USERNOTINCHANNEL, nick, user + " " + channel, "They aren't on that channel");
	return ss.str();
}

std::string Replies::errorChanOPrivsNeeded(const std::string &nick, const std::string &channel)
{
	return formatReply(ERR_CHANOPRIVSNEEDED, nick, channel, "You're not channel operator");
}

std::string Replies::errorChannelIsFull(const std::string &nick, const std::string &channel)
{
	return formatReply(ERR_CHANNELISFULL, nick, channel, "Cannot join channel (+l)");
}

std::string Replies::errorInviteOnlyChannel(const std::string &nick, const std::string &channel)
{
	return formatReply(ERR_INVITEONLYCHAN, nick, channel, "Cannot join channel (+i)");
}

std::string Replies::errorBadChannelKey(const std::string &nick, const std::string &channel)
{
	return formatReply(ERR_BADCHANNELKEY, nick, channel, "Bad channel key");
}
