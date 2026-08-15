# ft_irc - Internet Relay Chat Server

*This project has been created as part of the 42 curriculum by blckstar.*

## Description

ft_irc is a custom IRC (Internet Relay Chat) server implementation in C++ 98. It allows multiple clients to connect, authenticate, and communicate in real-time through channels and private messages.

The project is divided into two main parts:
- **Part A** (~50%): Server infrastructure (Socket management, polling, client connections)
- **Part B** (~50%): Communication protocol implementation (Parser, channels, commands, replies)

This document focuses on **Part B** of the implementation.

### Part B - Communication Protocol

This section handles:

#### 1. **Parser (IRC Protocol)**
- Parses incoming IRC messages according to RFC 2812
- Handles partial messages and buffer aggregation
- Supports prefix, command name, parameters, and trailing message
- Manages incomplete commands when data arrives in chunks

#### 2. **Channel Management**
- Represents IRC channels where multiple users can communicate
- Implements channel modes:
  - `i` (Invite-only): Channel is invite-only
  - `t` (Topic restricted): Only channel operators can change topic
  - `k` (Key): Channel requires a password
  - `o` (Operator): Grant/revoke channel operator privileges
  - `l` (Limit): Set maximum number of users
- Supports channel operators and regular users
- Manages user lists and broadcasts messages

#### 3. **Command Handler**
- Dispatches incoming commands to appropriate handlers
- Implements all required IRC commands:
  - **PASS**: Authenticate with server password
  - **NICK**: Set or change nickname
  - **USER**: Register user information
  - **JOIN**: Join one or more channels
  - **PRIVMSG**: Send messages to users or channels
  - **KICK**: Remove users from channels (operator only)
  - **INVITE**: Invite users to channels
  - **TOPIC**: Set or view channel topic
  - **MODE**: Change channel or user modes

#### 4. **IRC Replies**
- Generates properly formatted IRC protocol responses
- Implements all standard reply codes (RPL_* and ERR_*)
- Follows RFC 2812 format: `:server code nick params :message\r\n`

#### 5. **Tests**
- Unit tests for Parser functionality
- Unit tests for Channel management
- Basic tests for CommandHandler

## Project Structure

```
IRC-42/
├── Makefile                    # Build configuration
├── README.md                   # This file
├── include/
│   └── irc.hpp                # Main header file with includes
├── src/
│   ├── main.cpp               # Entry point (Part A)
│   ├── parser/
│   │   ├── Parser.hpp
│   │   └── Parser.cpp
│   ├── channel/
│   │   ├── Channel.hpp
│   │   └── Channel.cpp
│   ├── commands/
│   │   ├── CommandHandler.hpp
│   │   ├── CommandHandler.cpp
│   │   ├── PASS.cpp
│   │   ├── NICK.cpp
│   │   ├── USER.cpp
│   │   ├── JOIN.cpp
│   │   ├── PRIVMSG.cpp
│   │   ├── KICK.cpp
│   │   ├── INVITE.cpp
│   │   ├── TOPIC.cpp
│   │   └── MODE.cpp
│   ├── replies/
│   │   ├── Replies.hpp
│   │   └── Replies.cpp
│   ├── client/                 # (Part A)
│   ├── server/                 # (Part A)
│   └── utils/                  # (Part A)
└── tests/
    ├── parser_test.cpp
    ├── channel_test.cpp
    └── client_test.cpp
```

## Instructions

### Compilation

```bash
# Navigate to the project directory
cd IRC-42

# Build the project
make

# Build with all sources
make all

# Run tests
make test

# Clean build artifacts
make clean

# Full clean and rebuild
make fclean
make re
```

### Running the Server

```bash
./ircserv <port> <password>
```

Example:
```bash
./ircserv 6667 mysecretpassword
```

### Testing

The project includes unit tests for the main components:

```bash
# Run parser tests
./tests/parser_test

# Run channel tests
./tests/channel_test

# Run client tests
./tests/client_test
```

### Testing with IRC Client

1. Start the server:
```bash
./ircserv 6667 mypassword
```

2. Connect with an IRC client (e.g., irssi, netcat):
```bash
irssi
/connect 127.0.0.1 6667
/nick mynickname
/msg NickServ PASS mypassword  # Send password
```

