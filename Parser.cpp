#include "Parser.h"

Parser::Parser(Requests& r) : request(r)
{
	const std::string JSON = this->request.RequestMyID().str();
	Json::Value JsonValues;
	Json::Reader reader;
	reader.parse(JSON, JsonValues);

	this->myID = JsonValues["id"].asString();
}

std::vector<std::vector<std::string>> Parser::GetAllChannelsFromJSON()
{
	const std::string JSON = this->request.RequestAllChannels().str();
	Json::Value JsonValues;
	Json::Reader reader;
	std::vector<std::vector<std::string>> channelsID;

	reader.parse(JSON, JsonValues);

	for (auto& json : JsonValues)
	{
		std::vector<std::string> channel;
		channel.push_back(json["id"].asString());

		if (json["type"] == 1 || json["name"] == Json::nullValue)
			for (auto& member : json["recipients"])
				channel.push_back(member["username"].asString());
		else
			channel.push_back(json["name"].asString());

		channelsID.push_back(channel);
	}

	return channelsID;
}

std::vector<std::string> Parser::GetAllMessagesToDelete(std::stringstream ss)
{	
	const std::string JSON = ss.str();
	Json::Value JsonValues;
	Json::Reader reader;
	std::vector<std::string> messagesID;

	reader.parse(JSON, JsonValues);

	for (auto &json : JsonValues)
		if(json["author"]["id"] == this->myID)
			messagesID.push_back(json["id"].asString());

	return messagesID;
}

void Parser::PurgeChannel(std::string channelToPurge)
{
	std::vector<std::string> messagesID = this->GetAllMessagesToDelete(this->request.RequestAllMessages(channelToPurge));

	for (int i = 0; i < messagesID.size(); i++)
	{
		const std::stringstream ss = this->request.RequestMessageDelete(channelToPurge, messagesID[i]);
		const std::string JSON = ss.str();
		Json::Value JsonValues;
		Json::Reader reader;

		if (ss.str() == "{\"message\": \"Unknown Message\", \"code\": 10008}")
			std::cout << i+1 << "|" << messagesID.size() << std::endl;
		else
		{
			std::cout << "RATE LIMIT" << std::endl;
			std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(8));
			i--;
		}
		std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(1500));
	}
}
