/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:58:20 by maxime            #+#    #+#             */
/*   Updated: 2024/02/29 16:46:25 by cgelin           ###   ########.fr       */
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

void	Server::leaveAll(Client &client){
	std::map<std::string, Channel>::iterator it;
	
	for(it = _channelList.begin(); it != _channelList.end(); ++it){
		Channel &channel = it->second;
		if (channel.isClientInChannel(client.getSocket())){
			std::string msg = ":" + client.getNickname() + " PART " + channel.getName() + " \r\n";
			send_msg(client, msg);
			channel.RemoveClientFromChannel(&client);
			if (channel.nbClient() == 0)
				return removeChannelFromServer(channel);
			if (channel.nbOperator() == 0)
			 	channel.setNewOperator();
			channel.updateClientList();
		}
	}
}

bool	checkChannelName(std::string name){
	if (name[0] != '#')
		return false;
	for (std::string::size_type i = 0; i < name.length(); ++i)
        if (name[i] == 7) //code Ascii de ^G
			return false;
	return true;
}

void	Command::JOIN(Client &client){
	if (params.size() < 1)
		return ERR_NEEDMOREPARAMS(client, "JOIN");
	std::vector<string> channel_list = splitWithComa(params[0]);
	std::vector<string> key_list;
	if (params.size() > 1)
		key_list = splitWithComa(params[1]);
	for (unsigned int i = 0; i < channel_list.size(); i++){
		if (channel_list[0] == "0"){ //part sur tous les channels
			_server.leaveAll(client);
		}
		else if (_server.channelExisting(channel_list[i])){ //si le channel existe
			Channel& channel = _server.getChannel(channel_list[i]);
			if (channel.isInviteOnly()){ //si c'est en invite only
				ERR_INVITEONLYCHAN(client, channel.getName());
				continue;
			}
			if (channel.getUserLimit() != -1 && channel.getUserLimit() <= channel.nbClient()){ //si la user limit est presente et si elle n'as pas ete depasser
				ERR_CHANNELISFULL(client, channel.getName());
				continue;
			}
			if (channel.hasPassword()){
				if	(key_list.size() <= i || channel.getPassword() != key_list[i]){ //si le password n'est pas valide et il faut check si une key est bien donner
					ERR_BADCHANNELKEY(client, channel.getName());			
					continue;
				}
			}
			JoinServeur(client, channel);
			
		}
		else
		{
			if (!checkChannelName(channel_list[i]))
				return;
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

