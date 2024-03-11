/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funFact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:39:07 by maxime            #+#    #+#             */
/*   Updated: 2024/03/11 21:44:22 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

static	int getRandomNumber()
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	return std::rand() % 101;
}

std::string fetchFunFact()
{
	std::ifstream file("funfactsvault.txt");
	std::vector<std::string> funfacts;
	std::string line;

	if (file.is_open())
	{
		while (std::getline(file, line))
			funfacts.push_back(line);
		file.close();
	}

	if (funfacts.empty())
		return "No fun facts found in the funfactsvault.txt file.";
	std::string funfact = funfacts[getRandomNumber()];
	size_t index = funfact.find_first_of("0123456789");
	while (index != std::string::npos)
	{
		funfact = funfact.substr(0, index) + funfact.substr(index + 1);
		index = funfact.find_first_of("0123456789");
	}
	funfact = funfact.substr(2);
	return funfact;
}