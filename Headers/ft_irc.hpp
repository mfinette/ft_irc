/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:10:41 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/17 00:36:44 by colas            ###   ########.fr       */
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
#include <stdlib.h>
#include <vector>
#include <poll.h>
#include <fcntl.h>
#include "user.hpp"
#include "command.hpp"
#include "server.hpp"
#include "RPL & ERR/ERR.hpp"
#include "RPL & ERR/RPL.hpp"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cerr;
using std::memset;

#endif // FT_IRC_HPP
