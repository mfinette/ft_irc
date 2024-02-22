/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:01:53 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/22 14:17:04 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"

std::ostream& operator<<(std::ostream& os, const Channel& channel)
{
	os << "Channel name: " << channel.getName() << std::endl;
	return os;
}

Channel::Channel(const string& name) : _name(name), _user_limit(-1), _invite_only(false), _has_password(false)
{
	(void)_user_limit;
	(void)_invite_only;
	(void)_has_password;
}

Channel::~Channel()
{
}

void	Channel::AddClientToChannel(Client* client)
{
	// Add Client to channel
	_client.insert(std::pair<Client *, bool>(client, false));
}

void	Channel::RemoveClientFromChannel(Client* client)
{
	// Remove Client from channel
	_client.erase(_client.find(client));
}

void	Channel::SendMessage(const string& message)
{
	(void)message;
	// Send message to all users in channel
}

bool	Channel::isOperator(int socket)
{
	std::map<Client *, bool>::iterator it;

	for(it = _client.begin(); it != _client.end(); ++it)
	{
		if (it->first->getSocket() == socket)
			return it->second;
	}
	std::cout << "not found" << std::endl;
	return false;
}

std::string	Channel::getName() const
{
	return _name;
}

std::string	Channel::getTopic()
{
	return _topic;
}

std::string	Channel::getPassword()
{
	return _password;
}

bool	Channel::isInviteOnly()
{
	return _invite_only;
}

bool	Channel::hasPassword()
{
	return _has_password;
}

int	Channel::getUserLimit()
{
	return _user_limit;
}

int	Channel::nbClient()
{
	return _client.size();
}

void	Channel::changeOperatorStatusToOff(int socket)
{
	std::map<Client *, bool>::iterator it;

	for(it = _client.begin(); it != _client.end(); ++it)
	{
		if (it->first->getSocket() == socket)
		{
			it->second = false;
			break;
		}
	}
}

void	Channel::changeOperatorStatusToOn(int socket)
{
	std::map<Client *, bool>::iterator it;

	for(it = _client.begin(); it != _client.end(); ++it)
	{
		if (it->first->getSocket() == socket)
		{
			it->second = true;
			break;
		}
	}
}

void	Channel::changeUserLimit(int user_limit)
{
	_user_limit = user_limit;
}

void	Channel::changeInviteOnlyStatusToOn()
{
	_invite_only = true;
}

void	Channel::changeInviteOnlyStatusToOff()
{
	_invite_only = false;
}

void	Channel::changePasswordStatusToOn()
{
	_has_password = true;
}

void	Channel::changePasswordStatusToOff()
{
	_has_password = false;
}
