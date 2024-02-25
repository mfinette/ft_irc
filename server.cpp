/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:51:45 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/25 10:02:33 by mfinette         ###   ########.fr       */
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
	if (_serverSocket != -1)
		close(_serverSocket);
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
			else {
				execCMD(string(buffer, bytesRead), getClient(clientSocket), *this);
			}
			break;
		}
		else if (bytesRead == 0)
		{
			// Client disconnected
			cout << "Client disconnected (" << clientSocket << ")" << endl;
			// Remove client from list
			removeClientFromServer(client);
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

void Server::handleServer(int serverSocket, int& numClients)
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
	// Add the new client socket to the set of file descriptors to monitor
	if (numClients + 1 >= CLIENT_LIMIT)
	{
		// Check if maximum number of clients reached
		cerr << "Maximum number of clients reached" << endl;
		closeSocket(serverSocket);
		return;
	}
	this->_fds[numClients + 1].fd = clientSocket; // Start from index 1
	this->_fds[numClients + 1].events = POLLIN;
	this->_fds[numClients + 1].revents = 0;
	this->setupClient(clientSocket);
	numClients++;
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
	if(setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
	{
		cerr << "setsockopt" << std::endl;   
		exit(EXIT_FAILURE);   
	}
	// Bind server socket to port
	bindServerSocket(serverSocket, this->_port);
	// Listen for connections on server socket
	listenForConnections(serverSocket, 10);
	cout << "Server listening on port " << this->_port << endl;
	_fds[SERVER].fd = serverSocket;
	_fds[SERVER].events = POLLIN;
	int numClients = 0; // Number of connected clients
	while (true)
	{
		// Poll for events and revents in every fd (POLLIN == data to read)
		int ret = poll(_fds, numClients + 1, -1);
		if (ret == -1)
		{
			cerr << "Error in poll: " << strerror(errno) << endl;
			closeSocket(serverSocket);
			return;
		}
		// Check for events on server socket (new client connection)
		if (_fds[SERVER].revents & POLLIN)
			handleServer(serverSocket, numClients);
		// Check for events on client sockets (message received / client disconnected)
		for (int i = 1; i <= numClients; ++i)
			if (_fds[i].revents & POLLIN)
				handleClient(_fds[i].fd);
	}
}

void	Server::closeServer()
{
	for (std::map<int, Client>::iterator it = _clientList.begin(); it != _clientList.end(); ++it)
		closeSocket(it->first);
	closeSocket(_serverSocket);
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

