#include "../Headers/ft_irc.hpp"

//RPL_TOPIC send when the topic is ask (RPL_TOPICWHOTIME should be sent at the same time)
//RPL_NOTOPIC if no topic

//topic can't be an empty string

//if want to see the topic or change it and not in the channel ==> ERR_NOTONCHANNEL

//if topic restrictions is on, check if client have appropriate permission to modify, if not ==> ERR_CHANOPRIVSNEEDED

// when the topic change, the author of the topic will change

// when the topic, every client on the server will receive RPL_TOPIC

// when new user join a channel, they receive RPL_TOPIC or not if there is no topic

//if channel as params didnt exist ==> ERR_NOSUCHCHANNEL

//if TOPIC function dont have enough params ==> ERR_NEEDMOREPARAMS

void	Command::TOPIC(Client &client, std::string channel_name, std::string topic){
	if (_server.channelExisting(channel_name)){
		Channel channel = _server.getChannel(channel_name);
		if (channel.isClientInChannel(client.getSocket())){
			if (params.size() != 0){
				// want to update the topic
				(void)topic;
			}
			else{
				//want to see the topic
				if (channel.getTopic().size() != 0){
					RPL_TOPIC(client, channel_name, channel.getTopic());
					RPL_TOPICWHOTIME(client, channel_name, channel.getTopicAuthor(), channel.getSetAt());
				}
				else
					RPL_NOTOPIC(client, channel_name);
			}
		}
		else
			ERR_NOTONCHANNEL(client, channel_name);
	}
	else
		ERR_NOSUCHCHANNEL(client, channel_name);
}