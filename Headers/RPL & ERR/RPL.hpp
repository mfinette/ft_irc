#ifndef RPL_HPP
#define RPL_HPP

#include "../ft_irc.hpp"

# define RN + "\r\n"
# define HOST + "127.0.0.1"

void send_msg(Client client, std::string msg);

# define HEADER(client) \
(":" + client.getNickname() + "!" + client.getUsername())

# define HEADER_CMD(client) \
(HEADER(client) + "@" + HOST + " ")

# define JOIN_CHANNEL(client, channel) \
send_msg(client, HEADER_CMD(client) + "JOIN " + channel + RN)


//001 RPL_WELCOME
# define RPL_WELCOME(client, msg) \
send_msg(client, HEADER(client) + " 001 " + client.getNickname() + " :" + msg + RN)

//301 RPL_AWAY
# define RPL_AWAY(client, nick, msg) \
send_msg(client, HEADER(client) + " 301 " + client.getNickname() + " " + nick + " " + msg + RN)

//332 RPL_TOPIC
# define RPL_TOPIC(client, channel, topic) \
send_msg(client, HEADER(client) + " 332 " + client.getNickname() + " " + channel + " :" + topic);

//353 RPL_NameReply
# define RPL_NameReply(client, msg) \
send_msg(client, HEADER(client) + " 353 " + client.getNickname() + " = channeltest " + msg + RN)

//404 ERR_CANNOTSENDTOCHAN
# define ERR_CANNOTSENDTOCHAN(client, channel) \
send_msg(client, HEADER(client) + " 404 " + client.getNickname() + " " + channel + " :Cannot send to channel" + RN)

//471 ERR_CHANNELISFULL
# define ERR_CHANNELISFULL(client, channel) \
send_msg(client, HEADER(client) + " 471 " + client.getNickname() + " " + channel + " :Cannot join channel (+l)" + RN)

//473 ERR_INVITEONLYCHAN
# define ERR_INVITEONLYCHAN(client, channel) \
send_msg(client, HEADER(client) + " 473 " + client.getNickname() + " " + channel + " :Cannot join channel (+i)" + RN)

//475 ERR_BADCHANNELKEY
# define ERR_BADCHANNELKEY(client, channel) \
send_msg(client, HEADER(client) + " 475 " + client.getNickname() + " " + channel + " :Cannot join channel (+k)" + RN)

#endif