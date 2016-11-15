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

	std::cout << name << ": " << description;

	if (alive)
	{
		std::cout << "\n";
		PrintItems(LIST_INTROS::CREATURE_ALIVE_ITEMS, true);
	}
	else
	{
		std::cout << " It's dead.\n";
		PrintItems(LIST_INTROS::CREATURE_DEATH_ITEMS, false);
	}
}

bool Creature::LookAt(Entity* origin,const std::string& thing) const
{
	bool thing_found = false;
	
	Entity* element = FindByStringExclude(thing, PLAYER);
	if (element != nullptr)
	{
		Item* item = (Item*)element;
		if (this->alive && item->in_pocket)
		{
			return false;
		}
		thing_found = true;
		element->Look(origin);
	}

	if (!thing_found)
		thing_found = parent->LookAt(origin,thing);

	return thing_found;
}

bool Creature::Take(Entity* origin, const std::string& thing)
{
	if (this == (Creature*)origin)
	{
		return false;
	}

	if (alive)
	{
		std::cout << "You cannot take anything from a living creature.\n";
		return true;
	}
	
	return Entity::Take(origin, thing);
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
	return PrintItems(LIST_INTROS::INVENTORY_HOST, false);
}

bool Creature::PrintItems(const std::string& intro, bool only_seen) const
{
	bool item_found = false;

	if (only_seen)
	{
		for (std::list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it)
		{
			if ((*it)->type == ITEM)
			{
				Item* item = (Item*)*it;
				if (!item->in_pocket)
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
			std::cout << ".\n";
		
	}
	else
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
			std::cout << ".\n";
	}

	return item_found;
}

Room* Creature::GetRoom() const
{
	return (Room*)parent;
}