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
	const std::vector<std::string> NORTH = { "north","n" };
	const std::vector<std::string> EAST = { "east","e" };
	const std::vector<std::string> SOUTH = { "south","s" };
	const std::vector<std::string> WEAST = { "west","w" };
	const std::vector<std::string> UP = { "up","u" };
	const std::vector<std::string> DOWN = { "down","d" };
	const std::string LOOK = "look";
	const std::string OPEN = "open";
	const std::vector<std::string> INFECT = { "infect","parasitize" };
	const std::vector<std::string> TAKE = { "take","pick" };
	const std::string EVOLVE = "evolve";
	const std::string FEED = "feed";
}

#endif // !CONSTANTS_H