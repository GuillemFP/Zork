#include "entity.h"

Entity::Entity(const std::string& name, const std::string& description, Entity* parent = nullptr) :
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

void Entity::Look() const
{
	
}

void Entity::LookAt(const std::string& thing) const
{

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