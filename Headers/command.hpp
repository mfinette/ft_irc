#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "ft_irc.hpp"
#include "server.hpp"

class Command
{
	public:
		Command(string input);
		Command parseMsgToCmd(string input);
		void printCmd();

	private:
		string prefix;
		string cmdName;
		// User *user;
		// Server *server;
		std::vector<string> params;
		string msg;
		// Add command-specific methods as needed
};

#endif