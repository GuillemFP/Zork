#ifndef EXIT_H
#define EXIT_H

#include "entity.h"
#include "room.h"
#include "item.h"
#include <string>

class Item;
class Room;

using namespace std;

class Exit : public Entity
{
public:
	Exit(const string& name1, const string& name2, const string& descript_1, const string& descript_2, const string& description,
		Room* room1, Room* room2, Item* key = nullptr, bool locked = false, bool small = false);
	~Exit();
	void Look(Entity* origin) const;
	const string& GetName(const Room* origin) const;
	const string& GetDescription(const Room* origin) const;
	Room* GetDestination(const Room* origin) const;
	void SetKey(Item* needed_key);
	void Unlock();
	void Open();

	string destination_name;
	string destination_desc;
	string connection_desc;
	Room* destination_entity;
	bool locked;
	Item* key;
	bool small;
};



#endif // !EXIT_H