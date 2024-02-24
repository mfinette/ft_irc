/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/24 12:11:34 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"

// std::string assemble_msg(std::string servName, std::string msg, std::string nickname, std::string code) { 
// 	return std::string(":" + servName + " " + getcode(msg) + " " + nickname + " ");
// }

void printWithNonPrintable(string input) {
	int i = 0;
	while (input[i]) {
		int res = input[i];
		if (res < 32 || res >= 127)
			cout << "|" << res;
		else
			cout << input[i];
		i++;
	}
	cout << endl;
}

bool findNextWord(string input, size_t &start, size_t &end) {
	cout << "b" << start << "|" << end << endl;
	start = input.find_first_not_of(' ', end);
	end = input.find(' ', start);
	cout << "a" << start << "|" << end << endl;
	if (start == string::npos)
		return false;
	return true;
}
//Parse input of hexchat into a "command" object,
//the msg variable is filled if there's a message at the end of the input.
Command::Command(string input, Server &server) : _server(server)
{
	size_t start = input.find_first_not_of(' ');
	size_t end = input.find(' ', start);
	int i = 0;
	cout << "premier : " << start << "|" << end << endl;
	input.erase(input.find('\r'));
	printWithNonPrintable(input);
	if (end == std::string::npos)
		this->cmdName = input.substr(start, input.length() - start);
	else
		this->cmdName = input.substr(start, end - start);
	while (end != std::string::npos)
	{
		if (!findNextWord(input, start, end))
			break;
		if (input[start] == ':')
		{
			this->msg = input.substr(start + 1, input.length() - start);
			break;
		}
		this->params.push_back(input.substr(start, end - start));
		i++;
	}
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
}

string Command::getCmdName() {
	return cmdName;
}

string Command::getCmdParam(int index) {
	return params[index];
}

string Command::getCmdMessage() {
	return msg;
}
