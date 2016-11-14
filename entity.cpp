#include "entity.h"
#include <iostream>

Entity::Entity(const std::string& name, const std::string& description, Entity* parent) :
	name(name), description(description), parent(parent)
{
	type = ENTITY;

	if (parent != nullptr)
		parent->contains.push_back(this);
}

Entity::~Entity()
{

}

std::string Entity::GetName() const
{
	return name;
}

std::string Entity::GetDescription() const
{
	return description;
}

void Entity::Look(Entity* origin) const
{
	std::cout << name << ": " << description << "\n";
}

bool Entity::LookAt(Entity* origin, const std::string& thing) const
{
	return false;
}

bool Entity::LookAtInside(Entity* origin, const std::string& item_name, const std::string& container_name) const
{
	return false;
}

void Entity::ChangeParent(Entity* new_parent)
{
	if (parent != nullptr)
	{
		parent->contains.remove(this);
		if (new_parent != nullptr)
		{
			parent = new_parent;
			parent->contains.push_back(this);
		}
	}
}

bool Entity::FindByEntity(Entity* match_entity) const
{
	for (std::list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it)
	{
		if (*it == match_entity)
		{
			return true;
		}
	}
	return false;
}

Entity* Entity::FindByString(const std::string& thing) const
{
	for (std::list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it)
	{
		if (IsEqual(thing,(*it)->name))
		{
			return *it;
		}
	}

	return nullptr;
}

Entity* Entity::FindByStringExclude(const std::string& thing, Entity_Type type_exclude) const
{
	for (std::list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it)
	{
		if (IsEqual(thing, (*it)->name) && (*it)->type != type_exclude)
		{
			return *it;
		}
	}

	return nullptr;
}

void Entity::PrintSubentitiesByType(const std::string& intro, Entity_Type type_check) const
{
	bool type_found = false;

	for (std::list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it)
	{
		if ((*it)->type == type_check)
		{
			if (type_found)
			{
				std::cout << ", " << (*it)->name;
			}
			else
			{
				std::cout << intro << (*it)->name;
				type_found = true;
			}
		}
	}
	if (type_found)
		std::cout << ".\n";
}

void Entity::PrintSubentitiesByTypeExcludeOrigin(const std::string& intro, Entity_Type type_check, Entity* origin) const
{
	bool type_found = false;

	for (std::list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it)
	{
		if ((*it)->type == type_check && *it != origin)
		{
			if (type_found)
			{
				std::cout << ", " << (*it)->name;
			}
			else
			{
				std::cout << intro << (*it)->name;
				type_found = true;
			}
		}
	}
	if (type_found)
		std::cout << ".\n";
}