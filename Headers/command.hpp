#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "ft_irc.hpp"
#include "server.hpp"

class Command
{
	public:
		static void ParseAndExecute(const std::string& command, User* user, Server* server);
	private:
		// Add command-specific methods as needed
};

#endif