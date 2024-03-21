/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BotCommands.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:30:25 by mfinette          #+#    #+#             */
/*   Updated: 2024/03/21 13:33:11 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

void	help(int client_socket, Cmd cmd)
{
	std::string response;
	if (cmd._cmdRemaining == "help")
		response = "PRIVMSG " + cmd._channel + " :Need some help? Here is a list of the available commands: [joke, help, join, hello, generate] For further insight, type help <command>";
	else if (cmd._cmdRemaining == "join")
		response = "PRIVMSG " + cmd._channel + " :The join command is used to join a channel. For example, type join #channel";
	else if (cmd._cmdRemaining == "joke")
		response = "PRIVMSG " + cmd._channel + " :The joke command is used to fetch a random joke. For example, type joke";
	else if (cmd._cmdRemaining == "funfact")
		response = "PRIVMSG " + cmd._channel + " :The funfact command is used to fetch a random fun fact. For example, type funfact";
	else if (cmd._cmdRemaining == "generate")
		response = "PRIVMSG " + cmd._channel + " :The generate command is used to generate an image based on a prompt. For example, type generate <prompt>. Please don't use this command too much, it costs money!";
	else if (cmd._cmdRemaining == "hello")
		response = "PRIVMSG " + cmd._channel + " :The hello command is used to greet the bot. For example, type hello";
	else if (cmd._cmdRemaining == "chatbot")
		response = "PRIVMSG " + cmd._channel + " :The chatbot command is used to chat with me using an AI! . For example, type chatbot <prompt>";
	else
		response = "PRIVMSG " + cmd._channel + " :Command not found. Type help to get a list of available commands.";
	sendMessage(client_socket, response);
}

void	joke(int client_socket, Cmd cmd)
{
	std::string response = "PRIVMSG " + cmd._channel + " :Here is a joke: " + fetchJoke();
	sendMessage(client_socket, response);
}

void	funfact(int client_socket, Cmd cmd)
{
	std::string response = "PRIVMSG " + cmd._channel + " :Here is a fun fact: " + fetchFunFact();
	sendMessage(client_socket, response);
}

void	generate(int client_socket, Cmd cmd)
{
	std::string response = "PRIVMSG " + cmd._channel + " :Generating an image based on the prompt: " + cmd._cmdRemaining;
	sendMessage(client_socket, response);
	usleep(1000);
	response = "PRIVMSG " + cmd._channel + " :Here is the generated image: " + getImageFromAPI(cmd._cmdRemaining.c_str());
	sendMessage(client_socket, response);
}

void	join(int client_socket, Cmd cmd)
{
	std::string response = "JOIN " + getFirstWord(cmd._cmdRemaining) + "\r\n";
	sendMessage(client_socket, response);
	usleep(1000);
	// Rajouter une conditions pour que le msg de confirmations ne soit pas envoyer qd pas reussi (car le channel n'existait pas)
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

void	chatbot(int client_socket, Cmd cmd)
{
	std::string	curatedCmd = removeSingleQuotesFromEntireString(removeDoubleQuotesFromEntireString(cmd._cmdRemaining));
	std::string	response = "PRIVMSG " + cmd._channel + " :" + getChatAnswerFromAPI(curatedCmd.c_str());
	sendMessage(client_socket, response);
}
