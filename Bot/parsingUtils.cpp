/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingUtils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:53:42 by mfinette          #+#    #+#             */
/*   Updated: 2024/03/09 12:18:37 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

std::string	getFirstWord(std::string str)
{
	std::istringstream iss(str);
	std::string word;
	std::getline(iss, word, ' ');
	return word;
}

std::string	getSecondWord(std::string str)
{
	std::istringstream iss(str);
	std::string word;
	std::getline(iss, word, ' ');
	std::getline(iss, word, ' ');
	return word;
}

std::string	getRemaining(std::string str)
{
	std::istringstream iss(str);
	std::string word;
	std::getline(iss, word, ' ');
	std::getline(iss, word, ' ');
	std::getline(iss, word, '\r');
	return word;
}

std::string removeBackslashR(std::string str)
{
	std::string newStr;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] != '\r')
			newStr += str[i];
	}
	return newStr;
}

std::string removeBackslashRN(std::string str)
{
	std::string newStr = str;
	size_t length = newStr.length();
	while (length > 0 && (newStr[length - 1] == '\r' || newStr[length - 1] == '\n'))
	{
		newStr.erase(length - 1);
		length--;
	}
	return newStr;
}

std::string	getFirstWordAfter2Colons(std::string str)
{
	std::istringstream iss(str);
	std::string word;
	std::getline(iss, word, ':');
	std::getline(iss, word, ':');
	std::getline(iss, word, ' ');
	return word;
}