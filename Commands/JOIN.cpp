/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:58:20 by maxime            #+#    #+#             */
/*   Updated: 2024/02/26 17:04:44 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/ft_irc.hpp"

void	Channel::updateClientList(){
	std::map<Client *, bool>::iterator it_client;
	
	for(it_client = _client.begin(); it_client != _client.end(); ++it_client){
		Client client_to	= *it_client->first;
		std::map<Client *, bool>::iterator it;
		std::string	server_name = "IRC 42";
		std::string msg = HEADER(client_to) + " 353 " + client_to.getNickname() + " = " + getName() + " :";
		for(it = _client.begin(); it != _client.end(); ++it){
			if (it->second)
				msg += "@";
			msg += it->first->getNickname();
			msg += " ";
		}
		msg.erase(msg.size() - 1);
		msg += "\r\n";
		send_msg(client_to, msg);
		RPL_ENDOFNAMES(client_to, getName());
	}
}

void	Command::JoinServeur(Client& client, Channel& channel){
	JOIN_CHANNEL(client, channel.getName());
	channel.AddClientToChannel(&client);
	if (channel.getTopic().size() != 0){ //si il y a un topic
		RPL_TOPIC(client, channel.getName(), channel.getTopic());
		RPL_TOPICWHOTIME(client, channel.getName(), channel.getTopicAuthor(), channel.getSetAt());
	}
	else
		RPL_NOTOPIC(client, channel.getName());
	channel.updateClientList();
}

void	Command::JOIN(Client &client){
	if (params.size() < 1)
		return ERR_NEEDMOREPARAMS(client, "JOIN");
	std::vector<string> channel_list = splitWithComa(params[0]);
	std::vector<string> key_list;
	if (params.size() > 1)
		key_list = splitWithComa(params[1]);
	for (unsigned int i = 0; i < channel_list.size(); i++){
		if (_server.channelExisting(channel_list[i])){ //si le channel existe
			Channel& channel = _server.getChannel(channel_list[i]);
			if (channel.isInviteOnly()) //si c'est en invite only
				return ERR_INVITEONLYCHAN(client, channel.getName());
			if (channel.getUserLimit() != -1 && channel.getUserLimit() <= channel.nbClient()) //si la user limit est presente et si elle n'as pas ete depasser
				return ERR_CHANNELISFULL(client, channel.getName());
			if (channel.hasPassword() && key_list.size() > i && channel.getPassword() != key_list[i]) //si le password n'est pas valide et il faut check si une key est bien donner
				return ERR_BADCHANNELKEY(client, channel.getName());			
			cout << "join serveur \n";
			JoinServeur(client, channel);
		}
		else
		{
			Channel new_channel(channel_list[i]);
			new_channel.AddClientToChannel(&client);
			new_channel.changeOperatorStatusToOn(client.getSocket());
			_server.addChannelToServer(new_channel);
			JOIN_CHANNEL(client, new_channel.getName());
			new_channel.updateClientList();
			RPL_NOTOPIC(client, new_channel.getName());
		}
	}
}
