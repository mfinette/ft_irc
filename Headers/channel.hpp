#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "ft_irc.hpp"

class Client;

class Channel
{
	public:
		Channel(const std::string& name);
		~Channel();
		void AddUser(Client* client);
		void RemoveUser(Client* client);
		void SendMessage(const std::string& message);
		// Add methods as needed for channel management
	private:
		std::map<Client*, bool>	_client;
		std::string				_name;
		std::string				_topic;
		std::string				_password;
	//	int						_user_limit;
	//	bool					_invite_only;
	//	bool					_has_password;

		// Add other channel-related data and methods as needed
};

#endif