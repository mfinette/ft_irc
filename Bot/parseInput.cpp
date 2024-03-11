/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseInput.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:09:28 by mfinette          #+#    #+#             */
/*   Updated: 2024/03/11 21:42:51 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

Cmd::Cmd(std::string cmd) : _fullCmd(cmd), _isPRIVMSG(false), _isChannel(false)
{
	std::istringstream iss(cmd);
	std::string sender, type, channel, content;
	std::getline(iss, sender, ' ');
	_sender = sender.substr(1, sender.length() - 1);
	std::getline(iss, type, ' ');
	if (type != "PRIVMSG")
		return;
	_isPRIVMSG = true;
	std::getline(iss, channel, ' ');
	if (channel == "bot")
	{
		_isChannel = false;
		_channel = _sender;
		std::getline(iss, content);
		content = content.substr(1, content.length() - 1);
		std::cout << "(IN PARSING) = content: " << content << "\n";
		_cmdRemaining = getStringWithoutFirstWord(content);
	}
	else
	{
		_isChannel = true;
		_channel = channel;
		std::getline(iss, content);
		_cmdRemaining = removeBackslashR(content);
		_cmdRemaining = getStringWithout2FirstWords(_cmdRemaining);
	}
	_cmdRemaining = removeBackslashR(_cmdRemaining);
	_isForBot = (getFirstWord(content) == "bot");
	_cmdType = getSecondWord(content);
	_cmdType = removeBackslashR(_cmdType);
	_channel = removeBackslashR(_channel);
}

Cmd::~Cmd()
{
}

void	sendResponse(int client_socket, Cmd cmd)
{
	if (cmd._isPRIVMSG)
	{
		if (cmd._isChannel)
		{
			if (cmd._isForBot)
				chooseResponse(client_socket, cmd);
		}
		else
		{
			cmd._cmdType = getFirstWordAfter2Colons(cmd._fullCmd);
			cmd._cmdType = removeBackslashRN(cmd._cmdType);
			cmd._cmdRemaining = removeBackslashRN(cmd._cmdRemaining);
			chooseResponse(client_socket, cmd);
		}
	}
}

void	chooseResponse(int client_socket, Cmd cmd)
{
	printCommand(cmd);
	if (cmd._cmdType == "join")
		join(client_socket, cmd);
	else if (cmd._cmdType == "hello")
		hello(client_socket, cmd);
	else if (cmd._cmdType == "help")
		help(client_socket, cmd);
	else if (cmd._cmdType == "joke")
		joke(client_socket, cmd);
	else if (cmd._cmdType == "funfact")
		funfact(client_socket, cmd);
	else
		sendMessage(client_socket, "PRIVMSG " + cmd._channel + " :Unknown command. Type 'help' for a list of available commands.");
}
