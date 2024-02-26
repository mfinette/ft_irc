#include "../Headers/ft_irc.hpp"

void	Channel::updateEveryClient(){
	std::map<Client *, bool>::iterator it;

	for(it = _client.begin(); it != _client.end(); ++it){
		Client client = *it->first;
		cout << _topic.size() << endl;
		RPL_TOPIC(client, _name, _topic);
		RPL_TOPICWHOTIME(client, _name, _topic_author, getSetAt());
	}
}

void	Command::TOPIC(Client &client){
	if (this->params.size() == 0) //check if a name as been given as parameters
		return ERR_NEEDMOREPARAMS(client, "TOPIC");
	if (!_server.channelExisting(this->params[0])) //si le channel n'existe pas
		return ERR_NOSUCHCHANNEL(client, this->params[0]);
	Channel channel = _server.getChannel(this->params[0]);
	if (!channel.isClientInChannel(client.getSocket())) //si le clien n'est pas dans le channel
		return ERR_NOTONCHANNEL(client, this->params[0]);
	if (params.size() != 0){ //si il y a des parametres ==> modifications du topic
		if (channel.hasTopicRestriction()) //check si le topic peut etre changer uniquement en tant que moderateur
			if (!channel.isOperator(client.getSocket())) //check si le client est ops
				return ERR_CHANOPRIVSNEEDED(client, this->params[0]); //si pas ops ERR
		channel.setTopic(this->msg);
		channel.setTopicAuthor(client.getNickname());
		channel.setSetAt();
		
		channel.updateEveryClient();
	}
	else{ //si il n'y a pas de parametre ==> affichage du topic
		if (channel.getTopic().size() == 0)
			return RPL_NOTOPIC(client, this->params[0]);
		RPL_TOPIC(client, this->params[0], channel.getTopic());
		RPL_TOPICWHOTIME(client, this->params[0], channel.getTopicAuthor(), channel.getSetAt());			
	}
}