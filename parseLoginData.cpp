#include "Headers/ft_irc.hpp"

bool isUserCmdValid(string input)
{
	std::istringstream iss(input);
	string word;
	while (std::getline(iss, input))
	{
		std::istringstream tokens(input);
		tokens >> word;
		if (word == "USER")
		{
			tokens >> word;
			if (word.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ\
			abcdefghijklmnopqrstuvwxyz0123456789[]{}\\|") == std::string::npos)
				return true;
		}
	}
	return false;
}

void getLoginData(string input, Client &client, Server &server) {
	std::istringstream iss(input);
	while (std::getline(iss, input))
	{
		if (input == "CAP LS 302\r")
			continue;
		input.append("\n"); // Rajout du \n pour que ca marche avec le constructeur de cmd
		Command cmd(input, server);
		if (cmd.getCmdName() != "PASS" && cmd.getCmdName() != "NICK" && cmd.getCmdName() != "USER")
			ERR_NOTREGISTERED(client, "channel name");
		else if (client.getLoginStage() == STAGE_1)
		{
			if (cmd.getCmdName() == "PASS")
			{
				if (cmd.PASS(client))
					client.incrementLoginStage();
			}
		}
		else if (client.getLoginStage() == STAGE_2)
		{
			if (cmd.getCmdName() == "NICK")
				if (cmd.NICK(client))
					client.incrementLoginStage();
		}
		else if (client.getLoginStage() == STAGE_3)
		{
			if (cmd.getCmdName() == "USER") 
				if (cmd.USER(client))
					client.incrementLoginStage();
		}
	}
	cout << client.getLoginStage() << endl;
}

void execCMD(string input, Client &client, Server &server)
{
//	RPL_WELCOME(client, "Welcome");
	Command command(input, server);
	cout << "|"<< command.getCmdName() << "|"<< endl;
//	if (command.getCmdName() == "TEST")
//		std::cout << "test\n";
	if (command.getCmdName() == "NICK")
		command.NICK(client);
	if (command.getCmdName() == "JOIN")
		command.JOIN(client);
	if (command.getCmdName() == "INVITE")
		command.INVITE(client);
	if (command.getCmdName() == "PRIVMSG")
		command.PRIVMSG(client);
	if (command.getCmdName() == "KICK")
		command.KICK(client);
	if (command.getCmdName() == "TOPIC")
		command.TOPIC(client);
//	cout << "clients connected to coucou : " << server.getChannel("coucou").getClientMap() << endl;
}

// sera a finir d'implementer dans les Commandes de login : ERR_NEEDMOREPARAMS et ERR_NOTREGISTERED
// sera a faire : corriger nom des variables privee dans classes qui commence pas par _