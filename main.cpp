/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:09:36 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/19 16:28:09 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"

int main(int argc, char **argv)
{
	if (argc != 3){
		std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
		return 0;
	}
	Server server(atoi(argv[1]), argv[2]);
	server.start();
	return 0;
}
