/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BotCommands.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:30:25 by mfinette          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:56 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

void	help(int client_socket, Cmd cmd)
{
	std::cout << " IN HELP COMMAND channel = " << cmd._channel << std::endl;
	std::string response = "PRIVMSG " + cmd._channel + " :Need some help? Here is a list of the available commands:\n-joke\n-help\n For further insight, type help <command>";
	sendMessage(client_socket, response);
	// do the <command> thingy here
}
