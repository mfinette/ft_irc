/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:51:45 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/20 19:51:01 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"

std::ostream& operator<<(std::ostream& os, std::map<int, Client>& myMap)
{
	for (std::map<int, Client>::const_iterator it = myMap.begin(); it != myMap.end(); ++it) {
		os << "socket : " << it->first << " " << it->second << endl;
	}
	return os;
}

Server::Server(int port, string password) : _serverSocket(-1) , _port(port), _password(password) 
{
}
 
Server::~Server()
{
	if (_serverSocket != -1)
		close(_serverSocket);
}

void	Server::bindServerSocket(int serverSocket, int port)
{
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(port);
	if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		cerr << "Error binding socket: " << strerror(errno) << endl;
		closeSocket(serverSocket);
		exit(EXIT_FAILURE);
	}
}

void	Server::listenForConnections(int serverSocket, int backlog)
{
	if (listen(serverSocket, backlog) < 0)
	{
		cerr << "Error listening on socket: " << strerror(errno) << endl;
		closeSocket(serverSocket);
		exit(EXIT_FAILURE);
	}
}

int	Server::acceptClientConnection(int serverSocket, sockaddr_in& clientAddr)
{
	socklen_t clientAddrLen = sizeof(clientAddr);
	int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
	return clientSocket;
}

void Server::handleClient(int clientSocket)
{
	char buffer[1024];
	int bytesRead;

	while (true)
	{
		// Receive message from client
		bytesRead = recv(clientSocket, buffer, sizeof(buffer), MSG_DONTWAIT);
		if (bytesRead > 0)
		{
			// Print message received from client
			cout << PALE_PINK << string(buffer, bytesRead) << RESET;
		//	if (clientSocket != 4)
		//		this->privmsg(buffer, 4, clientSocket);
			break;
		}
		else if (bytesRead == 0)
		{
			// Client disconnected
			cout << "Client disconnected (" << clientSocket << ")" << endl;
			// Close client socket
			closeSocket(clientSocket);
			break;
		}
		else if (errno == EAGAIN || errno == EWOULDBLOCK)
		{
			// No data available, continue polling
			continue;
		}
		else
		{
			// Error receiving message
			cerr << "Error receiving message: " << strerror(errno) << endl;
			break;
		}
	}
}

void	Server::closeSocket(int socket)
{
	close(socket);
}

void Server::handleServer(int serverSocket, struct pollfd fds[], int& numClients, const int MAX_CLIENTS)
{
	// Check for events on server socket
	sockaddr_in clientAddr;
	int clientSocket = acceptClientConnection(serverSocket, clientAddr);
	if (clientSocket < 0)
	{
		cerr << "Error accepting connection: " << strerror(errno) << endl;
		closeSocket(serverSocket);
		return;
	}
	cout << "Client connected (" << clientSocket << ")" << endl;
	test_send(clientSocket);
	// Add the new client socket to the set of file descriptors to monitor
	if (numClients + 1 >= MAX_CLIENTS)
	{
		// Check if maximum number of clients reached
		cerr << "Maximum number of clients reached" << endl;
		closeSocket(serverSocket);
		return;
	}
	fds[numClients + 1].fd = clientSocket; // Start from index 1
	fds[numClients + 1].events = POLLIN;
	fds[numClients + 1].revents = 0;
	Client	tmp(clientSocket, static_cast<const string>("nickname"));
	this->l_client.insert(std::make_pair(clientSocket, tmp));
	numClients++;
	cout << l_client;
}

void Server::start(void)
{
	int opt = 1;

	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0)
	{
		cerr << "Error creating socket: " << strerror(errno) << endl;
		return;
	}
	if( setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )   
    {   
        cerr << "setsockopt" << std::endl;   
        exit(EXIT_FAILURE);   
    }   
	bindServerSocket(serverSocket, this->_port);
	listenForConnections(serverSocket, 10);
	cout << "Server listening on port " << this->_port << endl;
	const int MAX_CLIENTS = 10; // Maximum number of clients
	struct pollfd fds[MAX_CLIENTS + 1]; // +1 for server socket
	fds[0].fd = serverSocket;
	fds[0].events = POLLIN;
	int numClients = 0; // Number of connected clients
	while (true)
	{
		int ret = poll(fds, numClients + 1, -1);
		if (ret == -1)
		{
			cerr << "Error in poll: " << strerror(errno) << endl;
			closeSocket(serverSocket);
			return;
		}
		if (fds[0].revents & POLLIN)
			handleServer(serverSocket, fds, numClients, MAX_CLIENTS);
		// Check for events on client sockets
		for (int i = 1; i <= numClients; ++i)
		{
			if (fds[i].revents & POLLIN)
				handleClient(fds[i].fd);
		}
	}
}

void	Server::setup()
{
}

Client&	Server::getClientWithSocket(int socket){
	std::map<int, Client>::iterator it;
	std::map<int, Client>::iterator ite = this->l_client.end();

	for(it = l_client.begin(); it != l_client.end(); ++it){
		if (it->first == socket)
			return it->second;
	}
	return ite->second;
}

Client&	Server::getClientWithNickname(std::string nickname){
	std::map<int, Client>::iterator it;
	std::map<int, Client>::iterator ite = this->l_client.end();

	for(it = l_client.begin(); it != l_client.end(); ++it){
		if (it->second.getNickname() == nickname)
			return it->second;
	}
	return ite->second;
}
