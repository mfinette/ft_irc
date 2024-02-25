/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:06:24 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/25 12:31:18 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"

Client::Client(int socket) : _socket(socket), _loginStage(0)
{
	}

Client::~Client()
{
	}

Client& Client::operator=(const Client& rhs)
{
		if (this != &rhs)
	{
		_socket = rhs._socket;
		_nickname = rhs._nickname;
		_username = rhs._socket;
	}
	return *this;
}

void	Client::SendMessage(const std::string& message) {
	send(_socket, message.c_str(), message.size(), 0);
}

void	Client::setUsername(string username) {
	_username = username;
}

void	Client::setNickname(string nickname) {
	_nickname = nickname;
}

void	Client::setRealname(string realname) {
	_realname = realname;
}

void	Client::setStatus(int status) {
	_status = status;
}

void	Client::incrementLoginStage() {
	_loginStage++;
}

int	Client::getLoginStage() {
	return _loginStage;
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

int		Client::getStatus() const{
	return _status;
}

std::ostream	&operator<<(std::ostream &o, const Client &client) {
	o << client.getNickname();
	return o;
}