## Implementation Details

### Parser (RFC 2812 Compliance)

The IRC protocol message format is:
```
[:<prefix> ]<command> [<param1> [<param2> [... [<param15>]]]] [:<trailing>]
```

The Parser class correctly handles:
- Optional prefix (usually from server)
- Command name (case-insensitive)
- 0-15 parameters separated by spaces
- Trailing message (allows spaces)
- Line endings: `\r\n`
- Partial messages across multiple packets

### Channel Modes

Channels support complex mode configurations:

```
MODE #channel +i          # Make invite-only
MODE #channel +t          # Restrict TOPIC to operators
MODE #channel +k secret   # Set channel key
MODE #channel +l 10       # Set user limit to 10
MODE #channel +o user1    # Give operator to user1
MODE #channel -o user1    # Remove operator from user1
```

### Command Flow

1. Server receives data from client
2. Parser aggregates partial messages
3. Parser creates Command struct
4. CommandHandler dispatches to appropriate cmd_* function
5. Command validates permissions and parameters
6. Command modifies state (channels, users, modes)
7. Replies generated and sent to relevant clients

## Resources

### IRC Protocol
- **RFC 2812**: Internet Relay Chat Protocol
  - https://tools.ietf.org/html/rfc2812

- **RFC 1459**: Internet Relay Chat Protocol (Original)
  - https://tools.ietf.org/html/rfc1459

### IRC Clients (for testing)
- **irssi**: Terminal-based IRC client
  - https://irssi.org/

- **Hexchat**: GUI IRC client
  - https://hexchat.github.io/

- **netcat**: Simple network utility (basic testing)
  - `nc -C 127.0.0.1 6667`

### C++ 98 References
- **cppreference.com**: C++ Standard Library
  - https://en.cppreference.com/w/cpp/container

- **cplusplus.com**: C++ Tutorial
  - http://www.cplusplus.com/

### Socket Programming
- **Man pages**: POSIX socket API
  - `man socket`, `man bind`, `man listen`, `man accept`
  - `man poll`, `man send`, `man recv`

## How AI Was Used

This project utilized AI assistance for:

1. **Code Structure & Templates**: Generated basic class structures and method signatures following C++ 98 standards and 42 school conventions.

2. **Parser Implementation**: AI provided regex patterns and string manipulation algorithms for parsing IRC protocol messages, specifically for handling the complex message format with prefix, command, parameters, and trailing sections.

3. **Protocol Response Generation**: Generated RFC 2812-compliant response templates and format strings for IRC protocol replies.

4. **Test Framework**: Created unit test templates and assertion patterns to validate Parser and Channel functionality.

5. **Documentation**: Generated comprehensive inline documentation and README sections explaining IRC protocol concepts.

**Important note**: All generated code was thoroughly reviewed, understood, tested, and modified to fit the 42 school standards and our specific requirements. The implementation was validated against IRC protocol specifications and peer-reviewed before deployment.

## Key Features

- ✅ RFC 2812 compliant IRC protocol parsing
- ✅ Channel management with operator privileges
- ✅ Multiple channel modes (i, t, k, o, l)
- ✅ Complete command implementation (PASS, NICK, USER, JOIN, PRIVMSG, KICK, INVITE, TOPIC, MODE)
- ✅ Standard IRC protocol replies and error messages
- ✅ Buffer management for partial/fragmented messages
- ✅ Comprehensive unit testing
- ✅ C++ 98 compliant code

## Compilation Flags

As per 42 school requirements:
```
-Wall -Wextra -Werror -std=c++98
```

## Notes for Evaluators

- The code does NOT use forking; all I/O is non-blocking
- Only one poll() call is used for all I/O operations
- No external libraries are used beyond C++ 98 standard library
- The implementation handles edge cases like partial messages and buffer overflow
- All required IRC commands are implemented and tested
- The code is organized modularly with clear separation of concerns

## Future Enhancements

- File transfer support
- IRC bot implementation
- Server-to-server communication
- SSL/TLS encryption
- Advanced user authentication
- Channel persistence

---

For questions or issues, refer to the source code comments and the IRC protocol specifications linked in the Resources section.
