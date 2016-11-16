#include "exit.h"
#include <iostream>

Exit::Exit(const string& name1, const string& name2, const string& descript_1, const string& descript_2, const string& description, 
	Room* room1, Room* room2, Item* key, bool locked, bool small) : Entity(name1, descript_1, room1),
	destination_name(name2), destination_desc(descript_2), connection_desc(description), destination_entity(room2),
	locked(locked), key(key), small(small)
{
	type = EXIT;

	room2->contains.push_back(this);
}

Exit::~Exit()
{

}

void Exit::Look(Entity* origin) const
{
	Room* room_origin;
	string name_print, desc_print;
	if (origin->parent->type == CREATURE)
		room_origin = (Room*)origin->parent->parent;
	else
		room_origin = (Room*)origin->parent;

	name_print = GetName(room_origin);
	desc_print = GetDescription(room_origin);

	std::cout << name_print << ": " << desc_print << ".";
	if (locked)
		std::cout << " It's locked.";
	std::cout << "\n";
}

const string& Exit::GetName(const Room* origin) const
{
	if (parent == origin)
		return name;
	if (destination_entity == origin)
		return destination_name;

	return NULL;
}

const string& Exit::GetDescription(const Room* origin) const
{
	if (parent == origin)
		return description;
	if (destination_entity == origin)
		return destination_desc;

	return NULL;
}

Room* Exit::GetDestination(const Room* origin) const
{
	if (parent == origin)
		return destination_entity;
	if (destination_entity == origin)
		return (Room*)parent;

	return nullptr;
}

void Exit::SetKey(Item* needed_key)
{
	key = needed_key;
	locked = true;
}

void Exit::Unlock()
{
	key = nullptr;
	locked = false;
}

void Exit::Open()
{
	locked = false;
}