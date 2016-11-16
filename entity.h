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
	Entity(const std::string& name, const std::string& description, Entity* parent = nullptr);
	virtual ~Entity();
	virtual std::string GetName() const;
	virtual std::string GetDescription() const;
	virtual void Look(Entity* origin) const;
	virtual bool LookAt(Entity* origin, const std::string& thing) const;
	virtual bool LookAtInside(Entity* origin, const std::string& item_name, const std::string& container_name) const;
	virtual bool Take(Entity* origin, const std::string& thing);
	virtual bool TakeFrom(Entity* origin, const std::string& item_name, const std::string& container_name);
	virtual bool Drop(Entity* item_drop, const std::string& container_name);
	virtual void DropTo(Entity* target);

	void ChangeParent(Entity* new_parent);
	bool FindByEntity(Entity* match_entity) const;
	Entity* FindByString(const std::string& thing) const;
	Entity* FindByStringType(const std::string& thing, Entity_Type type_match) const;
	Entity* FindByStringExclude(const std::string& thing, Entity_Type type_exclude) const;
	virtual void PrintSubentitiesByType(const std::string& intro, Entity_Type type_check) const;
	virtual void PrintSubentitiesByTypeExcludeOrigin(const std::string& intro, Entity_Type type_check, Entity* origin) const;

	Entity_Type type;
	std::string name;
	std::string description;
	std::list<Entity*> contains;
	Entity* parent;
};

#endif // !ENTITY_H
