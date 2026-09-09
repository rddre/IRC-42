#include "irc.hpp"

// Cette fonction initialise le socket serveur avec socket().
// On cree le descripteur de socket du serveur en mode TCP IPv4.
void Server::initSocket()
{
    _serverFd = socket(AF_INET, SOCK_STREAM, 0);

    if (_serverFd < 0)
    {
        std::cerr << "socket() failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Socket created (fd = " << _serverFd << ")" << std::endl;
}

// Cette fonction configurer la socket serveur avec SO_REUSEADDR.
// Cela permet de reutiliser rapidement le port quand le serveur redemarre.
void Server::configureSocket()
{
    int optVal = 1;

    if (setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal)) == -1)
    {
        perror("setsockopt");
        close(_serverFd);
        exit(EXIT_FAILURE);
    }
}

// Cette fonction relie le socket serveur a un port local.
// On choisit INADDR_ANY pour ecouter sur toutes les interfaces disponibles.
void Server::bindSocket()
{
    struct sockaddr_in serverAddr;

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(static_cast<unsigned short>(std::atoi(_port.c_str())));
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(_serverFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("bind");
        close(_serverFd);
        exit(EXIT_FAILURE);
    }
}

// Cette fonction met le socket serveur en mode ecoute avec un backlog.
// Le backlog correspond au nombre de connexions en attente avant traitement.
void Server::listenSocket()
{
    int backlog = 42;

    if (listen(_serverFd, backlog) == -1)
    {
        perror("listen");
        close(_serverFd);
        exit(EXIT_FAILURE);
    }
}

// Cette fonction met un socket en mode non bloquant avec fcntl().
// Cela est essentiel pour poll() et pour ne pas bloquer le serveur sur recv/send.
void Server::setNonBlocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);

    if (flags == -1)
    {
        perror("fcntl");
        close(fd);
        exit(EXIT_FAILURE);
    }
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
    {
        perror("fcntl");
        close(fd);
        exit(EXIT_FAILURE);
    }
}
