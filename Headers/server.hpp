#ifndef SERVER_HPP
#define SERVER_HPP

#include "ft_irc.hpp"

class Server
{
	public:
										Server(int port, string password);
										~Server();
		void							start();
		void							setup();
		void							stop();
		
		////////////////// MAP GETTERS //////////////////
		Client							&getClient(int socket);
		Client							&getClient(std::string nickname);
		Channel							&getChannel(std::string name);
		std::map<int, Client>			&getClientList();
		string 							getServPassword();

		////////////////// MAP MANAGEMENT //////////////////
		void							addClientToServer(Client& client);
		void							setupClient(int socket);
		void							removeClientFromServer(Client& client);
		void							addChannelToServer(string name, Channel& channel);
		void							removeChannelFromServer(string name, Channel& channel);

		////////////////// stuff //////////////////
		void							printClientMap();
		bool							isClientAway(int socket);
		bool							isClientAway(std::string nickname);
		bool							channelExisting(std::string channel_name);

	private:
		int								_serverSocket;
		int								_port;
		bool							_running;
		string							_password;
		std::map<int, Client>			_clientList;
		std::map<std::string, Channel>	_channelList;

		////////////////// SERVER MANAGEMENT //////////////////
		void							bindServerSocket(int serverSocket, int port);
		void							listenForConnections(int serverSocket, int backlog);
		int								acceptClientConnection(int serverSocket, sockaddr_in& clientAddr);
		void							handleClient(int clientSocket);
		void							handleServer(int serverSocket, struct pollfd fds[], int& numClients, const int MAX_CLIENTS);
		void							closeSocket(int socket);
};

		////////////////// OPERATOR OVERLOADS //////////////////
std::ostream& operator<<(std::ostream& os, std::map<int, Client>& myMap);
std::ostream& operator<<(std::ostream& os, std::map<std::string, Channel>& myChannel);



#endif
