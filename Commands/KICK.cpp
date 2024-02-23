#include "../Headers/ft_irc.hpp"

void	Command::KICK(Client &client){
	if (params.size() <= 1)
		return ERR_NEEDMOREPARAMS(client, "KICK");
	if (!_server.channelExisting(this->params[0]))// si le channel n'existe pas
		return ERR_NOSUCHCHANNEL(client, this->params[0]);
	Channel &channel = _server.getChannel(this->params[0]);
	if (!channel.isOperator(client.getSocket())) //si pas les droit de kick
		return ERR_CHANOPRIVSNEEDED(client, channel.getName());
	if (!_server.isClientLog(this->params[1])) //si la target n'est pas sur le serveur
		return ERR_NOSUCHNICK(client, this->params[1], "nick");
	if (!channel.isClientInChannel(_server.getClient(this->params[1]).getSocket())) //si la target a kick est bien sur le channel
		return ERR_USERNOTINCHANNEL(client, this->params[1], channel.getName());
	if (!channel.isClientInChannel(client.getSocket())) //si le client n'est pas sur le serveur
		return ERR_NOTONCHANNEL(client, channel.getName());
	//ttes les conditions sont remplies
	//possibilite de kick plusieurs user a la fois
	Client &client_target = _server.getClient(this->params[1]);
	std::string msg = ":" + client.getNickname() + " KICK " + channel.getName() + " " + client_target.getNickname() + " " + this->msg + "\r\n";
	send_msg(client_target, msg);
	channel.RemoveClientFromChannel(&client_target);
}