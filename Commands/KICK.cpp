#include "../Headers/ft_irc.hpp"

void	Command::KICK(Client &client, std::string channel_name, std::string target, std::string reason){
	if (params.size() == 0)
		return ERR_NEEDMOREPARAMS(client, "KICK");
	if (!_server.channelExisting(channel_name))// si le channel n'existe pas
		return ERR_NOSUCHCHANNEL(client, channel_name);
	Channel channel = _server.getChannel(channel_name);
	if (!channel.isOperator(client.getSocket())) //si pas les droit de kick
		return ERR_CHANOPRIVSNEEDED(client, channel_name);
	if (!_server.isClientLog(target)) //si la target n'est pas sur le serveur
		return ERR_NOSUCHNICK(client, target);
	if (!channel.isClientInChannel(_server.getClient(target).getSocket())) //si la target a kick est bien sur le channel
		return ERR_USERNOTINCHANNEL(client, target, channel_name);
	if (!channel.isClientInChannel(client.getSocket())) //si le client n'est pas sur le serveur
		return ERR_NOTONCHANNEL(client, channel_name);

	//ttes les conditions sont remplies
	//kick
	//possibilite de kick plusieurs user a la fois

	//kick avec commentaire special ou nn
}