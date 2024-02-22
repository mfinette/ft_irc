#include "../Headers/ft_irc.hpp"

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

void	Command::PRIVMSG(std::string msg, std::string target, Client &client){
	if (_server.isClientAway(target) && !_server.channelExisting(target)){
	 	RPL_AWAY(client, "targetTest", ":The user is currently away");
	 	return;
	}
	//if the msg cannot be delivered to the channel
	if (_server.isClientAway(target)){
		ERR_CANNOTSENDTOCHAN(client, "thischannel");
		return;
	}
	Client client_target = _server.getClient(target);
	std::string message = ":" + client.getNickname() + " PRIVMSG " + client_target.getNickname() + " :" + msg;
	send_msg(client_target, message);
}

//si client et serveur n'existe pas ==> msg client pas trouver

//si client trouver ==> essayer d'envoyer un msg vers le client

//si client pas trouver ==> alors envoie msg vers un channel


