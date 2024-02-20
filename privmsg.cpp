#include "Headers/ft_irc.hpp"

// target is a string, can be the nickname of a client or the name of a channel

//For a channel:
//if client banned from it and not covered by ban exception -> msg not send and silently fail
// moderate mode active can block msg from certin user
// some mode can also block or modify the msg see: https://modern.ircdocs.horse/#privmsg-message
//If a message cannot be delivered to a channel, the server SHOULD respond with an 
//ERR_CANNOTSENDTOCHAN (404) numeric to let the user know that this message could not be delivered.

//If <target> is a channel name, it may be prefixed with one or more channel membership prefix character (@, +, etc) 
//and the message will be delivered only to the members of that channel with the given or higher status in the channel. 


//For a target:
//If <target> is a user and that user has been set as away, the server may reply with an 
//RPL_AWAY (301) numeric and the command will continue.

void	Server::privmsg(std::string msg, int target, int from){
	Client client_target = this->getClientWithSocket(target);
	Client client_from = this->getClientWithSocket(from);
	
	std::string message = ":" + client_from.getNickname() + " PRIVMSG " + client_target.getNickname() + " :" + msg;
	send_msg(client_target, message);
}