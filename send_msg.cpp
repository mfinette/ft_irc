#include "Headers/ft_irc.hpp"

void	test_send(int	clientSocket)
{
	Client	c_pchapuis(clientSocket);
	c_pchapuis.setUsername("pchapuis");
	
	RPL_WELCOME(c_pchapuis, "Welcome");
//	JOIN_CHANNEL(c_pchapuis, "#pp");
//	RPL_NameReply(c_pchapuis, ":newUser");
}

void	send_msg(Client client, std::string msg)
{
	if (send(client.getSocket(), msg.c_str(), msg.length(), 0) == -1)
		cerr << ("Error sending RPL_NAMREPLY");
	// Handle error (printing an error message, closing the socket, etc.)
}