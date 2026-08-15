#ifndef REPLIES_HPP
#define REPLIES_HPP

#include <iostream>
#include <string>
#include <sstream>

class Client;

/**
 * @class Replies
 * @brief Classe contenant toutes les réponses IRC standardisées
 * 
 * Selon la RFC 2812, les réponses IRC doivent suivre un format précis.
 * Cette classe génère les réponses correctement formatées.
 */
class Replies
{
public:
	// Numéros de réponse IRC

	// Succès (200-299)
	static const int RPL_WELCOME = 001;
	static const int RPL_YOURHOST = 002;
	static const int RPL_CREATED = 003;
	static const int RPL_MYINFO = 004;
	static const int RPL_BOUNCE = 005;

	// Réponses utilisateur (300-399)
	static const int RPL_USERHOST = 302;
	static const int RPL_ISON = 303;
	static const int RPL_AWAY = 301;
	static const int RPL_UNAWAY = 305;
	static const int RPL_NOWAWAY = 306;

	// Réponses de statut (400-599)
	static const int RPL_WHOISUSER = 311;
	static const int RPL_WHOISSERVER = 312;
	static const int RPL_WHOISOPERATOR = 313;
	static const int RPL_WHOISIDLE = 317;
	static const int RPL_ENDOFWHOIS = 318;
	static const int RPL_WHOISCHANNELS = 319;
	static const int RPL_WHOWASUSER = 314;
	static const int RPL_ENDOFWHOWAS = 369;
	static const int RPL_LISTSTART = 321;
	static const int RPL_LIST = 322;
	static const int RPL_LISTEND = 323;
	static const int RPL_UNIQOPIS = 325;
	static const int RPL_CHANNELMODEIS = 324;
	static const int RPL_NOTOPIC = 331;
	static const int RPL_TOPIC = 332;
	static const int RPL_INVITING = 341;
	static const int RPL_SUMMONING = 342;
	static const int RPL_INVITELIST = 346;
	static const int RPL_ENDOFINVITELIST = 347;
	static const int RPL_EXCEPTLIST = 348;
	static const int RPL_ENDOFEXCEPTLIST = 349;
	static const int RPL_VERSION = 351;
	static const int RPL_WHOREPLY = 352;
	static const int RPL_ENDOFWHO = 315;
	static const int RPL_NAMREPLY = 353;
	static const int RPL_ENDOFNAMES = 366;
	static const int RPL_LINKS = 364;
	static const int RPL_ENDOFLINKS = 365;
	static const int RPL_BANLIST = 367;
	static const int RPL_ENDOFBANLIST = 368;
	static const int RPL_INFO = 371;
	static const int RPL_ENDOFINFO = 374;
	static const int RPL_MOTDSTART = 375;
	static const int RPL_MOTD = 372;
	static const int RPL_ENDOFMOTD = 376;
	static const int RPL_YOUREOPER = 381;
	static const int RPL_REHASHING = 382;
	static const int RPL_YOURESERVICE = 383;
	static const int RPL_TIME = 391;
	static const int RPL_USERSSTART = 392;
	static const int RPL_USERS = 393;
	static const int RPL_ENDOFUSERS = 394;
	static const int RPL_NOUSERS = 395;
	static const int RPL_TRACELINK = 200;
	static const int RPL_TRACECONNECTING = 201;
	static const int RPL_TRACEHANDSHAKE = 202;
	static const int RPL_TRACEUNKNOWN = 203;
	static const int RPL_TRACEOPERATOR = 204;
	static const int RPL_TRACEUSER = 205;
	static const int RPL_TRACESERVER = 206;
	static const int RPL_TRACENEWTYPE = 208;
	static const int RPL_TRACECLASS = 209;
	static const int RPL_TRACERECONNECT = 210;
	static const int RPL_TRACELOG = 261;
	static const int RPL_TRACEEND = 262;
	static const int RPL_STATSLINKINFO = 211;
	static const int RPL_STATSCOMMANDS = 212;
	static const int RPL_ENDOFSTATS = 219;
	static const int RPL_STATSUPTIME = 242;
	static const int RPL_STATSOLINE = 243;
	static const int RPL_UMODEIS = 221;
	static const int RPL_SERVLIST = 234;
	static const int RPL_SERVLISTEND = 235;
	static const int RPL_HELPHDR = 704;
	static const int RPL_HELPBODY = 705;
	static const int RPL_HELPTLR = 706;

