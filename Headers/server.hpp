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
		void	privmsg(std::string msg, int target, int from);
		Client	&getClientWithSocket(int socket);
		Client	&getClientWithNickname(std::string nickname);
		
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