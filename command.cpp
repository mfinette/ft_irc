/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:04:42 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/17 00:40:36 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"

// std::string assemble_msg(std::string servName, std::string msg, std::string nickname, std::string code) { 
// 	return std::string(":" + servName + " " + getcode(msg) + " " + nickname + " ");
// }

Command Command::parseMsgToCmd(string input)
{
	Command cmd;
	size_t start = 0;
    size_t end = input.find(" ");

    while (end != std::string::npos) {
		cmd.cmdName = input.substr(start, end - start);
		start = end + 1;
		end = input.find(" ", start);
    }
}

void	Command::parseCmd(Command command)
{
	(void)command;
	// Parse command and execute it
}
