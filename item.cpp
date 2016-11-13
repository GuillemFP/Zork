#include "item.h"

Item::Item(const std::string& name, const std::string& description, Entity* parent, Item_Type item_type, Exit* opens = nullptr, int damage = 0) : 
	Entity(name, description, parent), item_type(item_type), opens(opens), damage(damage)
{
	type = ITEM;
	if (this->item_type != KEY)
		opens = nullptr;
	if (this->damage != WEAPON)
		damage = 0;
}

Item::~Item()
{

}

void Item::Look() const
{

}