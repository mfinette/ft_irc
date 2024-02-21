#ifndef SERVER_HPP
#define SERVER_HPP

#include "ft_irc.hpp"

class Server
{
	public:
		Server(int port, string password);
		~Server();
		void	start();
		void	setup();
		void	stop();
		
		Client	&getClient(int socket);
		Client	&getClient(std::string nickname);
		Channel	&getChannel(std::string name);
		void	addClientToServer(int socket, Client& client, string nickname);
		void	removeClientFromServer(Client& client);
		void	addChannelToServer(string name, Channel& channel);
		void	removeChannelFromServer(string name, Channel& channel);
		bool	isClientAway(int socket);
		bool	isClientAway(std::string nickname);
		bool	channelExisting(std::string channel_name);
		
		string 	getServPassword();
		void printClientMap();

	private:
		int								_serverSocket;
		int								_port;
		bool							_running;
		string							_password;
		std::map<int, Client>			_clientList;
		std::map<std::string, Channel>	_channelList;

		void		bindServerSocket(int serverSocket, int port);
		void		listenForConnections(int serverSocket, int backlog);
		int			acceptClientConnection(int serverSocket, sockaddr_in& clientAddr);
		void		handleClient(int clientSocket);
		void		handleServer(int serverSocket, struct pollfd fds[], int& numClients, const int MAX_CLIENTS);
		void		closeSocket(int socket);

};

std::ostream& operator<<(std::ostream& os, std::map<int, Client>& myMap);

#endif
