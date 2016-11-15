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
		std::cout << "You are inside a host, " << parent->name << ".\n";
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

bool Player::Take(Entity* origin, const std::string& thing)
{
	return false;
}

bool Player::Inventory() const
{
	return PrintItems(LIST_INTROS::INVENTORY_PLAYER, false);
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