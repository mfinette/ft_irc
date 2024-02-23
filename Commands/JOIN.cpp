/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:58:20 by maxime            #+#    #+#             */
/*   Updated: 2024/02/23 18:02:03 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/ft_irc.hpp"

void	Command::JoinServeur(Client& client, Channel& channel){
	JOIN_CHANNEL(client, channel.getName());
	channel.AddClientToChannel(&client);
	if (channel.getTopic().size() == 0) //si il n'y a pas de topic
		return RPL_NOTOPIC(client, channel.getName());
	RPL_TOPIC(client, channel.getName(), channel.getTopic());
	RPL_TOPICWHOTIME(client, channel.getName(), channel.getTopicAuthor(), channel.getSetAt());
}

void	Command::JOIN(Client &client){
	if (_server.channelExisting(this->params[0])){ //si le channel existe
		Channel& channel = _server.getChannel(this->params[0]);
		if (channel.isInviteOnly()) //si c'est en invite only
			return ERR_INVITEONLYCHAN(client, channel.getName());
		if (channel.getUserLimit() != -1 && channel.getUserLimit() <= channel.nbClient()) //si la user limit est presente et si elle n'as pas ete depasser
			return ERR_CHANNELISFULL(client, channel.getName());
		if (channel.hasPassword() && channel.getPassword() != this->params[1]) //si le password n'est pas valide
			return ERR_BADCHANNELKEY(client, channel.getName());			
		JoinServeur(client, channel);
	}
	else
	{
		Channel new_channel(this->params[0]);
		new_channel.AddClientToChannel(&client);
		new_channel.changeOperatorStatusToOn(client.getSocket());
		_server.addChannelToServer(new_channel);
		JOIN_CHANNEL(client, new_channel.getName());
	}
}
