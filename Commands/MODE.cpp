#include "../Headers/ft_irc.hpp"

//PARAMETRES : MODE <channel> <options(-i, -o, -t,..)>



//Si option pas specifie, RPL_UMODEIS -> display des modes du channel
//Si option, execution et MODE message envoye au client, si un des modes specifie ne marche pas, execution des modes 
//qui marchent et ERR_UMODEUNKNOWNFLAG + MODE message.

//if channel  existe pas ERR_NOSUCHCHANNEL
//Si option pas specifie, RPL_CHANNELMODEIS - > display des modes du channel

//si option sur channel, le user doit etre op sinon ERR_CHANOPRIVSNEEDED
//Quand le serveur a exec les changement, une cmmand mode est envoye a tt les users

//option commencent avec - ou + et lettres
//i t k l o TYPE B (necessite un argument), si pas dargument le server ignore
void Command::oMode(Client &client, Channel &channel, string param, char sign) {
	cout << "oFUNC" << endl;
	if (!isExistingNick(_server, param))
		return ERR_NOSUCHNICK(client, param, "nick");
	int targetClient = _server.getClient(param).getSocket();
	cout << targetClient << endl;
	if (sign == '-' && client.getSocket() != targetClient)
		channel.changeOperatorStatusToOff(targetClient);
	else if (sign == '+')
		channel.changeOperatorStatusToOn(targetClient); 
	else if (channel.isOperator(_server.getClient(param).getSocket()))
		channel.changeOperatorStatusToOff(targetClient); 
	else
		channel.changeOperatorStatusToOn(targetClient);
	channel.updateClientList();
}

void Command::iMode(Channel &channel, char sign) {
	cout << "iFUNC" << endl;
	if (sign == '-')
		channel.changeInviteOnlyStatusToOn();
	else if (sign == '+')
		channel.changeInviteOnlyStatusToOff();
	else if (channel.getInviteStatus())
		channel.changeInviteOnlyStatusToOn();
	else
		channel.changeInviteOnlyStatusToOff();

}

void Command::tMode(Channel &channel, char sign) {

	cout << "tFUNC" << endl;
	if (sign == '-')
		channel.changeTopicRestrictionToOff();
	else if (sign == '+')
		channel.changeTopicRestrictionToOn();
	else if (channel.hasTopicRestriction())
		channel.changeTopicRestrictionToOff();
	else
		channel.changeTopicRestrictionToOn();
}

void Command::kMode(Channel &channel, string param, char sign) {
	cout << "kFUNC" << endl;
	if (sign == '-') {

		channel.setHasPasswordToFalse();
		cout << "oui" << endl;
	}
	else if (sign == '+' && param != "") {
		cout << "oui" << endl;
		channel.setHasPasswordToTrue();
		channel.setPassword(param);
		cout << channel.getPassword() << endl;
		cout << channel.hasPassword() << endl;
	}
	else if (channel.hasPassword()) {
		channel.setHasPasswordToFalse();
	}
	else if (!channel.hasPassword() && param != "") {
		channel.setHasPasswordToTrue();
		channel.setPassword(param);
		cout << channel.getPassword() << endl;
		cout << channel.hasPassword() << endl;
	}

}

void Command::lMode(Channel &channel, string param, char sign) {
	cout << "lFUNC" << endl;
	(void) channel;
	
	size_t nbr = atoi(param.c_str());
	cout << nbr << endl;
	if (sign == '-')
		channel.changeUserLimit(-1);
	if (sign == '+' && param.find_first_not_of("0123456789") == std::string::npos)
		channel.changeUserLimit(nbr);
	else
		channel.changeUserLimit(-1);
}

std::string	Server::getModestring(std::string channelName){
	Channel &channel = getChannel(channelName);
	
	std::string modestring = " +";
	if (channel.hasPassword())
		modestring += "k";
	if (channel.isInviteOnly())
		modestring += "i";
	if (channel.getUserLimit() == -1)
		modestring += "l";
	if (channel.hasTopicRestriction())
		modestring += "t";
	if (modestring.size() == 2)
		return ("");
	return modestring;
}

void	Command::MODE(Client &client) {
	string modeStr = "";
	char sign = '\0';
	size_t j = 2;
	string parameter;

	cout << "mode fnc" << endl;
	if (params.size() <= 0)
		return ERR_NEEDMOREPARAMS(client, "MODE");
	if (!_server.channelExisting(params[0]))
		return ERR_NOSUCHCHANNEL(client, params[0]);
	if (params.size() <= 1)
		return RPL_CHANNELMODEIS(client, params[0], _server.getModestring(params[0]));
	if (params.size() >= 2)
		modeStr = params[1];
	Channel &channel = _server.getChannel(params[0]);
	if (!channel.isOperator(client.getSocket()))
		return ERR_CHANOPRIVSNEEDED(client, params[0]);
	if (modeStr == "")
		return RPL_CHANNELMODEIS(client, params[0], _server.getModestring(params[0]));
	parameter = "";
	for (size_t i = 0; i < modeStr.size(); i++) {
		if (j < params.size() && (modeStr[i] == 'o' || modeStr[i] == 'k' || modeStr[i] == 'l'))
			parameter = params[j++];
		if (modeStr[i] == '+' || modeStr[i] == '-') {
			sign = modeStr[i];
			if (modeStr[i + 1] && !isalpha(modeStr[i + 1])) {
				cout << "erreur" << endl;
				break; //si pas une lettre apres sign arret de la cmd.
			}
			continue;
		}
		if (modeStr[i] == 'o') {
			oMode(client, channel, parameter, sign);
		}
		else if (modeStr[i] == 'i')
			iMode(channel, sign);
		else if (modeStr[i] == 't')
			tMode(channel, sign);
		else if (modeStr[i] == 'k')
			kMode(channel, parameter, sign);
		else if (modeStr[i] == 'l')
			lMode(channel, parameter, sign);
		else if (isalpha(modeStr[i]))
<<<<<<< HEAD
			//ERR_UMODEUNKNOWNFLAG
		;
=======
			ERR_UMODEUNKNOWNFLAG(client);
>>>>>>> e44164f7796ba3d925a43ab28cc17eb2a86355a9
	}
}