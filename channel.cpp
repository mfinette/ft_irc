/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:01:53 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/15 19:32:05 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Channel::Channel(const string& name) : _name(name)
{
}

Channel::~Channel()
{
}

void	Channel::AddUser(User* user)
{
	(void)user;
	// Add user to channel
}

void	Channel::RemoveUser(User* user)
{
	(void)user;
	// Remove user from channel
}

void	Channel::SendMessage(const string& message)
{
	(void)message;
	// Send message to all users in channel
}