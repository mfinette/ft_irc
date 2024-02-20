#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "ft_irc.hpp"

using std::string;

class Channel;

class Client
{
	public:
		Client(int socket, const string& nickname);
		~Client();
		void	SendMessage(const string& message);
		// Add methods as needed for Client management
		int		getSocket() const;
		string	getNickname() const;
		string	getUsername() const;

		void	setUsername(string username);
		void	setNickname(string nickname);
		
	private:
		int			_socket;
		string		_nickname;
		string		_username;
		std::map<std::string, Channel> l_channel;

		// Add other Client-related data and methods as needed
};

#endif