#include "player.h"
#include "globals.h"
#include "constants.h"
#include <iostream>

Player::Player(const std::string& name, const std::string& description, Entity* parent, int hp) : Creature(name, description, parent, hp)
{
	type = PLAYER;
	evolution_status = LARVA;
}

Player::~Player()
{
}

void Player::Look() const
{
	if (parent->type == CREATURE)
	{ 
		std::cout << OUTPUTS::_ACCEPTED + "You are inside a " + parent->name + ", your current host.\n";
		parent->parent->Look();
	}
	else
		parent->Look();
}

void Player::LookAt(const std::string& thing) const
{
	if (parent->type == CREATURE)
	{
		if (IsEqual(thing, NAMES::HOST))
			parent->Look();
		else
			parent->LookAt(thing);
	}
	else
	{
		if (IsEqual(thing,NAMES::YOU))
			State();
		else
			parent->LookAt(thing);
	}
}

void Player::State() const
{
	if (evolution_status == LARVA)
	{
		std::cout << OUTPUTS::_ACCEPTED + PLAYER_CONSTANTS::LARVA_DESC + "\n";
	}
	else if (evolution_status == ARACHNID)
	{
		std::cout << OUTPUTS::_ACCEPTED + PLAYER_CONSTANTS::ARACHNID_DESC + "\n";
	}
	else if (evolution_status == BIPED)
	{
		std::cout << OUTPUTS::_ACCEPTED + PLAYER_CONSTANTS::BIPED_DESC + "\n";
	}

	if (parent->type == CREATURE)
	{
		std::cout << OUTPUTS::_ACCEPTED + "You are inside a " + parent->name + ", your current host.\n";
	}
}