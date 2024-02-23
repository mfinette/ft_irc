/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/23 13:47:39 by pchapuis         ###   ########.fr       */
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
}

Channel::~Channel()
{
}

void	Channel::AddClientToChannel(Client* client)
{
	_client.insert(std::pair<Client *, bool>(client, false));
}

void	Channel::RemoveClientFromChannel(Client* client)
{
	_client.erase(_client.find(client));
}

void	Channel::SendMessageToChannel(const string& message)
{
	// Send message to all users in channel
	for (std::map<Client *, bool>::iterator it = _client.begin(); it != _client.end(); ++it)
		send(it->first->getSocket(), message.c_str(), message.size(), 0);
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

std::string	Channel::getTopicAuthor()
{
	return _topic_author;
}

std::string	Channel::getPassword()
{
	return _password;
}

std::string	Channel::getSetAt()
{
	std::string timeString;
	const int bufferSize = 20; // Sufficient size for a Unix timestamp
	char buffer[bufferSize];

	// Use std::strftime to format the time
	if (std::strftime(buffer, bufferSize, "%Y-%m-%d %H:%M:%S", std::localtime(&_setAt)))
		timeString = buffer;
	return timeString;
}

bool	Channel::isInviteOnly()
{
	return _invite_only;
}

bool	Channel::hasPassword()
{
	return _has_password;
}

bool	Channel::hasTopicRestriction(){
	return _topic_restriction;
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

void	Channel::setTopic(std::string topic){
	_topic = topic;
}

void	Channel::setTopicAuthor(std::string nickname){
	_topic_author = nickname;
}

bool	Channel::isClientInChannel(int socket)
{
	std::map<Client *, bool>::iterator it;

	for(it = _client.begin(); it != _client.end(); ++it)
		if (it->first->getSocket() == socket)
			return true;
	return false;
}