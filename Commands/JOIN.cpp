/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:58:20 by maxime            #+#    #+#             */
/*   Updated: 2024/02/23 16:21:19 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/ft_irc.hpp"

void	Command::JOIN(Client &client){
	if (_server.channelExisting(this->params[0])){ //si le channel existe
		Channel& channel = _server.getChannel(this->params[0]);
		if (channel.isInviteOnly()) //si c'est en invite only
			return ERR_INVITEONLYCHAN(client, this->params[0]);
		if (channel.getUserLimit() != -1 && channel.getUserLimit() <= channel.nbClient()) //si la user limit est presente et si elle n'as pas ete depasser
			return ERR_CHANNELISFULL(client, this->params[0]);
		if (channel.getPassword() != this->params[1]) //si le password n'est pas valide
			return ERR_BADCHANNELKEY(client, this->params[0]);
			
		JOIN_CHANNEL(client, this->params[0]);
		channel.AddClientToChannel(&client);
	//	channel.printList();
		
		if (channel.getTopic().size() == 0) //si il n'y a pas de topic
			return RPL_NOTOPIC(client, this->params[0]);
		RPL_TOPIC(client, this->params[0], channel.getTopic());
		RPL_TOPICWHOTIME(client, this->params[0], channel.getTopicAuthor(), channel.getSetAt());
	}
	else
	{
		Channel new_channel(this->params[0]);
		new_channel.AddClientToChannel(&client);
		_server.addChannelToServer(this->params[0], new_channel);
		JOIN_CHANNEL(client, this->params[0]);
	}
}
