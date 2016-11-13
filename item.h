#ifndef ITEM_H
#define ITEM_H

#include "entity.h"
#include "exit.h"

enum Item_Type
{
	KEY,
	WEAPON,
	INFO,
	OBJECT
};

class Item : public Entity
{
public:
	Item(const std::string& name, const std::string& description, Entity* parent, Item_Type item_type, Exit* opens, int damage);
	~Item();
	void Look() const;

	Item_Type item_type;
	Exit* opens;
	int damage;
};


#endif // !ITEM_H
