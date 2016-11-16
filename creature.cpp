#include "creature.h"
#include "constants.h"
#include <iostream>
#include "item.h"

Creature::Creature(const std::string& name, const std::string& description, Entity* parent, bool smart, int hp, int evo_points, int damage) :
	Entity(name, description, parent), smart(smart), max_hit_points(hp), evolution_points(evo_points), damage(damage)
{
	type = CREATURE;
	hit_points = max_hit_points;
	alive = true;
}

Creature::~Creature()
{
}

void Creature::Look(Entity* origin) const
{
	Creature* creature_origin = (Creature*)origin;

	std::cout << name << ": " << description;

	if (this != creature_origin)
	{
		if (alive)
		{
			if (IsInjured())
				std::cout << " It's injured.";
			std::cout << "\n";
			PrintItems(LIST_INTROS::CREATURE_ALIVE_ITEMS, true);
		}
		else
		{
			std::cout << " It's dead.\n";
			PrintItems(LIST_INTROS::CREATURE_LIST_ITEMS, false);
		}
	}
	else
	{
		std::cout << " It is your current host.";
		if (IsInjured())
			std::cout << " It's injured.";
		std::cout << "\n";
		PrintItems(LIST_INTROS::CREATURE_LIST_ITEMS, false);
	}
	
}

bool Creature::LookAt(Entity* origin,const std::string& thing) const
{
	bool thing_found = false;
	
	Entity* element = FindEntityByStringExclude(thing, PLAYER);
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

void Creature::Damage(int damage_taken)
{
	hit_points -= damage_taken;
	if (IsHost())
		std::cout << name << " takes damage.";
	else
	{
		if (parent->FindByString(PLAYER_CONSTANTS::PLAYER))
			std::cout << name << " takes damage.";		
	}
	
	if (hit_points <= 0)
	{
		std::cout << " ";
		Kill();
	}
	else
		std::cout << "\n";
}

void Creature::Heal(int damage_healed)
{
	hit_points += damage_healed;
	if (hit_points > max_hit_points)
		hit_points = max_hit_points;
}

void Creature::Kill()
{
	alive = false;
	
	if (IsHost())
	{
		Entity* player = FindParasite();
		std::cout << name << " drops dead on the ground. ";
		player->ChangeParent(parent);
		std::cout << "You emerge from the corpse of " << name << " into " << parent->name << ".\n";
	}
	else
	{
		if (parent->FindByString(PLAYER_CONSTANTS::PLAYER))
			std::cout << name << " drops dead on the ground.\n";
	}

	if (hit_points > 0)
		hit_points = 0;
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

bool Creature::IsHost() const
{
	Entity* player = FindEntityByStringType(PLAYER_CONSTANTS::PLAYER, PLAYER);
	if (player != nullptr)
		return true;
	else
		return false;
}

bool Creature::IsInjured() const
{
	return (float)hit_points / max_hit_points < 0.5;
}

Entity* Creature::FindParasite() const
{
	return FindEntityByStringType(PLAYER_CONSTANTS::PLAYER, PLAYER);
}

Room* Creature::GetRoom() const
{
	return (Room*)parent;
}