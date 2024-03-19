/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:09:59 by mfinette          #+#    #+#             */
/*   Updated: 2024/03/18 22:19:23 by maxime           ###   ########.fr       */
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
#include <vector>
#include <fstream>
#include <ctime>

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
# define BUFFER_SIZE 1024

// # define BOT_GLOBAL_INFO	"You are a bot in an irc server. You dont have any possible interactions with the server, you can only join channels. Here are the available commands: [join, help, hello, joke, funfact, generate, chatbot]. If someone asks you a question about the server, say that it is coded by people way too intelligent for you to understand, and give them a list of the available commands. If not, people will just talk to you, make sure to be funny in every response. Every response must also be in only one line, make sure to have no new lines in your respones, although the response line can be very long if needed. Have fun!"
# define BOT_GLOBAL_INFO	"You are a bot in an irc server, and you are very very sarcastic. Sarcasm doesnt mean starting every answer with <Oh> You have no interaction with the server, the only thing you can do is talk back to the clients. Also, the answers can be as long as you want but have to be in one line. No new line characters allowed."
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

/////////// SERVER UTILS ///////////
int						createSocket(void);
bool					connectToServer(int client_socket, int port);
void					sendMessage(int client_socket, const std::string& message);
void					receiveAndPrintMessage(int client_socket);
void					connectBot(int client_socket, char **argv);
void					handleUserInput(int client_socket);
void					chooseResponse(int client_socket, Cmd cmd);
void					sendResponse(int client_socket, Cmd cmd);

/////////// COMMANDS ///////////
void					help(int client_socket, Cmd cmd);
void					joke(int client_socket, Cmd cmd);
void					join(int client_socket, Cmd cmd);
void					hello(int client_socket, Cmd cmd);
void					funfact(int client_socket, Cmd cmd);
void					generate(int client_socket, Cmd cmd);
void					chatbot(int client_socket, Cmd cmd);

/////////// COMMAND UTILS ///////////
std::string				fetchJoke();
std::string				fetchFunFact();
std::string				getImageFromAPI(const char *prompt);
std::string				getChatAnswerFromAPI(const char* prompt);

/////////// PARSING ///////////
std::string				getFirstWord(std::string str);
std::string				getSecondWord(std::string str);
std::string				getRemaining(std::string str);
std::string 			removeBackslashR(std::string str);
std::string 			removeBackslashRN(std::string str);
std::string				getFirstWordAfter2Colons(std::string str);
std::string				getStringWithoutFirstWord(std::string str);
std::string				getStringWithout2FirstWords(std::string str);
void					printCommand(Cmd cmd);
bool					isLastWord(std::string str, std::string toFind);
std::string				removeDoubleQuotesFromEntireString(std::string str);
std::string				removeSingleQuotesFromEntireString(std::string str);


#endif