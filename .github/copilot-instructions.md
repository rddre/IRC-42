# ft_irc - Copilot Repository Instructions

## Project

42 ft_irc project.

Language: C++98.

The project must compile with:

- c++ -Wall -Wextra -Werror
- c++ -std=c++98

No external libraries or Boost.

Do not introduce C++11 or newer features.

---

## Official project requirements

The server executable is:

./ircserv <port> <password>

The server must:

- handle multiple clients simultaneously without hanging
- use non-blocking I/O
- use one poll() or equivalent to handle all I/O operations
- use TCP/IP
- correctly handle partial/incomplete network data
- aggregate received data before processing complete IRC commands
- never rely on errno after recv/send to decide what to do next
- not crash or terminate unexpectedly

Do not implement:

- an IRC client
- server-to-server communication
- unnecessary bonus features before the mandatory part is complete

Allowed networking/system APIs are those permitted by the ft_irc subject.

---

## Mandatory IRC functionality

The mandatory implementation must support:

- authentication with the server password
- nickname
- username
- joining channels
- private messaging
- channel messaging
- broadcasting channel messages to other members
- channel operators
- regular users

Operator commands:

- KICK
- INVITE
- TOPIC
- MODE

Required MODE flags:

- i: invite-only
- t: topic restricted to channel operators
- k: channel key
- o: operator privilege
- l: user limit

Do not add unrelated IRC behavior unless explicitly requested.

---

## Team ownership

This project has two developers.

### Ayoub owns

- Parser
- Channel
- CommandHandler
- PASS
- USER
- NICK
- JOIN
- PRIVMSG
- KICK
- INVITE
- TOPIC
- MODE
- IRC replies
- Parser tests
- Channel tests

### Andrei owns

- Makefile
- main
- Server
- Socket
- Poll
- Accept
- Receive
- Send
- Disconnect
- Client
- Utils
- memory cleanup
- TCP connection handling

Respect this separation.

Do not modify the other developer's area unless it is strictly required for integration or compilation.

If a change to another developer's interface is required, explain:

1. why it is required
2. what interface is affected
3. what code depends on it
4. the smallest safe change

Never silently redesign another developer's module.

---

## Architecture rules

Preserve the existing architecture unless explicitly asked to refactor it.

Prefer:

- minimal changes
- localized changes
- existing classes and interfaces
- simple C++98 solutions
- explicit code over unnecessary abstractions

Do not:

- rewrite working modules for style reasons
- introduce unnecessary design patterns
- rename large parts of the project without a reason
- add dependencies
- change public interfaces without explaining the impact
- modify unrelated files

The README is not authoritative for implementation status.

Always inspect the actual source code.

---

## Before modifying code

First inspect the relevant files and understand:

- existing architecture
- class responsibilities
- existing APIs
- dependencies
- data flow
- ownership of the code being modified

For non-trivial tasks, briefly state the implementation approach before editing.

Do not modify files outside the requested scope unless strictly necessary.

---

## Implementation workflow

For each task:

1. Inspect the relevant code.
2. Identify dependencies.
3. Implement the smallest correct change.
4. Compile.
5. Run relevant tests.
6. Inspect the resulting diff.
7. Report what changed and any remaining issue.

Do not claim that something works without compiling/testing it.

---

## IRC/network edge cases

When implementing or reviewing code, consider:

- multiple connected clients
- disconnected clients
- invalid client state
- malformed commands
- missing parameters
- extra parameters
- unknown nicknames
- unknown channels
- unauthorized operations
- permission errors
- duplicate nicknames
- duplicate channel membership
- channel keys
- invite-only channels
- user limits
- operator privileges
- topic permissions
- partial TCP messages
- multiple IRC commands received together
- commands split across multiple recv() calls
- connection cleanup
- resource cleanup

Do not assume one recv() call contains exactly one IRC command.

---

## Command/reply behavior

Keep command parsing, validation, execution and IRC replies clearly separated according to the existing architecture.

When adding or modifying a command:

- validate parameters
- validate client state
- validate permissions
- update server/channel/client state correctly
- send the appropriate IRC reply/error
- avoid sending messages to the wrong clients

Do not invent protocol behavior when the existing project design or official subject does not require it.

---

## Memory and resource safety

Any change involving:

- clients
- sockets
- channels
- dynamically allocated objects
- containers
- file descriptors

must consider cleanup and lifetime ownership.

Avoid leaks, dangling pointers, invalid file descriptors and use-after-free situations.

---

## Compilation and tests

Before considering a change complete, use the project's normal build system.

At minimum verify:

make
make re

when appropriate.

Use focused tests for the module being changed.

For networking behavior, test with a real IRC client and/or suitable command-line tools where useful.

Test both valid and invalid cases.

---

## Git

Do not commit or push unless explicitly requested.

Do not modify main directly.

Do not reset, force-push, rebase shared branches, or discard work unless explicitly requested.

Development branches:

- ayoub
- andrei
- integration
- main

`integration` is used to test the two developers' work together.

When working on Ayoub's features, keep implementation commits on `ayoub`.

Do not mix unrelated changes into the same commit.

---

## Scope control

When asked to implement one feature:

- implement that feature only
- do not opportunistically refactor unrelated code
- do not "improve" other modules
- do not rewrite code that already works
- do not add bonus functionality

If the requested feature requires a change outside its normal scope, explain the dependency before making the change.

---

## Final review of a task

Before reporting a task as complete, verify:

- code compiles
- relevant tests pass
- no unrelated files were changed
- no C++11+ features were introduced
- architecture remains consistent
- error handling is present
- resource cleanup is safe
- the diff is minimal
