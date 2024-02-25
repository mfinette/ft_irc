#include "Headers/ft_irc.hpp"

void getLoginData(string input, Client &client, Server &server) {
	std::istringstream iss(input);
	while (std::getline(iss, input))
	{
		if (input == "CAP LS 302\r")
			continue;
		Command cmd(input, server);
		if (cmd.getCmdName() != "PASS" && cmd.getCmdName() != "NICK" && cmd.getCmdName() != "USER" && cmd.getCmdName() != "")
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
				if (cmd.USER(client)) {
					client.incrementLoginStage();
					cout << COLOR_1 << "\nUSER ("  << COLOR_2 << client.getSocket()  << COLOR_1 << ") SUCCESSFULLY LOGGED AS : " << COLOR_2 << client.getNickname() << COLOR_1 << " !" << RESET;
				}
		}
	}
}

void execCMD(string input, Client &client, Server &server)
{
//	RPL_WELCOME(client, "Welcome");
	Command command(input, server);
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