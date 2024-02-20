#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "ft_irc.hpp"

class Client;

class Channel
{
	public:
		Channel(const std::string& name);
		~Channel();
		
		void	AddClient(Client* client);
		void	RemoveClient(Client* client);
		void	SendMessage(const std::string& message);
		bool	isOperator(int socket);

		void	changeOperatorStatusToOff(int socket);
		void	changeOperatorStatusToOn(int socket);
		void	changeUserLimit(int user_limit);
		void	changeInviteOnlyStatusToOn();
		void	changeInviteOnlyStatusToOff();
		void	changePasswordStatusToOn();
		void	changePasswordStatusToOff();

	private:
		std::map<Client*, bool>	_client;
		std::string				_name;
		std::string				_topic;
		std::string				_password;
		int						_user_limit;
		bool					_invite_only;
		bool					_has_password;

		// Add other channel-related data and methods as needed
};

#endif