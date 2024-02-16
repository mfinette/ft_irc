/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:09:36 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/16 16:25:30 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"

int main(int argc, char **argv)
{
	(void)argc;
	Server server(-1);
	server.start(atoi(argv[1]));
	return 0;
}
