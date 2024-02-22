#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "ft_irc.hpp"

class Client;

class Channel
{
	public:
		Channel(const std::string& name);
		~Channel();
		
		void	AddClientToChannel(Client* client);
		void	RemoveClientFromChannel(Client* client);
		void	SendMessage(const std::string& message);
		bool	isOperator(int socket);

		std::string	getName();
		std::string	getTopic();
		std::string	getTopicAuthor();
		std::string	getPassword();
		std::string	getSetAt();
		bool		isInviteOnly();
		bool		hasPassword();
		int			getUserLimit();

		int		nbClient();

		void	changeOperatorStatusToOff(int socket);
		void	changeOperatorStatusToOn(int socket);
		void	changeUserLimit(int user_limit);
		void	changeInviteOnlyStatusToOn();
		void	changeInviteOnlyStatusToOff();
		void	changePasswordStatusToOn();
		void	changePasswordStatusToOff();

		bool	isClientInChannel(int socket);

	private:
		std::map<Client *, bool>	_client;
		std::string				_name;
		std::string				_topic;
		std::string				_topic_author;
		std::string				_password;
		std::time_t				_setAt;
		int						_user_limit;
		bool					_invite_only;
		bool					_has_password;

		// Add other channel-related data and methods as needed
};

#endif