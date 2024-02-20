#include "Headers/ft_irc.hpp"

void	test_send(int	clientSocket){
	Client	c_pchapuis(clientSocket, "pchapuis");

	c_pchapuis.setUsername("pchapuis");
	JOIN_CHANNEL(c_pchapuis, "#pp");
	

//	std::string rplNamReply = ":getServerName 353 pchapuis = channeltest :newUser\r\n";
//	std::string cmd = ":pchapuis!pchapuis@127.0.0.1 JOIN #channelTest\r\n";
	
	// if (send(clientSocket, cmd.c_str(), cmd.length(), 0) == -1)
	// {
    //    // Handle error (printing an error message, closing the socket, etc.)
    //    cerr << ("Error sending RPL_NAMREPLY");
	// }
	
	// if (send(clientSocket, rplNamReply.c_str(), rplNamReply.length(), 0) == -1)
	// {
    //    // Handle error (printing an error message, closing the socket, etc.)
    //    cerr << ("Error sending RPL_NAMREPLY");
	// }
}

void	send_msg(Client client, std::string msg){
	if (send(client.getSocket(), msg.c_str(), msg.length(), 0) == -1)
	{
       // Handle error (printing an error message, closing the socket, etc.)
       cerr << ("Error sending RPL_NAMREPLY");
	}
}