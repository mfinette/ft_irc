#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "ft_irc.hpp"
#include "server.hpp"

class Command
{
	public:
		Command() : last_param(""){};
		Command parseMsgToCmd(string input);
		static void parseCmd(Command command);

	private:
		string cmdName;
		User *user;
		Server *server;
		std::vector<string> params;
		string last_param;
		// Add command-specific methods as needed
};

#endif