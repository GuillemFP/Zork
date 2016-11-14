#include "room.h"
#include <iostream>
#include "item.h"
#include "constants.h"
#include "creature.h"

Room::Room(const std::string& name, const std::string& description) : Entity(name, description)
{
	type = ROOM;
}

Room::~Room()
{

}

void Room::Look(Entity* origin) const
{
	Creature* creature = (Creature*)origin;

	std::cout << name << ": " << description << "\n";

	PrintSubentitiesByType(LIST_INTROS::ROOM_EXITS, EXIT);
	PrintSubentitiesByType(LIST_INTROS::ROOM_ITEMS, ITEM);
	PrintSubentitiesByTypeExcludeOrigin(LIST_INTROS::ROOM_CREATURES, CREATURE, origin);
}

bool Room::LookAt(Entity* origin, const std::string& thing) const
{
	Creature* creature = (Creature*)origin;
	
	for (std::list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it)
	{
		if (IsEqual(thing, (*it)->name) && (*it)->type != EXIT )
		{
			(*it)->Look(origin);
			return true;
		}
	}

	Exit* exit = GetExit(thing);
	if (exit != nullptr)
	{
		exit->Look(origin);
		return true;
	}

	if (IsEqual(name,thing))
	{
		Look(origin);
		return true;
	}

	return false;
}

bool Room::LookAtInside(Entity* origin, const std::string& item_name, const std::string& container_name) const
{
	bool all_found = false;

	Entity* container = FindByStringExclude(container_name, EXIT);
	if (container != nullptr)
		all_found = container->LookAt(origin, item_name);
	else if (IsEqual(container_name, name))
		all_found = LookAt(origin, item_name);

	return all_found;
}

Exit* Room::GetExit(const std::string& thing) const
{
	for (std::list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			Exit* exit = (Exit*)*it;
			if (IsEqual(thing,exit->GetName(this)))
				return exit;
		}
	}

	return nullptr;
}

void Room::PrintSubentitiesByType(const std::string& intro, Entity_Type type_check) const
{
	bool type_found = false;

	if (type_check != EXIT)
		Entity::PrintSubentitiesByType(intro, type_check);
	else
	{
		for (std::list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it)
		{
			if ((*it)->type == type_check)
			{
				Exit* exit = (Exit*)*it;
				if (type_found)
				{
					std::cout << ", " << exit->GetName(this);
				}
				else
				{
					std::cout << intro << exit->GetName(this);
					type_found = true;
				}
			}
		}
		if (type_found)
			std::cout << "\n";
	}
}