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
	if (sign == '-' && client.getSocket() != targetClient){
		channel.changeOperatorStatusToOff(targetClient);
		std::string modestring = "-o " + param;
		MODE_MESSAGE(client, channel.getName(), modestring);
	}
	else if (_server.getClient(param).getNickname() != "bot" && sign == '+'){
		channel.changeOperatorStatusToOn(targetClient);
		std::string modestring = "+o " + param;
		MODE_MESSAGE(client, channel.getName(), modestring);
	}
	else if (channel.isOperator(_server.getClient(param).getSocket())){
		channel.changeOperatorStatusToOff(targetClient);
		std::string modestring = "-o " + param;
		MODE_MESSAGE(client, channel.getName(), modestring);
	}
	else if (_server.getClient(param).getNickname() != "bot"){
		channel.changeOperatorStatusToOn(targetClient);
		std::string modestring = "+o " + param;
		MODE_MESSAGE(client, channel.getName(), modestring);
	}
	channel.updateClientList();
}

void Command::iMode(Channel &channel, char sign, Client &client) {
	cout << "iFUNC" << endl;
	if (sign == '-'){
		channel.changeInviteOnlyStatusToOff();
		MODE_MESSAGE(client, channel.getName(), "-i");
	}
	else if (sign == '+'){
		channel.changeInviteOnlyStatusToOn();
		MODE_MESSAGE(client, channel.getName(), "+i");
	}
	else if (channel.getInviteStatus()){
		channel.changeInviteOnlyStatusToOff();
		MODE_MESSAGE(client, channel.getName(), "-i");
	}
	else{
		channel.changeInviteOnlyStatusToOn();
		MODE_MESSAGE(client, channel.getName(), "+i");
	}
}

void Command::tMode(Channel &channel, char sign, Client &client) {

	cout << "tFUNC" << endl;
	if (sign == '-'){
		channel.changeTopicRestrictionToOff();
		MODE_MESSAGE(client, channel.getName(), "-t");
	}
	else if (sign == '+'){
		channel.changeTopicRestrictionToOn();
		MODE_MESSAGE(client, channel.getName(), "+t");
	}
	else if (channel.hasTopicRestriction()){
		channel.changeTopicRestrictionToOff();
		MODE_MESSAGE(client, channel.getName(), "-t");
	}
	else{
		channel.changeTopicRestrictionToOn();
		MODE_MESSAGE(client, channel.getName(), "+t");
	}
}

void Command::kMode(Channel &channel, string param, char sign, Client &client) {
	cout << "kFUNC" << endl;
	cout << "sign: " << sign << " param: " << param << "\n"; 
	if (sign == '-') {
		channel.setHasPasswordToFalse();
		MODE_MESSAGE(client, channel.getName(), "-k");
	}
	else if (sign == '+' && param != "") {
		cout << "test: " << param << "\n";
		channel.setHasPasswordToTrue();
		channel.setPassword(param);
		std::string modestring = "+k " + channel.getPassword();
		MODE_MESSAGE(client, channel.getName(), modestring);
	}
	else if (channel.hasPassword()) {
		channel.setHasPasswordToFalse();
		MODE_MESSAGE(client, channel.getName(), "-k");
	}
	else if (!channel.hasPassword() && param != "") {
		channel.setHasPasswordToTrue();
		channel.setPassword(param);
		std::string modestring = "+k " + channel.getPassword();
		MODE_MESSAGE(client, channel.getName(), modestring);
	}

}

void Command::lMode(Channel &channel, string param, char sign, Client &client) {
	cout << "lFUNC" << endl;
	(void) channel;
	
	int nbr = atoi(param.c_str());
	if (sign == '-'){
		channel.changeUserLimit(-1);
		MODE_MESSAGE(client, channel.getName(), "-l");
	}
	else if (sign == '+' && param.find_first_not_of("0123456789") == std::string::npos){
		if (nbr < channel.nbClient())
			return ;
		channel.changeUserLimit(nbr);
		std::string modestring = "+l ";
		std::ostringstream oss;
   		oss << channel.getUserLimit();
		modestring += oss.str();
		MODE_MESSAGE(client, channel.getName(), modestring);

	}
	else{
		channel.changeUserLimit(-1);
		MODE_MESSAGE(client, channel.getName(), "-l");
	}
}

std::string	Server::getModestring(std::string channelName){
	Channel &channel = getChannel(channelName);

	std::string modestring = "+";
	if (channel.hasPassword())
		modestring += "k";
	if (channel.isInviteOnly())
		modestring += "i";
	if (channel.getUserLimit() != -1)
		modestring += "l";
	if (channel.hasTopicRestriction())
		modestring += "t";
	if (modestring.size() == 1)
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
		if (modeStr[i] == 'o')
			oMode(client, channel, parameter, sign);
		else if (modeStr[i] == 'i')
			iMode(channel, sign, client);
		else if (modeStr[i] == 't')
			tMode(channel, sign, client);
		else if (modeStr[i] == 'k')
			kMode(channel, parameter, sign, client);
		else if (modeStr[i] == 'l')
			lMode(channel, parameter, sign, client);
		else if (isalpha(modeStr[i]))
			ERR_UMODEUNKNOWNFLAG(client);
	}
}