#include "Requests.h"

#include <fstream>

Requests::Requests()
{
	std::ifstream file("token.cfg");
	file >> this->myToken;
	file.close();
}

std::stringstream Requests::RequestMyID()
{
	std::list<std::string> header;

	header.push_back("Content-Type: application/json");
	header.push_back("Authorization: " + this->myToken);

	cURLpp::Easy r;

	r.setOpt(new curlpp::options::Url("https://discordapp.com/api/users/@me"));
	r.setOpt(new curlpp::options::HttpHeader(header));
	std::stringstream buffer;
	r.setOpt(new curlpp::options::WriteStream(&buffer));
	r.perform();

	std::stringstream ss;
	ss << r;
	return ss;
}

std::stringstream Requests::RequestAllChannels()
{
	std::list<std::string> header;

	header.push_back("Content-Type: application/json");
	header.push_back("Authorization: " + this->myToken);

	cURLpp::Easy r;

	r.setOpt(new curlpp::options::Url("https://discordapp.com/api/users/@me/channels"));
	r.setOpt(new curlpp::options::HttpHeader(header));
	std::stringstream buffer;
	r.setOpt(new curlpp::options::WriteStream(&buffer));
	r.perform();

	std::stringstream ss;
	ss << r;
	return ss;
}

std::stringstream Requests::RequestAllMessages(std::string channelID)
{
	std::list<std::string> header;

	header.push_back("Content-Type: application/json");
	header.push_back("Authorization: " + this->myToken);

	cURLpp::Easy r;

	const std::string URL = "https://discordapp.com/api/channels/" + channelID + "/messages";

	r.setOpt(new curlpp::options::Url(URL));
	r.setOpt(new curlpp::options::HttpHeader(header));
	std::stringstream buffer;
	r.setOpt(new curlpp::options::WriteStream(&buffer));
	r.perform();

	std::stringstream ss;
	ss << r;
	return ss;
}

std::stringstream Requests::RequestMessageDelete(std::string channelID, std::string messageID)
{
	std::list<std::string> header;

	header.push_back("Content-Type: application/json");
	header.push_back("Authorization: " + this->myToken);

	cURLpp::Easy r;

	const std::string URL = "https://discordapp.com/api/channels/" + channelID + "/messages/" + messageID;

	r.setOpt(new curlpp::options::Url(URL));
	r.setOpt(new curlpp::options::HttpHeader(header));
	r.setOpt(new curlpp::options::CustomRequest("DELETE"));
	r.perform();
	std::stringstream ss;
	ss << r;
	return ss;
}

