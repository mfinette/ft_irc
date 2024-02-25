/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientChannelManagement.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:05:45 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/25 13:19:46 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"

void	Server::setupClient(int socket)
{
		Client newClient(socket);
	newClient.setNickname("");
	newClient.setUsername("");
	newClient.setRealname("");
		this->addClientToServer(newClient);
	}

void	Server::addClientToServer(const Client& client)
{
		this->_clientList.insert(std::pair<int, Client>(client.getSocket(), client));
	}

void	Server::removeClientFromServer(Client& client)
{
		_clientList.erase(_clientList.find(client.getSocket()));
}

void	Server::addChannelToServer(Channel& channel)
{
	_channelList.insert(std::pair<std::string, Channel>(channel.getName(), channel));
}

void	Server::removeChannelFromServer(Channel& channel)
{
	_channelList.erase(_channelList.find(channel.getName()));
}
