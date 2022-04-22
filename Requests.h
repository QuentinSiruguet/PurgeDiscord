#pragma once

#include "curlpp/Easy.hpp"
#include "curlpp/Options.hpp"
#include <json/json.h>

#include <cstdio>
#include <sstream>
#include <string>
#include <vector>


class Requests
{
private:
	std::string myToken;
public:
	Requests();
	std::stringstream RequestMyID();
	std::stringstream RequestAllChannels();
	std::stringstream RequestAllMessages(std::string channelID);
	std::stringstream RequestMessageDelete(std::string channelID, std::string messageID);
};

