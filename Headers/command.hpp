#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "ft_irc.hpp"
#include "server.hpp"

#define USERLEN 15

#define STAGE_1 0
#define STAGE_2 1
#define STAGE_3 2
#define ALL_LOGIN_DATA_ENTERED 3

class Command
{
	public:
		Command(string input, Server &server);
		void printCmd();
		
		bool	PASS(Client &client);
		bool	NICK(Client &client);
		bool	USER(Client &client);
		void	PRIVMSG(std::string msg, std::string target, Client &client);
		void	JOIN(Client &client, std::string channel_name, std::string password);

		string getCmdName();

	private:
		Server &_server;
		string cmdName;
		// Client *client;
		std::vector<string> params;
		string msg;
		// Add command-specific methods as needed
};

#endif