#pragma once
#include "Requests.h"

#include<chrono>
#include<thread>

class Parser
{
private:
	Requests &request;
	std::string myID;
public:
	Parser(Requests&);
	std::vector<std::vector<std::string>> GetAllChannelsFromJSON();
	std::vector<std::string> GetAllMessagesToDelete(std::stringstream);
	void PurgeChannel(std::string channelToPurge);
};

