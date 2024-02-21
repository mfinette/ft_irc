#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "ft_irc.hpp"
#include "server.hpp"

#define USERLEN 15

#define NOTHING_VALIDATED 0
#define PASS_VALIDATED 1
#define NICK_VALIDATED 2
#define ALL_LOGIN_DATA_ENTERED 3

class Command
{
	public:
		Command(string input, Server &server);
		void printCmd();
		
		void	PRIVMSG(std::string msg, std::string target, Client &client);
		void	JOIN(Client &client, std::string channel_name, std::string password);
		void	NICK(Client &client);

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