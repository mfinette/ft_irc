/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:51:45 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/26 13:07:26 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/ft_irc.hpp"
#include <iomanip>

std::ostream& operator<<(std::ostream& os, std::map<int, Client>& myMap)
{
	for (std::map<int, Client>::const_iterator it = myMap.begin(); it != myMap.end(); ++it) {
		os << "|Socket : " << std::setw(1) << it->first << " |Nick : " << std::setw(8) << it->second << " |Username : " << std::setw(5) << it->second.getUsername() << " |RealName : " << std::setw(5) << it->second.getRealname() << endl;
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, std::map<std::string, Channel>& myChannel)
{
	for (std::map<std::string, Channel>::const_iterator it = myChannel.begin(); it != myChannel.end(); ++it) {
		os << "channel : " << it->first << " " << it->second << endl;
	}
	return os;
}

Server::Server(int port, string password) : _serverSocket(-1) , _port(port), _password(password) 
{
}

Server::~Server()
{
}

string Server::getServPassword()
{
	return _password;
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
		closeServer();
		exit(EXIT_FAILURE);
	}
}

void	Server::listenForConnections(int serverSocket, int backlog)
{
	if (listen(serverSocket, backlog) < 0)
	{
		cerr << "Error listening on socket: " << strerror(errno) << endl;
		closeServer();
		exit(EXIT_FAILURE);
	}
}

int	Server::acceptClientConnection(int serverSocket, sockaddr_in& clientAddr)
{
	socklen_t clientAddrLen = sizeof(clientAddr);
	int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
	return clientSocket;
}

void	Server::handleClient(int clientSocket, int &numClients)
{
	char buffer[1024];
	int bytesRead;
	Client client = getClient(clientSocket);
	while (true)
	{
		// Receive message from client
		bytesRead = recv(clientSocket, buffer, sizeof(buffer), MSG_DONTWAIT);
		if (bytesRead > 0)
		{
			// Print message received from client
			cout << PALE_PINK << string(buffer, bytesRead) << RESET;
			if (client.getLoginStage() != ALL_LOGIN_DATA_ENTERED)
				getLoginData(string(buffer, bytesRead), getClient(clientSocket), *this);
			else
				execCMD(string(buffer, bytesRead), getClient(clientSocket), *this);
			break;
		}
		else if (bytesRead == 0)
		{
			// Client disconnected
			cout << BLUE << "Client disconnected (" << clientSocket << ")" << RESET << endl;
			numClients--;
			// Close client socket
			closeClientSocket(client);
			client.setSocketState(false);
			// Remove client from list
			removeClientFromServer(client);
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
			continue;
		}
	}
}

void	Server::closeClientSocket(Client &client)
{
	cout << BLUE << "Client socket (" << client.getSocket() << ") : " << client.getSocketState() << RESET << endl;
	if (client.getSocketState() == true)
	{
		cout << BLUE << "Closing client socket " << client.getSocket() << RESET << endl;
		close(client.getSocket());
	}
	else
		cout << BLUE << "Client socket already closed" << RESET << endl;
}

void	Server::closeServerSocket(int socket)
{
	cout << BLUE << "Closing server socket : " << socket << RESET << endl;
	close(socket);
}

void Server::handleServer(int serverSocket, int& numClients, pollfd fds[])
{
	// Check for events on server socket
	sockaddr_in clientAddr;
	int clientSocket = acceptClientConnection(serverSocket, clientAddr);
	if (clientSocket < 0)
	{
		cerr << RED << "Error accepting connection: " << strerror(errno) << RESET << endl;
		closeServer();
		return ;
	}
	cout << COLOR_1 << "USER ("  << COLOR_2 << clientSocket << COLOR_1 << ") APPEARED, WAITING FOR AUTHENTICATION : " << RESET << endl;
	// Add the new client socket to the set of file descriptors to monitor
	if (numClients + 1 >= CLIENT_LIMIT)
	{
		// Check if maximum number of clients reached
		cerr << RED << "Maximum number of clients reached" << RESET << endl;
		closeServer();
		return ;
	}
	fds[numClients + 1].fd = clientSocket; // Start from index 1
	fds[numClients + 1].events = POLLIN;
	fds[numClients + 1].revents = 0;
	this->setupClient(clientSocket);
	numClients++;
}

