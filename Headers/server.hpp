#ifndef SERVER_HPP
#define SERVER_HPP

#include "ft_irc.hpp"

class Server
{
	public:
					Server(int port);
					~Server();
		void		start(int port);
		void		stop();
		
	private:
		int			_serverSocket;
		int			_port;
		bool		_running;

		void		bindServerSocket(int serverSocket, int port);
		void		listenForConnections(int serverSocket, int backlog);
		int			acceptClientConnection(int serverSocket, sockaddr_in& clientAddr);
		void		handleClient(int clientSocket);
		void		closeSocket(int socket);
};

#endif