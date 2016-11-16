#ifndef ITEM_H
#define ITEM_H

#include "entity.h"
#include "exit.h"

enum Item_Type
{
	KEY,
	WEAPON,
	OBJECT,
	INFO
};

class Exit;

class Item : public Entity
{
public:
	Item(const std::string& name, const std::string& description, Entity* parent, Item_Type item_type, bool storable = true, bool can_store = false, Exit* opens = nullptr, int damage = 0, bool in_pocket = true);
	~Item();
	void Look(Entity* origin) const;
	bool LookAt(Entity* origin,const std::string& thing) const;
	bool Take(Entity* origin, const std::string& thing);
	void DropTo(Entity* target);

	Item_Type item_type;
	Exit* opens;
	int damage;
	bool in_pocket;
	bool storable;
	bool can_store;
};


#endif // !ITEM_H
