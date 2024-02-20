#ifndef RPL_HPP
#define RPL_HPP

#include "../ft_irc.hpp"

# define RN + "\r\n"
# define HOST + "127.0.0.1"

void send_msg(Client client, std::string msg);

# define HEADER_CMD(client) \
(":" + client.getNickname() + "!" + client.getUsername() + "@" + HOST + " ")

# define JOIN_CHANNEL(client, channel) \
send_msg(client, HEADER_CMD(client) + "JOIN " + channel + RN)

#endif