#include "Parser.h"



int main()
{
	Requests request;
	Parser parser(request);
	
	std::vector<std::vector<std::string>> channelsID = parser.GetAllChannelsFromJSON();

	std::cout << "All your channels : " << std::endl << std::endl;

	for (auto& c : channelsID)
	{
		std::cout << "ID : ";
		for (int i = 0; i < c.size(); i++)
		{
			std::cout << c[i];
			if (i < c.size() - 1 && i > 0)
				std::cout << ", ";
			else if (i == 0)
				std::cout << " - ";
		}
		std::cout << std::endl;
	}

	std::string channelToPurge;
	std::cout << std::endl << "Choose ID : ";
	std::cin >> channelToPurge;

	parser.PurgeChannel(std::move(channelToPurge));
}