void Server::start(void)
{
	int opt = 1;

	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0)
	{
		cerr << BLUE << "Error creating socket: " << strerror(errno) << RESET << endl;
		return;
	}
	if(setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
	{
		cerr << "setsockopt" << std::endl;   
		exit(EXIT_FAILURE);   
	}
	_serverSocket = serverSocket;
	// Bind server socket to port
	bindServerSocket(_serverSocket, this->_port);
	// Listen for connections on server socket
	listenForConnections(_serverSocket, 10);
	cout << MAGENTA << "Server listening on port " << this->_port << RESET << endl;
	struct pollfd fds[CLIENT_LIMIT + 1];
	fds[SERVER].fd = serverSocket;
	cout << BLUE << "serverSocket = " << serverSocket << RESET << endl;
	fds[SERVER].events = POLLIN;
	int numClients = 0; // Number of connected clients
	while (true)
	{
		// Poll for events and revents in every fd (POLLIN == data to read)
		int ret = poll(fds, numClients + 1, -1);
		if (ret == -1)
		{
			cerr << BLUE << "Error in poll: " << strerror(errno) << RESET << endl;
			closeServer();
			return;
		}
		// Check for events on server socket (new client connection)
		if (fds[SERVER].revents & POLLIN)
			handleServer(serverSocket, numClients, fds);
		// Check for events on client sockets (message received / client disconnected)
		for (int i = 1; i <= numClients; ++i)
			if (fds[i].revents & POLLIN)
				handleClient(fds[i].fd, numClients);
	}
}

void	Server::closeServer()
{
	for (std::map<int, Client>::iterator it = _clientList.begin(); it != _clientList.end(); ++it)
		closeClientSocket(it->second);
	closeServerSocket(_serverSocket);
}

Client&	Server::getClient(int socket)
{
	std::map<int, Client>::iterator it;
	std::map<int, Client>::iterator ite = this->_clientList.end();

	for(it = _clientList.begin(); it != _clientList.end(); ++it)
		if (it->first == socket)
			return it->second;
	return ite->second;
}

Client&	Server::getClient(std::string nickname)
{
	std::map<int, Client>::iterator it;
	std::map<int, Client>::iterator ite = this->_clientList.end();

	for(it = _clientList.begin(); it != _clientList.end(); ++it)
		if (it->second.getNickname() == nickname)
			return it->second;
	return ite->second;
}

Channel	&Server::getChannel(std::string name)
{
	std::map<std::string, Channel>::iterator it;
	std::map<std::string, Channel>::iterator ite = this->_channelList.end();

	for(it = _channelList.begin(); it != _channelList.end(); ++it)
		if (it->first == name)
			return it->second;
	return ite->second;
}

bool	Server::isClientLog(int socket){
	std::map<int, Client>::iterator it;

	for(it = _clientList.begin(); it != _clientList.end(); ++it){
		if (it->first == socket)
			return true;
	}
	return false;
}

bool	Server::isClientLog(std::string nickname){
	std::map<int, Client>::iterator it;

	for(it = _clientList.begin(); it != _clientList.end(); ++it){
		if (it->second.getNickname() == nickname)
			return true;
	}
	return false;
}

bool	Server::getClientStatus(int socket){
	std::map<int, Client>::iterator it;

	for(it = _clientList.begin(); it != _clientList.end(); ++it){
		if (it->first == socket)
			return it->second.getStatus();
	}
	return false;
}

bool	Server::getClientStatus(std::string nickname){
	std::map<int, Client>::iterator it;

	for(it = _clientList.begin(); it != _clientList.end(); ++it){
		if (it->second.getNickname() == nickname)
			return it->second.getStatus();
	}
	return false;
}


bool	Server::channelExisting(std::string channel_name)
{
	std::map<std::string, Channel>::iterator it;

	for(it = _channelList.begin(); it != _channelList.end(); ++it)
		if (it->first == channel_name)
			return true;
	return false;
}

void Server::printClientMap()
{
	cout << this->_clientList << endl;
}

std::map<int, Client> &Server::getClientList()
{
	return _clientList;
}
