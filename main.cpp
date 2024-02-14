/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:09:36 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/13 17:43:14 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

int main()
{
	// Create a socket
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0)
	{
		std::cerr << "Error creating socket\n";
		return 1;
	}

	// Bind the socket to an IP address and port
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // Listen on all available interfaces
	serverAddr.sin_port = htons(12346); // Port number, change to desired port

	if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		std::cerr << "Error binding socket\n";
		return 1;
	}

	// Listen for incoming connections
	if (listen(serverSocket, 10) < 0)
	{
		std::cerr << "Error listening on socket\n";
		return 1;
	}

	std::cout << "Server listening on port 12345\n";

	// Accept incoming connections and continuously receive messages
	while (true)
	{
		// Accept incoming connections
		struct sockaddr_in clientAddr;
		socklen_t clientAddrLen = sizeof(clientAddr);
		int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
		if (clientSocket < 0)
		{
			std::cerr << "Error accepting connection\n";
			return 1;
		}

		std::cout << "Client connected\n";

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
		{
			// Client disconnected
			std::cout << "Client disconnected\n";
		} else if (bytesRead < 0)
		{
			// Error receiving message
			std::cerr << "Error receiving message\n";
		}

		// Close the client socket
		close(clientSocket);
	}

	// Close the server socket (never reached in this code)
	close(serverSocket);

	return 0;
}


