/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:10:41 by mfinette          #+#    #+#             */
/*   Updated: 2024/02/15 19:56:17 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
#define FT_IRC_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cerr;
using std::memset;

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


class User
{
	public:
					User(int socket, const string& nickname);
					~User();
		void 		SendMessage(const string& message);
		// Add methods as needed for user management
		
	private:
		int			_socket;
		string		_nickname;
		// Add other user-related data and methods as needed
};

class Channel
{
	public:
		Channel(const std::string& name);
		~Channel();
		void AddUser(User* user);
		void RemoveUser(User* user);
		void SendMessage(const std::string& message);
		// Add methods as needed for channel management
	private:
		std::string _name;
		std::vector<User*> _users;
		// Add other channel-related data and methods as needed
};

class Command
{
	public:
		static void ParseAndExecute(const std::string& command, User* user, Server* server);
	private:
		// Add command-specific methods as needed
};


#endif // FT_IRC_HPP
