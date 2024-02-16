#ifndef USER_HPP
#define USER_HPP

#include "ft_irc.hpp"

using std::string;

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

#endif