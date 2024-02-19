/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:01:53 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/19 17:39:31 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"

Channel::Channel(const string& name) : _name(name), _user_limit(-1), _invite_only(false), _has_password(false)
{
	(void)_user_limit;
	(void)_invite_only;
	(void)_has_password;
}

Channel::~Channel()
{
}

void	Channel::AddUser(Client* client)
{
	(void)client;
	// Add user to channel
}

void	Channel::RemoveUser(Client* client)
{
	(void)client;
	// Remove user from channel
}

void	Channel::SendMessage(const string& message)
{
	(void)message;
	// Send message to all users in channel
}