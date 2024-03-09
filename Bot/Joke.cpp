/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Joke.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:18:37 by mfinette          #+#    #+#             */
/*   Updated: 2024/03/09 12:41:49 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

#include <fstream>
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

int getRandomNumber() {
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(0)));

    // Generate a random number from 0 to 49
    return std::rand() % 50;
}

std::string fetchJoke() {
    std::ifstream file("jokevault.txt");
    std::vector<std::string> jokes;
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            jokes.push_back(line);
        }
        file.close();
    }

    if (jokes.empty()) {
        return "No jokes found in the jokevault.txt file.";
    }
    std::string joke = jokes[getRandomNumber()];
    size_t index = joke.find_first_of("0123456789");
    while (index != std::string::npos) {
        joke = joke.substr(0, index) + joke.substr(index + 1);
        index = joke.find_first_of("0123456789");
    }
    joke = joke.substr(2);
    return joke;
}