	// Erreurs (400-599)
	static const int ERR_NOSUCHNICK = 401;
	static const int ERR_NOSUCHSERVER = 402;
	static const int ERR_NOSUCHCHANNEL = 403;
	static const int ERR_CANNOTSENDTOCHAN = 404;
	static const int ERR_TOOMANYCHANNELS = 405;
	static const int ERR_WASNOSUCHNICK = 406;
	static const int ERR_TOOMANYTARGETS = 407;
	static const int ERR_NOSUCHSERVICE = 408;
	static const int ERR_NOORIGIN = 409;
	static const int ERR_NORECIPIENT = 411;
	static const int ERR_NOTEXTTOSEND = 412;
	static const int ERR_NOTOPLEVEL = 413;
	static const int ERR_WILDTOPLEVEL = 414;
	static const int ERR_BADMASK = 415;
	static const int ERR_UNKNOWNCOMMAND = 421;
	static const int ERR_NOMOTD = 422;
	static const int ERR_NOADMININFO = 423;
	static const int ERR_FILEERROR = 424;
	static const int ERR_NONICKNAMEGIVEN = 431;
	static const int ERR_ERRONEUSNICKNAME = 432;
	static const int ERR_NICKNAMEINUSE = 433;
	static const int ERR_NICKCOLLISION = 436;
	static const int ERR_UNAVAILRESOURCE = 437;
	static const int ERR_USERNOTINCHANNEL = 441;
	static const int ERR_NOTONCHANNEL = 442;
	static const int ERR_USERONCHANNEL = 443;
	static const int ERR_NOLOGIN = 444;
	static const int ERR_SUMMONDISABLED = 445;
	static const int ERR_USERSDISABLED = 446;
	static const int ERR_NOTREGISTERED = 451;
	static const int ERR_NEEDMOREPARAMS = 461;
	static const int ERR_ALREADYREGISTRED = 462;
	static const int ERR_NOPERMFORHOST = 463;
	static const int ERR_PASSWDMISMATCH = 464;
	static const int ERR_YOUREBANNEDCREEP = 465;
	static const int ERR_YOUWILLBEBANNED = 466;
	static const int ERR_KEYSET = 467;
	static const int ERR_CHANNELISFULL = 471;
	static const int ERR_UNKNOWNMODE = 472;
	static const int ERR_INVITEONLYCHAN = 473;
	static const int ERR_BANNEDFROMCHAN = 474;
	static const int ERR_BADCHANNELKEY = 475;
	static const int ERR_BADCHANMASK = 476;
	static const int ERR_NOCHANMODES = 477;
	static const int ERR_BANLISTFULL = 478;
	static const int ERR_NOPRIVILEGES = 481;
	static const int ERR_CHANOPRIVSNEEDED = 482;
	static const int ERR_CANTMODEBAN = 484;
	static const int ERR_USERSDONTMATCH = 502;

	Replies(void);
	~Replies(void);

	/**
	 * @brief Formate une réponse IRC
	 * @param code Code de réponse numérique
	 * @param params Les paramètres de la réponse
	 * @param message Le message optionnel
	 * @return La réponse formatée
	 */
	static std::string formatReply(int code, const std::string &nick, 
		const std::string &params, const std::string &message);

	// Réponses de bienvenue
	static std::string welcomeMessage(const std::string &nick, const std::string &user, 
		const std::string &host);
	
	// Réponses d'erreur
	static std::string errorNeedMoreParams(const std::string &nick, const std::string &cmd);
	static std::string errorNickNameInUse(const std::string &nick);
	static std::string errorNotRegistered(const std::string &nick);
	static std::string errorUnknownCommand(const std::string &nick, const std::string &cmd);
	static std::string errorNoSuchNick(const std::string &nick, const std::string &target);
	static std::string errorNoSuchChannel(const std::string &nick, const std::string &channel);
	static std::string errorNotOnChannel(const std::string &nick, const std::string &channel);
	static std::string errorUserNotInChannel(const std::string &nick, const std::string &user, 
		const std::string &channel);
	static std::string errorChanOPrivsNeeded(const std::string &nick, const std::string &channel);
	static std::string errorChannelIsFull(const std::string &nick, const std::string &channel);
	static std::string errorInviteOnlyChannel(const std::string &nick, const std::string &channel);
	static std::string errorBadChannelKey(const std::string &nick, const std::string &channel);

private:
	typedef int ResponseCode;
};

#endif
