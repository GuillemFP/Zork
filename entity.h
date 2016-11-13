#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <list>
#include "globals.h"

enum Entity_Type
{
	ENTITY,
	ROOM,
	EXIT,
	ITEM,
	CREATURE,
	PLAYER
};

class Entity
{
public:
	Entity(const std::string& name, const std::string& description, Entity* parent);
	virtual ~Entity();
	virtual std::string GetName() const;
	virtual std::string GetDescription() const;
	virtual void Look() const;
	virtual void LookAt(const std::string& thing) const;
	void ChangeParent(Entity* new_parent);

	Entity_Type type;
	std::string name;
	std::string description;
	std::list<Entity*> contains;
	Entity* parent;

};

#endif // !ENTITY_H
