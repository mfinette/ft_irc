/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:01:53 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/20 16:23:43 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"

Channel::Channel(const string& name) : _name(name), _user_limit(-1), _invite_only(false), _has_password(false){
	(void)_user_limit;
	(void)_invite_only;
	(void)_has_password;
}

Channel::~Channel(){
}

void	Channel::AddClient(Client* client){
	(void)client;
	// Add Client to channel
}

void	Channel::RemoveClient(Client* client)
{
	(void)client;
	// Remove Client from channel
}

void	Channel::SendMessage(const string& message)
{
	(void)message;
	// Send message to all users in channel
}

bool	Channel::isOperator(int socket){
	std::map<Client *, bool>::iterator it;

	for(it = _client.begin(); it != _client.end(); ++it){
		if (it->first->getSocket() == socket){
			return it->second;
		}
	}
	std::cout << "not found" << std::endl;
	return false;
}

void	Channel::changeOperatorStatusToOff(int socket){
	std::map<Client *, bool>::iterator it;

	for(it = _client.begin(); it != _client.end(); ++it){
		if (it->first->getSocket() == socket){
			it->second = false;
			break;
		}
	}
}

void	Channel::changeOperatorStatusToOn(int socket){
	std::map<Client *, bool>::iterator it;

	for(it = _client.begin(); it != _client.end(); ++it){
		if (it->first->getSocket() == socket){
			it->second = true;
			break;
		}
	}
}

void	Channel::changeUserLimit(int user_limit){
	_user_limit = user_limit;
}

void	Channel::changeInviteOnlyStatusToOn(){
	_invite_only = true;
}

void	Channel::changeInviteOnlyStatusToOff(){
	_invite_only = false;
}

void	Channel::changePasswordStatusToOn(){
	_has_password = true;
}

void	Channel::changePasswordStatusToOff(){
	_has_password = false;
}


