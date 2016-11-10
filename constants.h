#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <vector>

namespace MENU
{
	const std::vector<std::string> QUIT = {"quit","exit"};
}

namespace COMMAND
{
	const std::vector<std::string> MOVE = { "move","go" };
	const std::vector<std::string> NORTH = { "north","n" };
	const std::vector<std::string> EAST = { "east","e" };
	const std::vector<std::string> SOUTH = { "south","s" };
	const std::vector<std::string> WEAST = { "west","w" };
	const std::vector<std::string> UP = { "up","u" };
	const std::vector<std::string> DOWN = { "down","d" };
	const std::vector<std::string> LOOK = { "look" };
	const std::vector<std::string> OPEN = { "open" };
	const std::vector<std::string> INFECT = { "infect","parasitize" };
	const std::vector<std::string> TAKE = { "take","pick" };
	const std::vector<std::string> DROP = { "drop","release" };
	const std::vector<std::string> EVOLVE = { "evolve" };
	const std::vector<std::string> FEED = { "feed" };
	const std::vector<std::string> INVENTORY = { "inventory","items" };
	const std::vector<std::string> STATE = { "state","check" };
}

namespace CONNECTORS
{
	const std::vector<std::string> FROM = { "from" };
	const std::vector<std::string> INTO = { "into","to","inside" };
	const std::vector<std::string> AT = { "at","to" };
}

namespace OUTPUTS
{
	const std::string _ERROR = "-> ";
	const std::string _ACCEPTED = "->> ";
	const std::string MISTAKE = "Sorry, I cannot understand you.";
	const std::string WHERE = " where?";
}

#endif // !CONSTANTS_H