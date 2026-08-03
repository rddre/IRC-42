#include "irc.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
        return (1);

    Server server(argv[1], argv[2]);

    server.run();
}