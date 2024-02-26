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
void Command::oMode(Channel channel, string param, char sign) {
	if (!isExistingNick(_server, param))
		// ERR_NOSUCHNICK(client, client.getNickname(), channel);
		return;
	if (sign == '-')
		cout << "-o" << endl;
		//remove user from op
	else if (sign == '+')
		cout << "+o" << endl;
		//add user to op
	else if (channel.isOperator(_server.getClient(param).getSocket()))
	;
		//remove user from op
	else ;
		//add user to op
}

void Command::iMode(Channel channel, char sign) {
	if (sign == '-')
	;
		//make channel free entry
	else if (sign == '+')
	;
		//make channel invitation only
	else if (channel.getInviteStatus())
	;
		//make channel free entry
	else ;
		//make channel invitation only
}

void Command::tMode(Channel channel, char sign) {
	if (sign == '-')
	;
		//make channel topic restriction free
	else if (sign == '+')
	;
		//make channel topic restricted
	else if (channel.hasTopicRestriction())
	;
		//make channel topic restriction free
	else ;
		//make channel topic resticted
}

void Command::kMode(Channel channel, string param, char sign) {
	if (sign == '-') ;
		//rm pass
	else if (sign == '+')
	;
		//add pass
	else if (channel.getPassword() == param)
	;
		//rm pass
}

void Command::lMode(Channel channel, string param, char sign) {
	(void) channel;
	if (param == "")
	;
		//rm channel limit
	if (sign == '-')
	;
		//rm channel limit
	else if (sign == '+')
	;
		//add channel limit
	else
	;
		//rm channel limit 
}


void	Command::MODE(Client &client) {
	(void)client;
	string modeStr = "";
	char sign = '\0';
	size_t j = 2;
	cout << "mode fnc" << endl;
	if (params.size() <= 0)
		// RPL_CHANNELMODEIS
		;
	if (params.size() <= 1)
		// ERR_NEEDMOREPARAMS
		;
	if (params.size() >= 2)
		modeStr = params[1];
	if (!_server.channelExisting(params[0]))
		// ERR_NOSUCHNICK(client params[j]
		;
	Channel &channel = _server.getChannel(params[0]);
	if (!channel.isOperator(_server.getClient(params[0]).getSocket()))
	// ERR_CHANOPRIVSNEEDED
		return;
	if (modeStr == "")
		//RPL_CHANNELMODEIS
	;
	for (size_t i = 0; i < modeStr.size(); i++) {
		if (modeStr[i] == '+' || modeStr[i] == '-') {
			sign = modeStr[i];
			if (modeStr[i + 1] && !isalpha(modeStr[i + 1])) {
				break; //si pas une lettre apres sign arret de la cmd.
			}
			continue;
		}
		cout << modeStr[i] << "sign : " << sign  << "!"<< endl;
		if (modeStr[i] == 'o') {
			oMode(channel, params[j], sign);
		}
		else if (modeStr[i] == 'i')
			iMode(channel, sign);
		else if (modeStr[i] == 't')
			tMode(channel, sign);
		else if (modeStr[i] == 'k' && j < params.size())
			kMode(channel, params[j], sign);
		else if (modeStr[i] == 'l')
			lMode(channel, params[j], sign);
		else if (isalpha(modeStr[i]))
			// ERR_UMODEUNKNOWNFLAG
		if (j < params.size() && (modeStr[i] == 'o' || modeStr[i] == 'k' || modeStr[i] == 'l'))
			j++;
	}
}