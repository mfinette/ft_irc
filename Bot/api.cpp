/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:51:20 by mfinette          #+#    #+#             */
/*   Updated: 2024/03/18 19:03:45 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

#define EDEN_API_KEY "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VyX2lkIjoiMmMzMzNiYmQtMjk4OS00ZWMyLWJmYmYtZGY3YzFmN2RiNmViIiwidHlwZSI6ImZyb250X2FwaV90b2tlbiJ9.t9j8enV6eu91ifok9d0JwhvbJNV9REKNvnRex1LNr8Y"
#define EDEN_API_IMAGE_ENDPOINT "https://api.edenai.run/v2/image/generation"
#define EDEN_API_CHATBOT_ENDPOINT "https://api.edenai.run/v2/text/chat"

std::string extract_image_url(const std::string& data)
{
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
std::string extractText(const std::string& data)
{
	std::string url;
	std::string search_str = "\"generated_text\":\"";
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
	std::string providers = "openai";
	std::string model = "dall-e-3";
	std::string resolution = "1024x1024";
	std::string jsonData = "{\"response_as_dict\":true,\"attributes_as_list\":false,\"show_original_response\":false,\"resolution\":\"" + resolution + "\",\"num_images\":1,\"providers\":\"" + providers + "\",\"text\":\"" + std::string(prompt) + "\",\"model\":\"" + model + "\"}";
	std::string command = "curl -s -X POST -H \"accept: application/json\" -H \"content-type: application/json\" -H \"Authorization: Bearer " + std::string(EDEN_API_KEY) + "\" -d '" + jsonData + "' " + std::string(EDEN_API_IMAGE_ENDPOINT);
	FILE* pipe = popen(command.c_str(), "r");
	if (!pipe)
		return "Error when using popen function";
	char buffer[256];
	std::string response;
	while (fgets(buffer, sizeof(buffer), pipe) != NULL)
		response += buffer;
	pclose(pipe);
	std::cout << response << std::endl;
	if (response.find("error") != std::string::npos)
		return "Error when using the API";
	return extract_image_url(response);
}

std::string getChatAnswerFromAPI(const char* prompt)
{
	std::string providers = "openai";
	std::string model = "gpt-4-vision-preview";
	std::string global_action = std::string(BOT_GLOBAL_INFO);
	std::string jsonData = "{\"response_as_dict\":true,\"attributes_as_list\":false,\"show_original_response\":false,\"temperature\":0,\"max_tokens\":1000,\"chatbot_global_action\":\"" + global_action + "\",\"text\":\"" + std::string(prompt) + "\",\"providers\":\"" + providers + "\"}";
	std::string command = "curl -s -X POST -H \"accept: application/json\" -H \"content-type: application/json\" -H \"Authorization: Bearer " + std::string(EDEN_API_KEY) + "\" -d '" + jsonData + "' " + std::string(EDEN_API_CHATBOT_ENDPOINT);
	FILE* pipe = popen(command.c_str(), "r");
	if (!pipe)
		return "Error when using popen function";
	char buffer[256];
	std::string response;
	std::cout << "response: " << response << std::endl;
	while (fgets(buffer, sizeof(buffer), pipe) != NULL)
		response += buffer;
	pclose(pipe);
	return extractText(response);
}