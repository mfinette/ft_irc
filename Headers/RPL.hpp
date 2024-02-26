#ifndef RPL_HPP
#define RPL_HPP

#include "ft_irc.hpp"

# define RN + "\r\n"
# define HOST + "127.0.0.1"

void send_msg(Client client, std::string msg);

# define HEADER(client) \
(":" + client.getNickname() + "!" + client.getUsername())

# define HEADER_CMD(client) \
(HEADER(client) + "@" + HOST + " ")

//  _____                                                 _      
////  __ \                                               | |     
//|| /  \/  ___   _ __ ___   _ __ ___    __ _  _ __    __| | ___ 
//|| |     / _ \ | '_ ` _ \ | '_ ` _ \  / _` || '_ \  / _` |/ __|
//|| \__/\| (_) || | | | | || | | | | || (_| || | | || (_| |\__ \
//  \____/ \___/ |_| |_| |_||_| |_| |_| \__,_||_| |_| \__,_||___/

# define JOIN_CHANNEL(client, channel) \
send_msg(client, HEADER_CMD(client) + "JOIN " + channel + RN)

#define NICK_CLIENT(tempNick, client, newNick) \
send_msg(client, (":" + tempNick + "!" + client.getUsername()) + " NICK :" + newNick + RN);

#define QUIT_SERVER(client, reason) \
send_msg(client, HEADER_CMD(client) + "QUIT :" + reason + RN);

//______              _        ______              _  _            
//| ___ \            (_)       | ___ \            | |(_)           
//| |_/ /  __ _  ___  _   ___  | |_/ / ___  _ __  | | _   ___  ___ 
//| ___ \ / _` |/ __|| | / __| |    / / _ \| '_ \ | || | / _ \/ __|
//| |_/ /| (_| |\__ \| || (__  | |\ \|  __/| |_) || || ||  __/\__ \
//\____/  \__,_||___/|_| \___| \_| \_|\___|| .__/ |_||_| \___||___/
//                                         |_|                                     

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

//______              _         _____                             
//| ___ \            (_)       |  ___|                            
//| |_/ /  __ _  ___  _   ___  | |__  _ __  _ __  ___   _ __  ___ 
//| ___ \ / _` |/ __|| | / __| |  __|| '__|| '__|/ _ \ | '__|/ __|
//| |_/ /| (_| |\__ \| || (__  | |___| |   | |  | (_) || |   \__ \
//\____/  \__,_||___/|_| \___| \____/|_|   |_|   \___/ |_|   |___/

//451 ERR_NOTREGISTERED
#define ERR_NOTREGISTERED(client, nick) \
send_msg(client, HEADER(client) + " 451 " + nick + " :You have not registered" + RN)

//461 ERR_NEEDMOREPARAMS
# define ERR_NEEDMOREPARAMS(client, command) \
send_msg(client, HEADER(client) + " 461 " + client.getNickname() + " " + command + " :Not enough parameters" + RN)

//462 ERR_ALREADYREGISTERED
#define ERR_ALREADYREGISTERED(client) \
send_msg(client, HEADER(client) + " 462 " + client.getNickname() + " :You may not reregister" + RN)

//464 ERR_PASSWDMISSMATCH
#define ERR_PASSWDMISSMATCH(client, nick) \
send_msg(client, HEADER(client) + " 464 " + nick + ":Password incorrect" + RN)

// _____              _  _        
//|_   _|            (_)| |       
//  | |  _ __ __   __ _ | |_  ___ 
//  | | | '_ \\ \ / /| || __|/ _ \
// _| |_| | | |\ V / | || |_|  __/
// \___/|_| |_| \_/  |_| \__|\___|


//336 RPL_INVITELIST
# define RPL_INVITELIST(client, channel) \
send_msg(client, HEADER(client) + " 336 " + client.getNickname() + " " + channel + RN);

