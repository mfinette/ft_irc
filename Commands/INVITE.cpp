#include "../Headers/ft_irc.hpp"

void	Command::INVITE(Client &client){
	if (params.size() <= 1) //si pas de parametres => err param
		return ERR_NEEDMOREPARAMS(client, "INVITE");
	if (!_server.channelExisting(this->params[1]))// si le channel n'existe pas
		return ERR_NOSUCHCHANNEL(client, this->params[1]);
	Channel &channel = _server.getChannel(this->params[1]);
	if (!channel.isClientInChannel(client.getSocket())) //si le client n'est pas sur le serveur
		return ERR_NOTONCHANNEL(client, channel.getName());
	if (channel.isInviteOnly() && !channel.isOperator(client.getSocket())) //si invite only et pas les droit de kick
		return ERR_CHANOPRIVSNEEDED(client, channel.getName());
	if (!_server.isClientLog(this->params[0]))
		return ERR_NOSUCHNICK(client, this->params[0], "nick");
	Client &client_target = _server.getClient(this->params[0]);
	if (channel.isClientInChannel(client_target.getSocket())) //si la target a invite est deja sur le channel
		return ERR_USERONCHANNEL(client, client_target.getNickname(), channel.getName());
	//conditions remplies
	RPL_INVITING(client, client_target.getNickname(), channel.getName()); //send to notify the client that the request as succeed
	std::string msg = ":" + client.getNickname() + " INVITE " + client_target.getNickname() + " :" + channel.getName() + "\r\n";
	send_msg(client_target, msg);
	JoinServeur(client_target, channel);
}
