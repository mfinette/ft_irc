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
		void	privmsg(std::string msg, std::string target, int from);
		void	join();
		Client	&getClient(int socket);
		Client	&getClient(std::string nickname);
		bool	isClientAway(int socket);
		bool	isClientAway(std::string nickname);
		bool	channelExisting(std::string channel_name);
		string 	getServPassword();

	private:
		int								_serverSocket;
		int								_port;
		bool							_running;
		string							_password;
		std::map<int, Client>			l_client;
		std::map<std::string, Channel>	l_channel;

		void		bindServerSocket(int serverSocket, int port);
		void		listenForConnections(int serverSocket, int backlog);
		int			acceptClientConnection(int serverSocket, sockaddr_in& clientAddr);
		void		handleClient(int clientSocket);
		void		handleServer(int serverSocket, struct pollfd fds[], int& numClients, const int MAX_CLIENTS);
		void		closeSocket(int socket);
};

std::ostream& operator<<(std::ostream& os, std::map<int, Client>& myMap);

#endif