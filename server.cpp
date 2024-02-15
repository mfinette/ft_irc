/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:51:45 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/15 14:30:11 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Server::Server() : serverSocket(-1)
{
}

Server::~Server()
{
    if (serverSocket != -1)
        close(serverSocket);
}

void Server::start(int port)
{
	// Create a socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0)
	{
		std::cerr << "Error creating socket: " << strerror(errno) << std::endl;
		return;
	}
	// Bind the socket to an IP address and port
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // Listen on all available interfaces
	serverAddr.sin_port = htons(port); // Port number, change to desired port
	if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		std::cerr << "Error binding socket: " << strerror(errno) << std::endl;
		close(serverSocket);
		return;
	}
	// Listen for incoming connections
	if (listen(serverSocket, 10) < 0)
	{
		std::cerr << "Error listening on socket: " << strerror(errno) << std::endl;
		close(serverSocket);
		return;
	}
	std::cout << "Server listening on port " << port << std::endl;
	// Accept incoming connections and continuously receive messages
	while (true)
	{
		// Accept incoming connections
		struct sockaddr_in clientAddr;
		socklen_t clientAddrLen = sizeof(clientAddr);
		int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
		if (clientSocket < 0)
		{
			std::cerr << "Error accepting connection: " << strerror(errno) << std::endl;
			close(serverSocket);
			return;
		}
		std::cout << "Client connected" << std::endl;
		// Receive messages from the client
		char buffer[1024];
		int bytesRead;
		while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0)
		{
			std::cout << "Received message: " << std::string(buffer, bytesRead);
			// Echo the message back to the client (optional)
			send(clientSocket, buffer, bytesRead, 0);
		}
		if (bytesRead == 0)
			std::cout << "Client disconnected" << std::endl;
		else if (bytesRead < 0)
			std::cerr << "Error receiving message: " << strerror(errno) << std::endl;
		// Close the client socket
		close(clientSocket);
	}
}
