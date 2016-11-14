#include "creature.h"
#include "constants.h"
#include <iostream>
#include "item.h"

Creature::Creature(const std::string& name, const std::string& description, Entity* parent, int hp, bool smart) :
	Entity(name, description, parent), hit_points(hp), smart(smart)
{
	type = CREATURE;
	if (hp > 0)
		alive = true;
	else
		alive = false;
}

Creature::~Creature()
{
}

void Creature::Look(Entity* origin) const
{
	Creature* creature = (Creature*)origin;

	if (alive)
	{
		std::cout << name << ": " << description << "\n";
		PrintSubentitiesByType(name + LIST_INTROS::CREATURE_ALIVE_ITEMS, ITEM);
	}
	else
	{
		std::cout << "The corpse of a " + name << ": " << description << "\n";
		PrintSubentitiesByType(name + LIST_INTROS::CREATURE_DEATH_ITEMS, ITEM);
	}
}

bool Creature::LookAt(Entity* origin,const std::string& thing) const
{
	bool thing_found = false;
	
	Entity* element = FindByString(thing);
	if (element->type != PLAYER && element != nullptr)
	{
		thing_found = true;
		element->Look(origin);
	}

	if (!thing_found)
		thing_found = parent->LookAt(origin,thing);

	return thing_found;
}

bool Creature::LookAtInside(Entity* origin,const std::string& item_name, const std::string& container_name) const
{
	bool all_found = false;

	Entity* container = FindByString(container_name);
	if (container == nullptr)
		all_found = parent->LookAtInside(origin,item_name, container_name);
	else
		all_found = container->LookAt(origin,item_name);

	return all_found;
}

bool Creature::Move(const std::string& direction)
{
	Room* room = GetRoom();
	Exit* exit = room->GetExit(direction);

	if (exit == nullptr)
		return false;

	if (exit->locked)
	{
		std::cout << "It's locked. You cannot move further in that direction.\n";
	}
	else
	{
		std::cout << "You go " + direction + " through " + exit->GetDescription(room) + ". " + exit->connection_desc + "\n";
		ChangeParent(exit->GetDestination(room));
	}

	return true;
}

bool Creature::Open(const std::string& direction)
{
	Room* room = GetRoom();
	Exit* exit = room->GetExit(direction);

	if (exit == nullptr)
		return false;

	if (!exit->locked)
		return false;

	Item* needed_key = exit->key;
	if (FindByEntity(needed_key))
	{
		std::cout << "You used " + needed_key->name + " to open " + exit->GetDescription(room) + " leading " + exit->GetName(room) + ".\n";
		exit->Unlock();
	}
	else
		std::cout << "You cannot open " + exit->GetDescription(room) + " with your current equipment.\n";

	return true;
}

bool Creature::Inventory() const
{
	return PrintItems(LIST_INTROS::INVENTORY_HOST, true);
}

bool Creature::PrintItems(const std::string& intro, bool print_all) const
{
	bool item_found = false;

	if (print_all)
	{
		for (std::list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it)
		{
			if ((*it)->type == ITEM)
			{
				Item* item = (Item*)*it;
				if (item_found)
				{
					std::cout << ", " << (*it)->name;
				}
				else
				{
					std::cout << intro << (*it)->name;
					item_found = true;
				}
			}
		}
		if (item_found)
			std::cout << "\n";
	}
	else
	{
		for (std::list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it)
		{
			if ((*it)->type == ITEM)
			{
				Item* item = (Item*)*it;
				if (item->big)
				{
					if (item_found)
					{
						std::cout << ", " << (*it)->name;
					}
					else
					{
						std::cout << intro << (*it)->name;
						item_found = true;
					}
				}
			}
		}
		if (item_found)
			std::cout << "\n";
	}

	return item_found;
}

Room* Creature::GetRoom() const
{
	return (Room*)parent;
}