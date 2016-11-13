#include "exit.h"

Exit::Exit(const string& name1, const string& name2, string& descript_1, string& descript_2, const string& description,
	Entity* room1, Entity* room2, Item* key, bool closed = false, bool locked = false) : Entity(name1, descript_1, room1),
	destination_name(name2), destination_desc(descript_2), connection_description(description), destination_entity(room2),
	closed(closed), locked(locked), key(key)
{
	type = EXIT;

	room2->contains.push_back(this);
	
}

Exit::~Exit()
{

}

void Exit::Look() const
{

}