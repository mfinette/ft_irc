#include "../Headers/ft_irc.hpp"

void	Command::QUIT(Client &client)
{
	if (msg != "")
		QUIT_SERVER(client, msg);
	//QUIT
}