/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/23 13:47:05 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_IRC_HPP
#define FT_IRC_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <ostream>
#include <stdlib.h>
#include <vector>
#include <poll.h>
#include <fcntl.h>
#include <ctime>
#include <map>
#include <sstream>
#include "channel.hpp"
#include "client.hpp"
#include "command.hpp"
#include "server.hpp"
#include "RPL & ERR/RPL.hpp"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cerr;
using std::memset;

void	getLoginData(string input, Client &client, Server &server);
void	execCMD(string input, Client &client, Server &server);


# define RESET				"\033[0m"
# define BLACK				"\033[30m"
# define RED				"\033[31m"
# define GREEN				"\033[32m"
# define YELLOW				"\033[33m"
# define BLUE				"\033[34m"
# define MAGENTA			"\033[35m"
# define CYAN				"\033[36m"
# define WHITE				"\033[37m"
# define LIGHT_PINK			"\033[38;5;217m"
# define MEDIUM_PINK		"\033[38;5;219m"
# define DARK_PINK			"\033[38;5;205m"
# define PALE_PINK			"\033[38;5;218m"
# define HOT_PINK			"\033[38;5;205m"
# define BABY_PINK			"\033[38;5;225m"
# define NEON_PINK			"\033[38;5;207m"
# define SERVER 0

#endif // FT_IRC_HPP