//341 RPL_INVITING
# define RPL_INVITING(client, nick, channel) \
send_msg(client, HEADER(client) + " 341 " + client.getNickname() + " " + nick + " " + channel + RN);

//473 ERR_INVITEONLYCHAN
# define ERR_INVITEONLYCHAN(client, channel) \
send_msg(client, HEADER(client) + " 473 " + client.getNickname() + " " + channel + " :Cannot join channel (+i)" + RN)

// _   _  _        _    
//| \ | |(_)      | |   
//|  \| | _   ___ | | __
//| . ` || | / __|| |/ /
//| |\  || || (__ |   < 
//\_| \_/|_| \___||_|\_\

//401 ERR_NOSUCHNICK
# define ERR_NOSUCHNICK(client, nick, msg) \
send_msg(client, HEADER(client) + " 401 " + client.getNickname() + " " + nick + " :No such " + msg + RN)

//431 ERR_NONICKNAMEGIVEN
#define ERR_NONICKNAMEGIVEN(client, nick) \
send_msg(client, HEADER_CMD(client) + "431 " + client.getNickname() + " " + nick + " :No nickname given" + RN)

//432 ERR_ERRONEUSNICKNAME
#define ERR_ERRONEUSNICKNAME(client, nick) \
send_msg(client, HEADER_CMD(client) + " 432 " + client.getNickname() + " " + nick + " :Erroneus nickname" + RN)

//433 ERR_NICKNAMEINUSE
#define ERR_NICKNAMEINUSE(client, nick) \
send_msg(client, HEADER_CMD(client) + "433 " + (client.getNickname().empty() ? "unknown" : client.getNickname()) + ": " + nick + " is already in use" + RN)

// _____  _                                 _ 
///  __ \| |                               | |
//| /  \/| |__    __ _  _ __   _ __    ___ | |
//| |    | '_ \  / _` || '_ \ | '_ \  / _ \| |
//| \__/\| | | || (_| || | | || | | ||  __/| |
// \____/|_| |_| \__,_||_| |_||_| |_| \___||_|
                                            
//403 ERR_NOSUCHCHANNEL
# define ERR_NOSUCHCHANNEL(client, channel) \
send_msg(client, HEADER(client) + " 403 " + client.getNickname() + " " + channel + " :No such channel" + RN)

//404 ERR_CANNOTSENDTOCHAN
# define ERR_CANNOTSENDTOCHAN(client, channel) \
send_msg(client, HEADER(client) + " 404 " + client.getNickname() + " " + channel + " :Cannot send to channel" + RN)

//441 ERR_USERNOTINCHANNEL
# define ERR_USERNOTINCHANNEL(client, nick, channel) \
send_msg(client, HEADER(client) + " 441 " + client.getNickname() + " " + nick + " " + channel + " :They aren't on that channel" + RN)

//442 ERR_NOTONCHANNEL
# define ERR_NOTONCHANNEL(client, channel) \
send_msg(client, HEADER(client) + " 442 " + client.getNickname() + " " + channel + " :You're not on that channel" + RN)

//443 ERR_USERONCHANNEL
# define ERR_USERONCHANNEL(client, nick, channel) \
send_msg(client, HEADER(client) + " 443 " + client.getNickname() + " " + nick + " " + channel + " :is already on channel" + RN)

//471 ERR_CHANNELISFULL
# define ERR_CHANNELISFULL(client, channel) \
send_msg(client, HEADER(client) + " 471 " + client.getNickname() + " " + channel + " :Cannot join channel (+l)" + RN)

//475 ERR_BADCHANNELKEY
# define ERR_BADCHANNELKEY(client, channel) \
send_msg(client, HEADER(client) + " 475 " + client.getNickname() + " " + channel + " :Cannot join channel (+k)" + RN)

//482 ERR_CHANOPRIVSNEEDED
# define ERR_CHANOPRIVSNEEDED(client, channel) \
send_msg(client, HEADER(client) + " 482 " + client.getNickname() + " " + channel + " :You're not channel operator" + RN)



#endif