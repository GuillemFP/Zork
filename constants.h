#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <vector>

using namespace std;

enum Output_type
{
	ACCEPTED,
	ERROR,
	KILLED,
	FLED,
	SURVIVOR
};

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
	const vector<string> DROP = { "drop","release","put","leave" };
	const vector<string> EVOLVE = { "evolve" };
	const vector<string> FEED = { "feed" };
	const vector<string> INVENTORY = { "inventory","items" };
	const vector<string> STATE = { "state","check" };
	const vector<string> ATTACK = { "attack" };
	
}

namespace NAMES
{
	const vector<string> HOST = { "host","you" };
	const vector<string> YOU = { "you","player","myself","alien" };
}

namespace CONNECTORS
{
	const vector<string> FROM = { "from","inside","in","on" };
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
	const string _GAMEOVER = "GAME OVER!";
	const string MISTAKE = "Sorry, I cannot understand you.";
	const string WHERE = " where?";
	const string WHAT = " what?";
	const string CANNOT = "I cannot ";
	const string INVENTORY_EMPTY = "The inventory is empty.";
	const string NOT_EVOLVE = "You have not feed enough to evolve.";
	const string NOT_FEED = "You can only feed from inside a living creature.";
	const string INJURED = " seriously injured.";
	const string FIRST_DESCRIPTION = "You are a larva of an alien species that have just hatched from its egg. Finding yourself in a strange location, you are unable to see more members of your species. Your length is 20 centimeters, your skin is grayish and soft. Your only instict is to survive by parasitizing other species. Good luck.";
}

namespace LIST_INTROS
{
	const string INVENTORY_PLAYER = "You hold: ";
	const string INVENTORY_HOST = "Your host hold: ";
	const string ROOM_EXITS = "There is a way out of this room: ";
	const string ROOM_ITEMS = "There is something interesting in this room: ";
	const string ROOM_CREATURES_ALIVE = "There are more sentient creatures in this room: ";
	const string ROOM_CREATURES_DEAD = "There are dead creatures in this room: ";
	const string ITEM_ITEMS = "There is something inside: ";
	const string CREATURE_ALIVE_ITEMS = "It holds, that you can see: ";
	const string CREATURE_LIST_ITEMS = "It has: ";
	const string TAKE_ITEM = "You take ";
	const string TAKE_ITEM_TO = " and put in into your inventory.";
	const string FROM = " from ";
	const string DROP_ITEM = "You leave ";
	const string DROP_ITEM_IN = " in ";
}

namespace PLAYER_CONSTANTS
{
	const string PLAYER = "you";
	const string LARVA_DESC = "You are a larva of an alien species. Your length is 20 centimeters, your skin is grayish and soft. Your only instict is to survive by parasitizing other species.";
	const string ARACHNID_DESC = "You are an arachnid, an evolved stage of your species. Your height is 30 centimeters, but your bones are strong, you are fast and have a set of mortal claws.";
	const string BIPED_DESC = "You are an evolved stage of your species. Yours is a biped form, with a grayish skin coated in a strong bone-like shell and taller than the average human. You no longer have the ability to parasitize other species, but have reached a state of evolution beyond humanity.";
	const string LOOK_UNKNOWN = "You are unable to understand what are you looking at.";
}

namespace STATS_VALUE
{
	const int LARVA_TO_ARACHNID = 50;
	const int ARACHNID_TO_BIPED = 25;
	const int LARVA_HP = 30;
	const int LARVA_DAMAGE = 10;
	const int ARACHNID_HP = 90;
	const int ARACHNID_DAMAGE = 40;
	const int BIPED_HP = 150;
	const int BIPED_DAMAGE = 60;
}

#endif // !CONSTANTS_H