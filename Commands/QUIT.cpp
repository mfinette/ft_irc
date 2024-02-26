#include "../Headers/ft_irc.hpp"

// si un client quitte le channel sans faire la commande QUIT le serveur doit 
//mettre un message correspondant a la raison de la deconnexion

void	Command::QUIT(Client &client)
{	
	QUIT_SERVER(client, msg);
	_server.closeClientSocket(client);
	client.setSocketState(false);
	_server.removeClientFromServer(client);
}