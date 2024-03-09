/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BotCommands.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:30:25 by mfinette          #+#    #+#             */
/*   Updated: 2024/03/09 12:48:30 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

void	help(int client_socket, Cmd cmd)
{
	std::string response = "PRIVMSG " + cmd._channel + " :Need some help? Here is a list of the available commands: [joke, help, join, hello] For further insight, type help <command>";
	sendMessage(client_socket, response);
	// do the <command> thingy here
}

void	joke(int client_socket, Cmd cmd)
{
	std::string response = "PRIVMSG " + cmd._channel + " :Here is a joke: " + fetchJoke();
	sendMessage(client_socket, response);
}