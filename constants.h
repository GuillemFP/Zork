#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <vector>

using namespace std;

namespace MENU
{
	const vector<string> QUIT = {"quit","exit"};
}

namespace COMMAND
{
	const vector<string> MOVE = { "move","go" };
	const vector<string> DIRECTIONS = { "north", "east", "south", "west" };
	const vector<string> LOOK = { "look" };
	const vector<string> OPEN = { "open" };
	const vector<string> INFECT = { "infect","parasitize" };
	const vector<string> TAKE = { "take","pick" };
	const vector<string> DROP = { "drop","release" };
	const vector<string> EVOLVE = { "evolve" };
	const vector<string> FEED = { "feed" };
	const vector<string> INVENTORY = { "inventory","items" };
	const vector<string> STATE = { "state","check" };
	
}

namespace NAMES
{
	const vector<string> HOST = { "host","you" };
	const vector<string> YOU = { "you","player","myself","alien" };
}

namespace CONNECTORS
{
	const vector<string> FROM = { "from" };
	const vector<string> INTO = { "into","to","inside" };
	const vector<string> AT = { "at" };
	const vector<string> INSIDE = { "inside","in","on" };
	const vector<string> WITH = { "with","using" };
}

namespace OUTPUTS
{
	const string _ERROR = "-> ";
	const string _ACCEPTED = "->> ";
	const string _WAITING = "> ";
	const string MISTAKE = "Sorry, I cannot understand you.";
	const string WHERE = " where?";
	const string WHAT = " what?";
	const string CANNOT = "I cannot ";
	const string INVENTORY_EMPTY = "The inventory is empty.";
}

namespace LIST_INTROS
{
	const string INVENTORY_PLAYER = "You hold: ";
	const string INVENTORY_HOST = "Your host hold: ";
	const string ROOM_EXITS = "There is a way out of this room: ";
	const string ROOM_ITEMS = "There is something interesting in this room: ";
	const string ROOM_CREATURES = "There is another sentient creature in this room: ";
	const string ITEM_ITEMS = "There is something inside: ";
	const string CREATURE_ALIVE_ITEMS = "It holds, that you can see: ";
	const string CREATURE_DEATH_ITEMS = "It has: ";
}

namespace PLAYER_CONSTANTS
{
	const string LARVA_DESC = "You are a larva of an alien species. Your length is 30 centimeters, your skin is grayish and soft. Your only instict is to survive by parasitizing other species.";
	const string ARACHNID_DESC = "You evolved into your species arachnid form. Your height is 60 centimeters, but your bones are strong, you are fast and have a set of mortal claws.";
	const string BIPED_DESC = "You evolved into your species biped form. You no longer have the ability to parasitize other species, but have reached a state of evolution beyond humanity.";
	const string LOOK_UNKNOWN = "You are unable to understand what are you looking at.";
}

#endif // !CONSTANTS_H