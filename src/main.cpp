#include "irc.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
        return (1);

    int port = std::atoi(argv[1]);
    if (port <= 0)
        return (1);

    Server server(port, argv[2]);

    server.run();
    return 0;
}