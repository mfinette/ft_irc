#include "../Headers/ft_irc.hpp"

void	Command::JOIN(Client &client, std::string channel_name, std::string password){
	if (_server.channelExisting(channel_name)){ //check si le channel existe
		Channel channel = _server.getChannel(channel_name);
		if (!channel.isInviteOnly()){ //check si ce n'est pas en invite only
			if (channel.getUserLimit() > channel.nbClient()){ //check si la user limit n'as pas ete depasser
					if (channel.getPassword() == password){ //check si le password est valide
						JOIN_CHANNEL(client, channel_name);
						if (channel.getTopic().size() != 0){
							RPL_TOPIC(client, channel_name, channel.getTopic());
							RPL_TOPICWHOTIME(client, channel_name, channel.getTopicAuthor(), channel.getSetAt());
						}
						else
							RPL_NOTOPIC(client, channel_name);
					}
					else //si mauvais pass
						ERR_BADCHANNELKEY(client, channel_name);
			}
			else //si la user limit est pleine
				ERR_CHANNELISFULL(client, channel_name);
		}
		else //si le channel est sur invitation seulement
			ERR_INVITEONLYCHAN(client, channel_name);
	}
	else{
		std::cout << "channel not existing\n";
		//need to create the channel
	}
}