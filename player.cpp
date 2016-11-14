#include "player.h"
#include "globals.h"
#include "constants.h"
#include <iostream>

Player::Player(const std::string& name, const std::string& description, Entity* parent, int hp, bool smart) : 
	Creature(name, description, parent, hp, smart)
{
	type = PLAYER;
	evolution_status = LARVA;
}

Player::~Player()
{
}

void Player::Look(Entity* origin) const
{
	std::cout << description + "\n";

	if (IsParasite())
	{
		std::cout << "You are inside a host, ";
		parent->Look(origin);
	}
}

bool Player::LookAt(Entity* origin,const std::string& thing) const
{
	bool thing_found = false;

	Entity* item = FindByString(thing);
	if (item != nullptr)
	{
		thing_found = true;
		item->Look(origin);
	}
	else
	{
		thing_found = parent->LookAt(GetPOV(), thing);
	}

	return thing_found;
}

bool Player::LookAtInside(Entity* origin,const std::string& item_name, const std::string& container_name) const
{
	bool all_found = false;

	Entity* container = FindByString(container_name);
	if (container == nullptr)
		all_found = parent->LookAtInside(GetPOV(), item_name, container_name);
	else
		all_found = container->LookAt(origin,item_name);

	return all_found;
}

bool Player::Inventory() const
{
	return PrintItems(LIST_INTROS::INVENTORY_PLAYER, true);
}

Room* Player::GetRoom() const
{
	if (IsParasite())
		return (Room*)parent->parent;
	else
		return (Room*)parent;
}

Entity* Player::GetPOV() const
{
	if (IsParasite())
		return parent;
	else
		return (Entity*)this;
}

bool Player::IsParasite() const
{
	return (parent->type == CREATURE);
}