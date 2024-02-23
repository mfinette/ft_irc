#include "../Headers/ft_irc.hpp"

void	send_msg(Client client, std::string msg){
	if (send(client.getSocket(), msg.c_str(), msg.length(), 0) == -1)
	{
		// Handle error (printing an error message, closing the socket, etc.)
		cerr << ("Error sending RPL_NAMREPLY");
	}
}

void	Command::PRIVMSG(std::string msg, std::string target, Client &client){
	if (!_server.isClientLog(target) && !_server.channelExisting(target)) //si ce n'est ni un client, ni un serveur ==> ERR pas de client avec ce nick
		return ERR_NOSUCHNICK(client, target);
	if (!_server.isClientLog(target)){ //si ce n'est pas un client alors c'est un serveur
		//check du moderate mode
		std::cout << "\n\n\n\n\nJESUISLAAALALLALALA et j'envoi " << "a la target: " << target << "\n\n\n\n";
		Channel tmp = _server.getChannel(target);
		tmp.SendMessageToChannel(this->msg);
		//envoie du msg a ts les users du channel
		ERR_CANNOTSENDTOCHAN(client, "thischannel"); //si le msg n'as pas pu etre envoyer
		return;
	}
	if (!_server.getClientStatus(target)) //si le status du client est sur away
		RPL_AWAY(client, "targetTest", ":The user is currently away");
	Client client_target = _server.getClient(target);
	std::string message = ":" + client.getNickname() + " PRIVMSG " + client_target.getNickname() + " :" + msg;
	send_msg(client_target, message);
}
