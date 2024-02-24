# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxime <maxime@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 16:53:11 by mfinette          #+#    #+#              #
#    Updated: 2024/02/24 19:26:00 by maxime           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ircserv
	
CC			= c++
FLAGS		= -Wall -Wextra  -g3 -std=c++98 #-Werror 
RM			= rm -rf

OBJDIR = .objFiles

FILES		= 	main \
				server channel command client signal \
				parseLoginData clientChannelManagement \
				Commands/NICK Commands/PASS Commands/PRIVMSG Commands/JOIN Commands/USER  Commands/TOPIC Commands/INVITE Commands/KICK\

SRC			= $(FILES:=.cpp)
OBJ			= $(addprefix $(OBJDIR)/, $(FILES:=.o))
HEADER		= Headers/*.hpp
#Colors:
GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(OBJ) -o $(NAME)
	@printf "$(GREEN)- Executable ready.\n$(RESET)"

$(OBJDIR)/%.o: %.cpp $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(OPTS) -c $< -o $@

clean:
	@$(RM) $(OBJDIR) $(OBJ)
	@printf "$(YELLOW)    - Object files removed.$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(YELLOW)    - Executable removed.$(RESET)\n"

re: fclean all

valgrind: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 6667 1

.PHONY: all clean fclean re bonus norm
