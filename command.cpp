/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:04:42 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/18 20:57:43 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"

// std::string assemble_msg(std::string servName, std::string msg, std::string nickname, std::string code) { 
// 	return std::string(":" + servName + " " + getcode(msg) + " " + nickname + " ");
// }

//Parse input of hexchat into a "command" object,
//the msg variable is filled if there's a message at the end of the input.
Command::Command(string input)
{
	size_t start = 0;
	size_t end = input.find(" ");
	int i = 0;

	while (end != std::string::npos)
	{
		if (i == 0 && input[start] == ':')
			this->prefix = input.substr(start, end - start);
		else if (i == 1)
			this->cmdName = input.substr(start, end - start);
		else {
			this->params.push_back(input.substr(start, end - start));
		}
		start = end + 1;
		end = input.find(" ", start);
		i++;
		if (input[start] == ':') {
				this->msg = input.substr(start + 1, input.length() - start);
				break;
			}
	}
	if (input[start] != ':')
		this->params.push_back(input.substr(start, end - start));
	// printCmd();
}

void	Command::printCmd()
{
	std::cout << "[prefix] " << this->prefix << endl;
	std::cout << "[cmdname] " << this->cmdName << endl;
	std::cout << "[msg] " <<this->msg << endl;
	std::cout << "[params] ";
	for (std::vector<std::string>::iterator it = this->params.begin(); it != this->params.end(); ++it)
		std::cout << *it << "|";
	// Parse command and execute it
}
