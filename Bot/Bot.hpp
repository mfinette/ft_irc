/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:09:59 by mfinette          #+#    #+#             */
/*   Updated: 2024/03/08 20:36:23 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

#include <iostream>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <cerrno>
#include <sstream>

# define RESET				"\033[0m"
# define BLACK				"\033[30m"
# define RED				"\033[31m"
# define GREEN				"\033[32m"
# define YELLOW				"\033[33m"
# define BLUE				"\033[34m"
# define DARK_BLUE			"\033[34m"
# define MEDIUM_BLUE		"\033[36m"
# define DODGER_BLUE		"\033[94m"
# define STEEL_BLUE			"\033[38;5;67m"
# define MAGENTA			"\033[35m"
# define CYAN				"\033[36m"
# define WHITE				"\033[37m"
# define LIGHT_PINK			"\033[38;5;217m"
# define MEDIUM_PINK		"\033[38;5;219m"
# define DARK_PINK			"\033[38;5;205m"
# define PALE_PINK			"\033[38;5;218m"
# define HOT_PINK			"\033[38;5;205m"
# define BABY_PINK			"\033[38;5;225m"
# define NEON_PINK			"\033[38;5;207m"

const int BUFFER_SIZE = 1024;

class	Cmd
{
	public:
		Cmd(std::string cmd);
		~Cmd();
		std::string		_fullCmd;
		std::string		_sender;
		std::string		_channel;
		std::string		_cmdType;
		std::string		_cmdRemaining;
		bool			_isForBot;
		bool			_isPRIVMSG;
		bool			_isChannel;
};

int						createSocket(void);
bool					connectToServer(int client_socket, int port);
void					sendMessage(int client_socket, const std::string& message);
void					receiveAndPrintMessage(int client_socket);
void					connectBot(int client_socket, char **argv);
void					handleUserInput(int client_socket);
void					chooseResponse(int client_socket, Cmd cmd);
void					sendResponse(int client_socket, Cmd cmd);
std::string				getFirstWord(std::string str);
std::string				getSecondWord(std::string str);
std::string				getRemaining(std::string str);
std::string 			removeBackslashR(std::string str);
std::string 			removeBackslashRN(std::string str);
std::string				getFirstWordAfter2Colons(std::string str);
std::string				fetchJoke();

/////////// COMMANDS ///////////
void					help(int client_socket, Cmd cmd);

#endif