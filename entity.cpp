#include "entity.h"
#include <iostream>
#include "constants.h"

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
	Entity* container = FindByStringExclude(container_name,EXIT);
	if (container == nullptr)
	{
		if (parent != nullptr)
			return parent->LookAtInside(origin, item_name, container_name);
		else
		{
			if (IsEqual(container_name, name))
				return LookAt(origin, item_name);
		}
	}
	else
		return container->LookAt(origin, item_name);

	return false;
}

bool Entity::Take(Entity* origin, const std::string& thing)
{
	Entity* entity_found = FindByStringType(thing, ITEM);
	if (entity_found != nullptr)
	{
		std::cout << LIST_INTROS::TAKE_ITEM << entity_found->name << LIST_INTROS::FROM << entity_found->parent->name << LIST_INTROS::TAKE_ITEM_TO << "\n";
		entity_found->ChangeParent(origin);
		return true;
	}

	return false;
}

bool Entity::TakeFrom(Entity* origin, const std::string& item_name, const std::string& container_name)
{
	Entity* container = FindByStringExclude(container_name,PLAYER);
	if (container == nullptr)
	{
		if (parent != nullptr)
			return parent->TakeFrom(origin, item_name, container_name);
		else
		{
			if (IsEqual(container_name, name))
				return Take(origin, item_name);
		}
	}	
	else
		return container->Take(origin, item_name);

	return false;
}

bool Entity::Drop(Entity* item_drop, const std::string& container_name)
{
	Entity* container = FindByStringType(container_name, ITEM);
	if (container == nullptr)
	{
		container = FindByStringType(container_name, CREATURE);
		if (container == nullptr)
		{
			if (parent != nullptr)
				return parent->Drop(item_drop, container_name);
			else
			{
				if (IsEqual(container_name, name) && type == ROOM)
				{
					item_drop->DropTo(this);
					return true;
				}
			}
		}
		else
		{
			item_drop->DropTo(container);
			return true;
		}
	}
	else
	{
		item_drop->DropTo(container);
		return true;
	}

	return false;
}

void Entity::DropTo(Entity* target)
{
	std::cout << LIST_INTROS::DROP_ITEM << name << LIST_INTROS::DROP_ITEM_IN << target->name << ".\n";
	ChangeParent(target);
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

Entity* Entity::FindByStringType(const std::string& thing, Entity_Type type_match) const
{
	for (std::list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it)
	{
		if (IsEqual(thing, (*it)->name) && (*it)->type == type_match)
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