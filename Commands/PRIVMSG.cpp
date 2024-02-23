#include "../Headers/ft_irc.hpp"

void	send_msg(Client client, std::string msg){
	if (send(client.getSocket(), msg.c_str(), msg.length(), 0) == -1)
	{
		// Handle error (printing an error message, closing the socket, etc.)
		cerr << ("Error sending RPL_NAMREPLY");
	}
}

void	Command::PRIVMSG(Client &client){
	if (!_server.isClientLog(this->params[0]) && !_server.channelExisting(this->params[0])) //si ce n'est ni un client, ni un serveur ==> ERR pas de client avec ce nick
		return ERR_NOSUCHNICK(client, this->params[0], "nick/channel");
	if (!_server.isClientLog(this->params[0])){ //si ce n'est pas un client alors c'est un serveur
		//check du moderate mode

		Channel tmp = _server.getChannel(this->params[0]);
		tmp.SendMessageToChannel(this->msg, this->params[0], client.getSocket());

	//	ERR_CANNOTSENDTOCHAN(client, "thischannel"); //si le msg n'as pas pu etre envoyer
		return;
	}
	if (!_server.getClientStatus(this->params[0])) //si le status du client est sur away
		RPL_AWAY(client, "targetTest", ":The user is currently away");
	Client client_target = _server.getClient(this->params[0]);
	std::string message = ":" + client.getNickname() + " PRIVMSG " + client_target.getNickname() + " :" + msg;
	send_msg(client_target, message);
}
