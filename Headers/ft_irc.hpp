/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:10:41 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/19 13:55:52 by pchapuis         ###   ########.fr       */
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
#include <map>
#include "channel.hpp"
#include "client.hpp"
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
