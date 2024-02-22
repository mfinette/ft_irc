#include "../Headers/ft_irc.hpp"

bool isExistingNick(Server server, string newNick) {
	std::map<int, Client>::const_iterator it;

	for (it = server.getClientList().begin(); it != server.getClientList().end(); ++it)
	{
        if (it->second.getNickname() == newNick)
            return true;
    }
	return false;
}

bool Command::NICK(Client &client) {
	if (params.size() != 0) {
		if (!isExistingNick(_server, params[0])) {
			if (params[0].find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ\
				abcdefghijklmnopqrstuvwxyz0123456789[]{}\\|") == std::string::npos) {
					client.setNickname(this->params[0]);
					return true;
			}
			else
				ERR_ERRONEUSNICKNAME(client, this->params[0]);
		}
		else
			ERR_NICKNAMEINUSE(client, this->params[0]);
	}
	else 
		ERR_NONICKNAMEGIVEN(client, "unknow");
	return false;
}