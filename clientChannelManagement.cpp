/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientChannelManagement.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:05:45 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/22 13:56:21 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"

void	Server::setupClient(int socket)
{
	Client newClient(socket);
	newClient.setNickname("unknown");
	newClient.setUsername("unknown");
	newClient.setRealname("unknown");
	this->addClientToServer(newClient);
}

void	Server::addClientToServer(Client& client)
{
	this->_clientList.insert(std::pair<int, Client>(client.getSocket(), client));
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
	(void)channel;
}
