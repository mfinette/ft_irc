#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "ft_irc.hpp"
#include "server.hpp"

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
		// Server *server;
		std::vector<string> params;
		string msg;
		// Add command-specific methods as needed
};

#endif