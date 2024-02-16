/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:51:45 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/16 16:24:42 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"

Server::Server(int port) : _serverSocket(-1)
{
	(void)port;
}

Server::~Server()
{
	if (_serverSocket != -1)
		close(_serverSocket);
}

void Server::bindServerSocket(int serverSocket, int port)
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

void Server::listenForConnections(int serverSocket, int backlog)
{
	if (listen(serverSocket, backlog) < 0)
	{
		cerr << "Error listening on socket: " << strerror(errno) << endl;
		closeSocket(serverSocket);
		exit(EXIT_FAILURE);
	}
}

int Server::acceptClientConnection(int serverSocket, sockaddr_in& clientAddr)
{
	socklen_t clientAddrLen = sizeof(clientAddr);
	int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
	return clientSocket;
}

void Server::handleClient(int clientSocket)
{
	char buffer[1024];
	int bytesRead;
	while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0)
	{
		cout << "Received message: " << string(buffer, bytesRead);
		send(clientSocket, buffer, bytesRead, 0); // Echo back to the client
	}
	if (bytesRead == 0)
		cout << "Client disconnected" << endl;
	else if (bytesRead < 0)
		cerr << "Error receiving message: " << strerror(errno) << endl;
}

void Server::closeSocket(int socket)
{
	close(socket);
}

void Server::start(int port)
{
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0)
	{
		cerr << "Error creating socket: " << strerror(errno) << endl;
		return;
	}
	bindServerSocket(serverSocket, port);
	listenForConnections(serverSocket, 10);
	cout << "Server listening on port " << port << endl;
	while (true)
	{
		sockaddr_in clientAddr;
		int clientSocket = acceptClientConnection(serverSocket, clientAddr);
		if (clientSocket < 0)
		{
			cerr << "Error accepting connection: " << strerror(errno) << endl;
			closeSocket(serverSocket);
			return;
		}
		cout << "Client connected" << endl;
		handleClient(clientSocket);
		closeSocket(clientSocket);
	}
}
