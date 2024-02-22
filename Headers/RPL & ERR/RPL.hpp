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

//331 RPL_NOTOPIC
# define RPL_NOTOPIC(client, channel) \
send_msg(client, HEADER(client) + " 331 " + client.getNickname() + " " + channel + " :No topic is set" + RN);

//332 RPL_TOPIC
# define RPL_TOPIC(client, channel, topic) \
send_msg(client, HEADER(client) + " 332 " + client.getNickname() + " " + channel + " :" + topic + RN);

//333 RPL_TOPICWHOTIME
# define RPL_TOPICWHOTIME(client, channel, author, setAt) \
send_msg(client, HEADER(client) + " 333 " + client.getNickname() + " " + channel + " " + author + " " + setAt + RN);

//353 RPL_NameReply
# define RPL_NameReply(client, msg) \
send_msg(client, HEADER(client) + " 353 " + client.getNickname() + " = channeltest " + msg + RN)

//403 ERR_NOSUCHCHANNEL
# define ERR_NOSUCHCHANNEL(client, channel) \
send_msg(client, HEADER(client) + " 403 " + client.getNickname() + " " + channel + " :No such channel" + RN)

//404 ERR_CANNOTSENDTOCHAN
# define ERR_CANNOTSENDTOCHAN(client, channel) \
send_msg(client, HEADER(client) + " 404 " + client.getNickname() + " " + channel + " :Cannot send to channel" + RN)

//442 ERR_NOTONCHANNEL
# define ERR_NOTONCHANNEL(client, channel) \
send_msg(client, HEADER(client) + " 442 " + client.getNickname() + " " + channel + " :You're not on that channel" + RN)

//461 ERR_NEEDMOREPARAMS
# define ERR_NEEDMOREPARAMS(client, command) \
send_msg(client, HEADER(client) + " 461 " + client.getNickname() + " " + command + " :Not enough parameters" + RN)

//471 ERR_CHANNELISFULL
# define ERR_CHANNELISFULL(client, channel) \
send_msg(client, HEADER(client) + " 471 " + client.getNickname() + " " + channel + " :Cannot join channel (+l)" + RN)

//473 ERR_INVITEONLYCHAN
# define ERR_INVITEONLYCHAN(client, channel) \
send_msg(client, HEADER(client) + " 473 " + client.getNickname() + " " + channel + " :Cannot join channel (+i)" + RN)

//475 ERR_BADCHANNELKEY
# define ERR_BADCHANNELKEY(client, channel) \
send_msg(client, HEADER(client) + " 475 " + client.getNickname() + " " + channel + " :Cannot join channel (+k)" + RN)

//482 ERR_CHANOPRIVSNEEDED
# define ERR_CHANOPRIVSNEEDED(client, channel) \
send_msg(client, HEADER(client) + " 482 " + client.getNickname() + " " + channel + " :You're not channel operator" + RN)
#endif