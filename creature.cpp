#include "creature.h"
#include <iostream>

Creature::Creature(const std::string& name, const std::string& description, Entity* parent, int hp = 100) : 
	Entity(name, description, parent), hit_points(hp)
{
	type = CREATURE;
}

Creature::~Creature()
{
}

void Creature::Look() const
{
	
}

void Creature::LookAt(const std::string& thing) const
{
	bool thing_found = false;

	for (std::list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it)
	{
		if (IsEqual((*it)->name, thing) && (*it)->type != PLAYER)
		{
			(*it)->Look();
			thing_found = true;
		}
	}

	if (!thing_found)
		parent->LookAt(thing);
}