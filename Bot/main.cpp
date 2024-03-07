/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:31:35 by mfinette          #+#    #+#             */
/*   Updated: 2024/03/07 17:32:17 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <cerrno>

# define RESET				"\033[0m"
# define BLACK				"\033[30m"
# define RED				"\033[31m"
# define GREEN				"\033[32m"
# define YELLOW				"\033[33m"
# define BLUE				"\033[34m"
# define DARK_BLUE			"\033[34m"
# define MEDIUM_BLUE		"\033[36m"
# define DODGER_BLUE		"\033[94m"
# define STEEL_BLUE			"\033[38;5;67m"
# define MAGENTA			"\033[35m"
# define CYAN				"\033[36m"
# define WHITE				"\033[37m"
# define LIGHT_PINK			"\033[38;5;217m"
# define MEDIUM_PINK		"\033[38;5;219m"
# define DARK_PINK			"\033[38;5;205m"
# define PALE_PINK			"\033[38;5;218m"
# define HOT_PINK			"\033[38;5;205m"
# define BABY_PINK			"\033[38;5;225m"
# define NEON_PINK			"\033[38;5;207m"

const int BUFFER_SIZE = 1024;
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
		if (errno != EWOULDBLOCK)
		{
			std::cerr << "Disconnected from server" << std::endl;
			return;
		}
	}
	buffer[bytes_received] = '\0';
	std::cout << YELLOW << "Server: " << buffer << RESET;
}

void handleUserInput(int client_socket)
{
	std::string message;
	std::cout << "bot > ";
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

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port_number> <server_password>" << std::endl;
		return 1;
	}
	int port = atoi(argv[1]);
	if (port <= 0 || port > 65535)
	{
		std::cerr << "Invalid port number" << std::endl;
		return 1;
	}
	int client_socket = createSocket();
	if (client_socket == -1)
		return 1;
	if (!connectToServer(client_socket, port))
		return 1;
	std::cout << "Connected to server. Type 'quit' to exit." << std::endl;
	connectBot(client_socket, argv);
	struct pollfd fds[2];
	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLIN;
	fds[1].fd = client_socket;
	fds[1].events = POLLIN;
	while (true)
	{
		int ret = poll(fds, 2, -1);
		if (ret == -1)
		{
			std::cerr << "Error in poll" << std::endl;
			break;
		}
		if (fds[0].revents & POLLIN)
			handleUserInput(client_socket);
		if (fds[1].revents & POLLIN)
			receiveAndPrintMessage(client_socket);
	}

	close(client_socket);
	return 0;
}


