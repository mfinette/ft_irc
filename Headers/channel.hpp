#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "user.hpp"

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

#endif