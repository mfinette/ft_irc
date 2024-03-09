/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BotCommands.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:30:25 by mfinette          #+#    #+#             */
/*   Updated: 2024/03/09 15:12:12 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

void	help(int client_socket, Cmd cmd)
{
	std::string response;
	if (cmd._cmdRemaining == "help")
		response = "PRIVMSG " + cmd._channel + " :Need some help? Here is a list of the available commands: [joke, help, join, hello] For further insight, type help <command>";
	else if (cmd._cmdRemaining == "join")
		response = "PRIVMSG " + cmd._channel + " :The join command is used to join a channel. For example, type join #channel";
	else if (cmd._cmdRemaining == "joke")
		response = "PRIVMSG " + cmd._channel + " :The joke command is used to fetch a random joke. For example, type joke";
	else if (cmd._cmdRemaining == "hello")
		response = "PRIVMSG " + cmd._channel + " :The hello command is used to greet the bot. For example, type hello";
	else
		response = "PRIVMSG " + cmd._channel + " :Command not found. Type help to get a list of available commands.";
	sendMessage(client_socket, response);
}

void	joke(int client_socket, Cmd cmd)
{
	std::string response = "PRIVMSG " + cmd._channel + " :Here is a joke: " + fetchJoke();
	sendMessage(client_socket, response);
}

void	join(int client_socket, Cmd cmd)
{
	std::string response = "JOIN " + getFirstWord(cmd._cmdRemaining) + "\r\n";
	sendMessage(client_socket, response);
	usleep(1000);
	response = "PRIVMSG " + cmd._channel + " :Joined " + getFirstWord(cmd._cmdRemaining) + "!";
	sendMessage(client_socket, response);
	usleep(1000);
	response = "PRIVMSG " + getFirstWord(cmd._cmdRemaining) + " :Hello! What's popping? I'm a bot. Type help to get a list of available commands.";
	sendMessage(client_socket, response);
}

void	hello(int client_socket, Cmd cmd)
{
	std::string response = "PRIVMSG " + cmd._channel + " :Hello " + cmd._sender + "!";
	sendMessage(client_socket, response);
}
