#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "ft_irc.hpp"
#include "server.hpp"

#define USERLEN 15

#define NOTHINGVALIDATED 0
#define PASSVALIDATED 1
#define NICKVALIDATED 2
#define ALLLOGINDATAENTERED 3

class Command
{
	public:
		Command(string input, Server &server);
		void printCmd();
		
		void execNICK(Client &client);

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