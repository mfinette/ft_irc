/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:09:36 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/14 14:49:46 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

int main(int argc, char **argv)
{
	(void)argc;
	Server server;
	server.start(atoi(argv[1]));
	return 0;
}



