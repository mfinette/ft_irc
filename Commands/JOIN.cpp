/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:58:20 by maxime            #+#    #+#             */
/*   Updated: 2024/02/23 15:10:55 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/ft_irc.hpp"

void	Command::JOIN(Client &client, std::string channel_name, std::string password){
	if (_server.channelExisting(channel_name)){ //si le channel existe
		Channel channel = _server.getChannel(channel_name);
		if (channel.isInviteOnly()) //si c'est en invite only
			return ERR_INVITEONLYCHAN(client, channel_name);
		if (channel.getUserLimit() != -1 && channel.getUserLimit() <= channel.nbClient()) //si la user limit est presente et si elle n'as pas ete depasser
			return ERR_CHANNELISFULL(client, channel_name);
		if (channel.getPassword() != password) //si le password n'est pas valide
			return ERR_BADCHANNELKEY(client, channel_name);
		JOIN_CHANNEL(client, channel_name);
		channel.AddClientToChannel(&client);
		if (channel.getTopic().size() == 0) //si il n'y a pas de topic
			return RPL_NOTOPIC(client, channel_name);
		RPL_TOPIC(client, channel_name, channel.getTopic());
		RPL_TOPICWHOTIME(client, channel_name, channel.getTopicAuthor(), channel.getSetAt());
	}
	else
	{
		Channel new_channel(channel_name);
		std::cout << "channel not existing\n";
		new_channel.AddClientToChannel(&client);
		_server.addChannelToServer(channel_name, new_channel);
		JOIN_CHANNEL(client, channel_name);
	}
}
