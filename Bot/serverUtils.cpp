/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:11:55 by mfinette          #+#    #+#             */
/*   Updated: 2024/03/08 19:52:47 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

const char* RN = "\r\n";

int createSocket(void)
{
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1)
	{
		std::cerr << "Error: Failed to create socket" << std::endl;
		return -1;
	}
	return client_socket;
}

void	printCommand(Cmd cmd)
{
	if (cmd._isPRIVMSG)
	{
		std::cout << "PRIVMSG DETECTED: " << std::endl;
		std::cout << "isPRIVMSG = " << cmd._isPRIVMSG << std::endl;
		std::cout << "isForBot = " << cmd._isForBot << std::endl;
		std::cout << "fullCommand = " << cmd._fullCmd;
		std::cout << "Sender = " << cmd._sender << std::endl;
		std::cout << "isChannel = " << cmd._isChannel << std::endl;
		if (cmd._isChannel)
			std::cout << "Channel = " << cmd._channel << std::endl;
		std::cout << "Command type = " << "\"" <<cmd._cmdType << "\"" << std::endl;
		std::cout << "Command remaining = " << cmd._cmdRemaining << std::endl;
	}
}

bool connectToServer(int client_socket, int port)
{
	sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Set socket to non-blocking
	int flags = fcntl(client_socket, F_GETFL, 0);
	fcntl(client_socket, F_SETFL, flags | O_NONBLOCK);

	if (connect(client_socket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == -1 &&
			errno != EINPROGRESS)
	{
		std::cerr << "Error: Failed to connect to server" << std::endl;
		close(client_socket);
		return false;
	}
	return true;
}

void sendMessage(int client_socket, const std::string& message)
{
	send(client_socket, message.c_str(), message.length(), 0);
}

void receiveAndPrintMessage(int client_socket)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;
    bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received <= 0)
    {
        if (bytes_received == 0) {
            std::cerr << "Disconnected from server" << std::endl;
        } else {
            std::cerr << "Error in recv: " << strerror(errno) << std::endl;
        }
        return;
    }
    buffer[bytes_received] = '\0';
    std::cout << YELLOW << "" << buffer << RESET;
    Cmd cmd(buffer);
    sendResponse(client_socket, cmd);
    std::cout << RESET;
}

void handleUserInput(int client_socket)
{
	std::string message;
	std::getline(std::cin, message);
	if (message == "quit")
		return;
	std::string formattedMessage = message + RN;
	sendMessage(client_socket, formattedMessage);
}

void connectBot(int client_socket, char **argv)
{
	sendMessage(client_socket, "PASS " + std::string(argv[2]) + RN);
	sendMessage(client_socket, "NICK bot" + std::string(RN));
	sendMessage(client_socket, "USER bot 0 * :realname" + std::string(RN));
}
