/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:06:24 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/19 14:00:06 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"

Client::Client(int socket, const std::string& nickname) : _socket(socket) , _nickname(nickname)
{
}

Client::~Client()
{
}

void Client::SendMessage(const std::string& message)
{
	send(_socket, message.c_str(), message.size(), 0);
}

