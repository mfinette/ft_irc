/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:58:20 by maxime            #+#    #+#             */
/*   Updated: 2024/02/22 21:58:21 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/ft_irc.hpp"

//quand on join un serveur si il n'existe pas, on le creer et on devient l'admin
// si il existe deja, on check si invite only
// puis la user limit
// puis la key

void	Command::JOIN(Client &client, std::string channel_name, std::string password)
{
	if (_server.channelExisting(channel_name))
	{
		Channel channel = _server.getChannel(channel_name);
		if (!channel.isInviteOnly())
		{
			if (channel.getUserLimit() > channel.nbClient())
			{
					if (channel.getPassword() == password)
						JOIN_CHANNEL(client, channel_name);
					else
						ERR_BADCHANNELKEY(client, channel_name);
			}
			else
				ERR_CHANNELISFULL(client, channel_name);
		}
		else
			ERR_INVITEONLYCHAN(client, channel_name);
	}
	else
	{
		std::cout << "channel not existing\n";
		//need to create the channel
	}
}