#include "item.h"
#include <iostream>
#include "constants.h"
#include "creature.h"

Item::Item(const std::string& name, const std::string& description, Entity* parent, Item_Type item_type, Exit* opens, int damage, bool in_pocket) :
	Entity(name, description, parent), item_type(item_type), opens(opens), damage(damage), in_pocket(in_pocket)
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
		Entity* entity_found = FindByStringType(thing, ITEM);
		if (entity_found != nullptr)
		{
			entity_found->Look(origin);
			return true;
		}
	}

	return false;
}

bool Item::Take(Entity* origin, const std::string& thing)
{
	Creature* creature = (Creature*)origin;

	if (!creature->smart && item_type == INFO)
	{
		return false;
	}
	else
	{
		Entity* entity_found = FindByStringType(thing, ITEM);
		if (entity_found != nullptr)
		{
			std::cout << LIST_INTROS::TAKE_ITEM << entity_found->name << LIST_INTROS::FROM << entity_found->parent->name << LIST_INTROS::TAKE_ITEM_TO << "\n";
			entity_found->ChangeParent(origin);
			return true;
		}
	}

	return false;
}