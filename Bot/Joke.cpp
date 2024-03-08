/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Joke.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:18:37 by mfinette          #+#    #+#             */
/*   Updated: 2024/03/08 20:25:28 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

#define PORT 80
#define HOST "v2.jokeapi.dev"
#define REQUEST "GET /joke/Any HTTP/1.1\r\nHost: v2.jokeapi.dev\r\n\r\n"

std::string fetchJoke() {
    int sockfd, bytes_read;
    char buffer[1024];
    struct sockaddr_in serv_addr;
    struct hostent *server;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error opening socket" << std::endl;
        return "";
    }

    // Resolve hostname
    server = gethostbyname(HOST);
    if (server == NULL) {
        std::cerr << "Error, no such host" << std::endl;
        return "";
    }

    // Configure server address structure
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    // Connect to server
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Error connecting to server" << std::endl;
        return "";
    }

    // Send HTTP request
    if (send(sockfd, REQUEST, strlen(REQUEST), 0) < 0) {
        std::cerr << "Error sending request" << std::endl;
        return "";
    }

    // Read response
    std::string response;
    while ((bytes_read = recv(sockfd, buffer, sizeof(buffer), 0)) > 0) {
        response.append(buffer, bytes_read);
    }

    // Close socket
    close(sockfd);

    // Extract joke from response
    std::string joke;
    size_t joke_start = response.find("\r\n\r\n");
    if (joke_start != std::string::npos) {
        joke_start += 4; // Move past the empty line
        joke = response.substr(joke_start);
    }
    return joke;
}