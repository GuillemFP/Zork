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

namespace NAMES
{
	const std::vector<std::string> HOST = { "host","you" };
	const std::vector<std::string> YOU = { "you" };
}

namespace CONNECTORS
{
	const std::vector<std::string> FROM = { "from" };
	const std::vector<std::string> INTO = { "into","to","inside" };
	const std::vector<std::string> AT = { "at" };
}

namespace OUTPUTS
{
	const std::string _ERROR = "-> ";
	const std::string _ACCEPTED = "->> ";
	const std::string MISTAKE = "Sorry, I cannot understand you.";
	const std::string WHERE = " where?";
	const std::string WHAT = " what?";
}

namespace PLAYER_CONSTANTS
{
	const std::string LARVA_DESC = "You are a larva of an alien species. Your length is 30 centimeters, your skin is grayish and soft. Your only instict is to survive by parasitizing other species.";
	const std::string ARACHNID_DESC = "You evolved into your species arachnid form. Your height is 60 centimeters, but your bones are strong, you are fast and have a set of mortal claws.";
	const std::string BIPED_DESC = "You evolved into your species biped form. You no longer have the ability to parasitize other species, but have reached a state of evolution beyond humanity.";

}

#endif // !CONSTANTS_H