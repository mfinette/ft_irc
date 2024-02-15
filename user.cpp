/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:06:24 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/15 19:04:19 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

User::User(int socket, const std::string& nickname) : _socket(socket) , _nickname(nickname)
{
}

User::~User()
{
}

void User::SendMessage(const std::string& message)
{
	send(_socket, message.c_str(), message.size(), 0);
}

