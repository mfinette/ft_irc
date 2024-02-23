#include "../Headers/ft_irc.hpp"

void setFallBackValues(Client &client, string newUsername, string newRealname)
{
	if (newUsername.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ\
	abcdefghijklmnopqrstuvwxyz0123456789[]{}\\|") == std::string::npos)
		client.setUsername(newUsername);
	else
		client.setUsername(client.getNickname());
	if (newRealname.find_first_not_of(" ABCDEFGHIJKLMNOPQRSTUVWXYZ\
	abcdefghijklmnopqrstuvwxyz0123456789[]{}\\|") == std::string::npos)
		client.setRealname(newRealname);
	else
		client.setRealname(client.getNickname());
}

bool Command::USER(Client &client)
{
	if (params.size() > 3 && params[1] == "0" && params[2] == "*")
	{
		if (params[0].length() > USERLEN)
			params[0] = params[0].substr(0, 15);
		if (client.getLoginStage() == ALL_LOGIN_DATA_ENTERED)
		{
			setFallBackValues(client, params[0], msg);
			return true;
		}
		else
			ERR_ALREADYREGISTERED(client);
	}
	else
		ERR_NEEDMOREPARAMS(client, cmdName);
	return false;
}

//eventuellement faire la verif que le realname est precede dun :