NAME		:= ircserv

CXX		:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98
INCLUDES	:= -Iinclude

SRC_DIR		:= src
OBJ_DIR		:= obj

SRCS		:= \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/server/Server.cpp \
	$(SRC_DIR)/server/Poll.cpp \
	$(SRC_DIR)/server/Socket.cpp \
	$(SRC_DIR)/server/Accept.cpp \
	$(SRC_DIR)/server/Receive.cpp \
	$(SRC_DIR)/server/Send.cpp \
	$(SRC_DIR)/server/Disconnect.cpp \
	$(SRC_DIR)/client/Client.cpp \
	$(SRC_DIR)/channel/Channel.cpp \
	$(SRC_DIR)/parser/Parser.cpp \
	$(SRC_DIR)/commands/CommandHandler.cpp \
	$(SRC_DIR)/commands/PASS.cpp \
	$(SRC_DIR)/commands/NICK.cpp \
	$(SRC_DIR)/commands/USER.cpp \
	$(SRC_DIR)/commands/JOIN.cpp \
	$(SRC_DIR)/commands/PRIVMSG.cpp \
	$(SRC_DIR)/commands/KICK.cpp \
	$(SRC_DIR)/commands/INVITE.cpp \
	$(SRC_DIR)/commands/TOPIC.cpp \
	$(SRC_DIR)/commands/MODE.cpp \
	$(SRC_DIR)/replies/Replies.cpp \
	$(SRC_DIR)/utils/Utils.cpp

OBJS		:= $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
