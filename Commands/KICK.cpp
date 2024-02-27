#include "../Headers/ft_irc.hpp"

void	Command::KICK(Client &client){
	if (params.size() < 2)
		return ERR_NEEDMOREPARAMS(client, "KICK");
	std::vector<string> client_list = splitWithComa(params[1]);
	std::vector<string> comment_list = splitWithComa(msg);
	if (!_server.channelExisting(this->params[0]))// si le channel n'existe pas
		return ERR_NOSUCHCHANNEL(client, this->params[0]);
	Channel &channel = _server.getChannel(this->params[0]);
	for (unsigned int i = 0; i < client_list.size(); i++){
		if (!channel.isOperator(client.getSocket())){ //si pas les droit de kick
			ERR_CHANOPRIVSNEEDED(client, channel.getName());
			continue;
		}
		if (!_server.isClientLog(client_list[i])){ //si la target n'est pas sur le serveur
			ERR_NOSUCHNICK(client, client_list[i], "nick");
			continue;
		}
		if (!channel.isClientInChannel(_server.getClient(client_list[i]).getSocket())){ //si la target a kick est bien sur le channel
			ERR_USERNOTINCHANNEL(client, client_list[i], channel.getName());
			continue;
		}
		if (!channel.isClientInChannel(client.getSocket())){ //si le client n'est pas sur le serveur
			ERR_NOTONCHANNEL(client, channel.getName());
			continue;
		}
		//ttes les conditions sont remplies
		Client &client_target = _server.getClient(client_list[i]);
		std::string msg = ":" + client.getNickname() + " KICK " + channel.getName() + " " + client_target.getNickname() + " ";
		if (comment_list.size() > i)
			msg += comment_list[i];
		msg += "\r\n";
		send_msg(client_target, msg);
		channel.RemoveClientFromChannel(&client_target);
		if (channel.nbClient() == 0)
			_server.removeChannelFromServer(channel);
		if (channel.nbOperator() == 0)
			channel.setNewOperator();
		channel.updateClientList();
	}
}

//peut etre mettre une limite sur le nombre de kick en une commande