/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingUtils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:53:42 by mfinette          #+#    #+#             */
/*   Updated: 2024/03/08 19:53:48 by mfinette         ###   ########.fr       */
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
	std::string newStr;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] != '\r' && str[i] != '\n')
			newStr += str[i];
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