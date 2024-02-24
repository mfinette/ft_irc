/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:09:36 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/24 20:26:04 by maxime           ###   ########.fr       */
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
	try
	{
		signal(SIGINT, signalHandler);
		server.start();
	}
	catch (const CtrlCException &e)
	{
		std::cout << "\nCtrl + C detected, closing server" << std::endl;
		server.closeServer();
		exit(1);
	}
	// commenter les deux catch d'en dessous pour coder sans crash toutes les 2 secondes
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		server.closeServer();
		return 1;
	}
	catch (...)
	{
		std::cerr << "Unknown error but it'll take more to crash us hihi" << std::endl;
		server.closeServer();
		return 1;
	}
	return 0;
}
