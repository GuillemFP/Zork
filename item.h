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
	Item(const std::string& name, const std::string& description, Entity* parent, Item_Type item_type, Exit* opens = nullptr, int damage = 0, bool big = false);
	~Item();
	void Look(Entity* origin) const;
	bool LookAt(Entity* origin,const std::string& thing) const;

	Item_Type item_type;
	Exit* opens;
	int damage;
	bool big;
};


#endif // !ITEM_H
