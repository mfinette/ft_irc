#include "../Headers/ft_irc.hpp"


void	Command::INVITE(Client &client, std::string target, std::string channel_name){
	//si pas de parametres ==> RPL_INVITELIST (aka. la liste des channel ds lesquels ce client est invite)
	//si pas d'argument ==> ERR_NEEDMOREPARAMS
	if (params.size() == 0) //si pas de parametres affiches la liste de channel ds lesquels le client est invite
		return RPL_INVITELIST(client, "channel_list");
	if (!_server.channelExisting(channel_name))// si le channel n'existe pas
		return ERR_NOSUCHCHANNEL(client, channel_name);
	Channel channel = _server.getChannel(channel_name);
	if (!channel.isClientInChannel(client.getSocket())) //si le client n'est pas sur le serveur
		return ERR_NOTONCHANNEL(client, channel_name);
	if (channel.isInviteOnly() && !channel.isOperator(client.getSocket())) //si invite only et pas les droit de kick
		return ERR_CHANOPRIVSNEEDED(client, channel_name);
	if (!_server.isClientLog(target))
		return ERR_NOSUCHNICK(client, target);
	if (channel.isClientInChannel(_server.getClient(target).getSocket())) //si la target a invite est deja sur le channel
		return ERR_USERONCHANNEL(client, target, channel_name);
	
	
	//conditions remplies
	RPL_INVITING(client, target, channel_name); //send to notify the client that the request as succeed

	// and an INVITE msg withe client as source

}
