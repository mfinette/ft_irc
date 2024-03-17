/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:51:20 by mfinette          #+#    #+#             */
/*   Updated: 2024/03/17 23:08:16 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#define EDEN_API_KEY "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VyX2lkIjoiMjY4NjM4OWItNGNiZi00MjQ1LWFkNmUtNGU3MTRhNTVjZjFkIiwidHlwZSI6ImFwaV90b2tlbiJ9.0vxsfoZQj8LBx0hYxnOX0uestYC3aTWvhedi9BTWj74"
#define EDEN_API_ENDPOINT "https://api.edenai.run/v2/image/generation"

std::string extract_image_url(const std::string& data) {
    std::string url;
    std::string search_str = "\"image_resource_url\":\"";
    size_t start_index = data.find(search_str);
    if (start_index == std::string::npos)
        return url;  // If the substring is not found, return an empty string
    start_index += search_str.length();
    size_t end_index = data.find("\"", start_index);
    if (end_index == std::string::npos)
        return url;  // If the closing quote is not found, return an empty string
    url = data.substr(start_index, end_index - start_index);
    return url;
}

std::string getImageFromAPI(const char *prompt)
{
    std::string jsonData = "{\"response_as_dict\":true,\"attributes_as_list\":false,\"show_original_response\":false,\"resolution\":\"1024x1024\",\"num_images\":1,\"providers\":\"deepai\",\"text\":\"" + std::string(prompt) + "\"}";
    std::string command = "curl -s -X POST -H \"accept: application/json\" -H \"content-type: application/json\" -H \"Authorization: Bearer " + std::string(EDEN_API_KEY) + "\" -d '" + jsonData + "' " + std::string(EDEN_API_ENDPOINT);
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        std::cerr << "Error popen()" << std::endl;
        return "Error when using popen function";
    }
    char buffer[256];
    std::string response;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
        response += buffer;
    pclose(pipe);
	return extract_image_url(response);
}
