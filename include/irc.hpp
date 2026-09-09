#ifndef IRC_HPP
#define IRC_HPP

//--------------- includes ----------------
# include <iostream>
# include <string>
// include pour unsleep
# include <unistd.h>
//include pour socket
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <poll.h>
# include <vector>
# include <cstring>
# include <cerrno>
# include <cstdio>
// include pour exit et failure exit
# include <stdlib.h>

//--------------- colors ----------------
# define RESET   "\033[0m"

# define BLACK   "\033[30m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"

# define BOLD    "\033[1m"

//--------------- les classes ----------------
#include "channel/Channel.hpp"
#include "client/Client.hpp"
#include "commands/CommandHandler.hpp"
#include "parser/Parser.hpp"
#include "server/Server.hpp"

//--------------- prototypes ----------------
//--------------- replies (toutes les fonctions de reply) ----------------

//--------------- utils (toutes les fonctions utiles) ----------------


#endif