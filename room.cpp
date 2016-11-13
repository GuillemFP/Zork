#include "room.h"

Room::Room(const std::string& name, const std::string& description) : Entity(name, description, nullptr)
{
	type = ROOM;
}

Room::~Room()
{

}

void Room::Look() const
{

}

void Room::LookAt(const std::string& thing) const
{
	bool thing_found = false;

	if (IsEqual(name,thing))
	{
		Look();
		thing_found = true;
	}
	else
	{
		for (std::list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it)
		{
			if (IsEqual((*it)->name,thing))
			{
				(*it)->Look();
				thing_found = true;
			}
		}
	}

	if (!thing_found)
	{

	}
}