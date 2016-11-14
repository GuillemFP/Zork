#include "item.h"
#include <iostream>
#include "constants.h"
#include "creature.h"

Item::Item(const std::string& name, const std::string& description, Entity* parent, Item_Type item_type, Exit* opens, int damage, bool big) :
	Entity(name, description, parent), item_type(item_type), opens(opens), damage(damage), big(big)
{
	type = ITEM;
	if (this->item_type != KEY)
		opens = nullptr;
	if (this->damage != WEAPON)
		damage = 0;
}

Item::~Item()
{

}

void Item::Look(Entity* origin) const
{
	Creature* creature = (Creature*)origin;

	if (!creature->smart && item_type == INFO)
	{
		std::cout << PLAYER_CONSTANTS::LOOK_UNKNOWN << "\n";
	}
	else
	{
		std::cout << name << ": " << description << "\n";

		PrintSubentitiesByType(LIST_INTROS::ITEM_ITEMS, ITEM);
	}
}

bool Item::LookAt(Entity* origin,const std::string& thing) const
{
	Creature* creature = (Creature*)origin;

	if (!creature->smart && item_type == INFO)
	{
		return false;
	}
	else
	{
		for (list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it)
		{
			if (IsEqual(thing, (*it)->name))
			{
				(*it)->Look(origin);
				return true;
			}
		}
	}

	return false;
}