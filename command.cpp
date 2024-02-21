/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:04:42 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/21 15:27:21 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"

// std::string assemble_msg(std::string servName, std::string msg, std::string nickname, std::string code) { 
// 	return std::string(":" + servName + " " + getcode(msg) + " " + nickname + " ");
// }

//Parse input of hexchat into a "command" object,
//the msg variable is filled if there's a message at the end of the input.
Command::Command(string input, Server &server) : _server(server)
{
	size_t start = 0;
	size_t end = input.find(" ");
	int i = 0;

	this->cmdName = input.substr(start, end - start);
	while (end != std::string::npos)
	{
		start = end + 1;
		end = input.find(" ", start);
		if (input[start] == ':') {
				this->msg = input.substr(start + 1, input.length() - 2 - start); //-2 pour enlever le \r\n
				break;
			}
		this->params.push_back(input.substr(start, end - start));
		i++;
	}
	// Enlever le \r\n du dernier parametre.
	if (input[start] != ':')
		this->params[this->params.size() - 1].erase(this->params[this->params.size() - 1].length() - 2);
	printCmd();
}

void	Command::printCmd()
{
	std::cout << endl << "------- COMMAND -------" << endl;
	std::cout << "[cmdname] " << this->cmdName << endl;
	std::cout << "[msg] " << this->msg << endl;
	std::cout << "[params] ";
	for (std::vector<std::string>::iterator it = this->params.begin(); it != this->params.end(); ++it)
		std::cout << *it << "|";
	std::cout << endl << "-------------------" << endl;
	// Parse command and execute it
}
void Command::execNICK(Client &client) {
	_server.printClientMap();
	client.setNickname(this->params[0]);
	_server.printClientMap();
	(void)client;
}

