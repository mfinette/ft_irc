/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientChannelManagement.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:05:45 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/21 18:43:00 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"

void	Server::addClientToServer(int socket, Client& client, std::string nickname)
{
	_clientList.insert(std::pair<int, Client>(socket, client));
	_clientList[socket].setNickname(nickname);
}

void	Server::removeClientFromServer(Client& client)
{
	_clientList.erase(_clientList.find(client.getSocket()));
}

void	Server::addChannelToServer(std::string name, Channel& channel)
{
	_channelList.insert(std::pair<std::string, Channel>(name, channel));
}

void	Server::removeChannelFromServer(std::string name, Channel& channel)
{
	_channelList.erase(_channelList.find(name));
}
