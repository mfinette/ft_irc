#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "ft_irc.hpp"

using std::string;

class Channel;

class Client
{
	public:
		Client(int socket);
		~Client();

		Client& operator=(const Client& rhs);

		void	SendMessage(const string& message);
		// Add methods as needed for Client management
		int		getSocket() const;
		string	getNickname() const;
		string	getUsername() const;
		string	getRealname() const;
		int		getStatus() const;

		void	setSocketState(bool state);
		bool	getSocketState() const;
		void	setUsername(string username);
		void	setNickname(string nickname);
		void	setRealname(string realName);
		void	setStatus(int status);

		void 	incrementLoginStage();
		int 	getLoginStage();

	private:
		int			_socket;
		bool		_isOpen;
		string		_nickname;
		string		_username;
		string		_realname;
		int			_loginStage; //Each step increments by one this variable -> 3 means we have all infos
		std::map<std::string, Channel> l_channel;
		int			_status; //1 si log, 0 si away

		// Add other Client-related data and methods as needed
};

std::ostream	&operator<<(std::ostream &o, const Client &client);

#endif