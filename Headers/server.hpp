#ifndef SERVER_HPP
#define SERVER_HPP

#include "ft_irc.hpp"

# define CLIENT_LIMIT 10

class Server
{
	public:
										Server(int port, string password);
										~Server();
		void							start();
		void							setup();
		void							closeServer();
		
		////////////////// MAP GETTERS //////////////////
		Client							&getClient(int socket);
		Client							&getClient(std::string nickname);
		Channel							&getChannel(std::string name);
		std::map<int, Client>			&getClientList();
		std::map<std::string, Channel>	&getChannelList();
		string 							getServPassword();

		////////////////// MAP MANAGEMENT //////////////////
		void							addClientToServer(const Client& client);
		void							setupClient(int socket);
		void							removeClientFromServer(Client& client);
		void							addChannelToServer(Channel& channel);
		void							removeChannelFromServer(Channel& channel);

		////////////////// stuff //////////////////
		void							printClientMap();
		bool							isClientLog(int socket);
		bool							isClientLog(std::string nickname);
		bool							getClientStatus(int socket);
		bool							getClientStatus(std::string nickname);
		bool							channelExisting(std::string channel_name);
		std::string						getModestring(std::string channelName);


		////////////////// SERVER MANAGEMENT //////////////////
		void							closeClientSocket(Client &client);
		void							bindServerSocket(int serverSocket, int port);
		void							listenForConnections(int serverSocket, int backlog);
		int								acceptClientConnection(int serverSocket, sockaddr_in& clientAddr);
		void							handleClient(int clientSocket, int &numClients);
		void							handleServer(int serverSocket, int& numClients, pollfd fds[]);
		void							closeServerSocket(int socket);
		void							leaveAll(Client &client);
		void							sendAll(Client &client, std::string msg);

	private:
		int								_serverSocket;
		int								_port;
		bool							_running;
		string							_password;
		std::map<int, Client>			_clientList;
		std::map<std::string, Channel>	_channelList;
		struct pollfd					_fds[CLIENT_LIMIT + 1]; // Define fds as a private member

};

		////////////////// OPERATOR OVERLOADS //////////////////
std::ostream& operator<<(std::ostream& os, std::map<int, Client>& myMap);
std::ostream& operator<<(std::ostream& os, std::map<std::string, Channel>& myChannel);

#endif
