#include "../Headers/ft_irc.hpp"

void	Channel::updateEveryClient(){
	std::map<Client *, bool>::iterator it;

	for(it = _client.begin(); it != _client.end(); ++it){
		Client client = *it->first;
		if (_topic.size() != 0){
			RPL_TOPIC(client, _name, _topic);
			RPL_TOPICWHOTIME(client, _name, _topic_author, getSetAt());
		}
		else
			RPL_NOTOPIC(client, _name);
	}
}

void	Command::TOPIC(Client &client, std::string channel_name, std::string topic){
	if (channel_name == "") //check if a name as been given as parameters
		return ERR_NEEDMOREPARAMS(client, "TOPIC");
	if (_server.channelExisting(channel_name)){ //check if the channel is existing
		Channel channel = _server.getChannel(channel_name);
		if (channel.isClientInChannel(client.getSocket())){ //check if the client is in the channel 
			if (params.size() != 0){ //si il y a des parametres ==> modifications du topic
				if (channel.hasTopicRestriction()) //check si le topic peut etre changer uniquement en tant que moderateur
					if (!channel.isOperator(client.getSocket())) //check si le client est ops
						return ERR_CHANOPRIVSNEEDED(client, channel_name); //si pas ops ERR
				channel.setTopic(topic);
				channel.setTopicAuthor(client.getNickname());
				channel.updateEveryClient();
			}
			else{ //si il n'y a pas de parametre ==> affichage du topic
				if (channel.getTopic().size() != 0){
					RPL_TOPIC(client, channel_name, channel.getTopic());
					RPL_TOPICWHOTIME(client, channel_name, channel.getTopicAuthor(), channel.getSetAt());
				}
				else
					RPL_NOTOPIC(client, channel_name);
			}
		} 
		else //si le client n'est pas dans le channel
			ERR_NOTONCHANNEL(client, channel_name);
	} //si le channel n'existe pas
	else
		ERR_NOSUCHCHANNEL(client, channel_name);
}