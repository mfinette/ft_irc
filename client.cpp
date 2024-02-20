/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:06:24 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/20 18:22:35 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"

Client::Client(int socket, const std::string& nickname) : _socket(socket) , _nickname(nickname)
{
}

Client::~Client()
{
}

Client& Client::operator=(const Client& rhs){
	if (this != &rhs){
		_socket = rhs._socket;
		_nickname = rhs._nickname;
		_username = rhs._socket;
	}
	return *this;
}

void Client::SendMessage(const std::string& message)
{
	send(_socket, message.c_str(), message.size(), 0);
}

void	Client::setUsername(string username){
	_username = username;
}

void	Client::setNickname(string nickname){
	_nickname = nickname;
}

int		Client::getSocket() const{
	return	_socket;
}

string	Client::getNickname() const{
	return _nickname;
}

string	Client::getUsername() const{
	return _username;
}

std::ostream	&operator<<(std::ostream &o, const Client &client)
{
	o << client.getNickname();
	return o;
}