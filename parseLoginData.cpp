#include "Headers/ft_irc.hpp"

bool isPassCmdValid(string input, string servPassword) {
	std::istringstream iss(input);
	string word;
	while (std::getline(iss, input))
	{
		if (input == "CAP LS 302")
			std::getline(iss, input);
		std::istringstream tokens(input);
		tokens >> word;
		if (word == "PASS") {
			tokens >> word;
			if (word == servPassword)
				return true;
			// else PASSWDMISMATCH
		}
	}
	return false;
}

bool isNickCmdValid(string input) {
	std::istringstream iss(input);
	string word;
	// A FAIRE : Check si qq a pas deja le meme sinon erreur
	while (std::getline(iss, input))
	{
		std::istringstream tokens(input);
		tokens >> word;
		if (word == "NICK") {
			tokens >> word;
			if (word.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ\
			abcdefghijklmnopqrstuvwxyz0123456789[]{}\\|") == std::string::npos) {
				return true;
			}
			// else ERR_ERRONEUSNICKNAME 				
		}
	}
	return false;
}

bool isUserCmdValid(string input) {
	std::istringstream iss(input);
	string word;
	while (std::getline(iss, input))
	{
		std::istringstream tokens(input);
		tokens >> word;
		if (word == "USER") {
			tokens >> word;
			if (word.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ\
			abcdefghijklmnopqrstuvwxyz0123456789[]{}\\|") == std::string::npos) {
				return true;
			}
		}
	}
	return false;
}

void getLoginData(string input, Client &client, Server &server) {
	if (client.getLoginStage() == 0) {
		if (isPassCmdValid(input, server.getServPassword()))
			client.incrementLoginStage();
	}
	if (client.getLoginStage() == 1) {
		if (isNickCmdValid(input)) {
			client.incrementLoginStage(); // & exec Nick cmd
			cout << "input" << input << endl;
			Command command(input, server);
			command.execNICK(client);
		}
	}
	if (client.getLoginStage() == 2) {
		if (isUserCmdValid(input))
			client.incrementLoginStage(); // & exec User cmd
	}
	cout << client.getLoginStage() << endl;

}