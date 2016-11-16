#include "player.h"
#include "globals.h"
#include "constants.h"
#include <iostream>

Player::Player(const std::string& name, const std::string& description, Entity* parent, bool smart, int hp, int damage) :
	Creature(name, description, parent, smart, hp, 0, damage, true)
{
	type = PLAYER;
	evolution_status = LARVA;
	can_infect = true;
	can_take = false;
}

Player::~Player()
{
}

void Player::Look(Entity* origin) const
{
	std::cout << description;
	if (IsInjured())
		std::cout << " You are" << OUTPUTS::INJURED;
	std::cout << "\n";

	if (IsParasite())
	{
		std::cout << "You are inside a host, " << parent->name << ".\n";
	}

	if (evolution_status == LARVA && evolution_points >= STATS_VALUE::LARVA_TO_ARACHNID)
	{
		std::cout << "You are ready to evolve.\n";
	}
	else if (evolution_status == ARACHNID && evolution_points >= STATS_VALUE::ARACHNID_TO_BIPED)
	{
		std::cout << "You are ready to evolve.\n";
	}
}

bool Player::LookAt(Entity* origin,const std::string& thing) const
{
	bool thing_found = false;

	Entity* item = FindEntityByString(thing);
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

bool Player::Move(const std::string& direction)
{
	Room* room = GetRoom();
	Exit* exit = room->GetExit(direction);

	if (exit == nullptr)
		return false;

	if (exit->locked)
	{
		std::cout << "It's locked. You cannot move further in that direction.\n";
	}
	else
	{
		if (!small && exit->small)
		{
			std::cout << "You cannot go in that direction. The opening is to small for you.\n";
		}
		else if (evolution_status == LARVA && !exit->small)
		{
			std::cout << "You are to small and weak to even open the door in that direction.\n";
		}
		else
		{
			std::cout << "You go " + direction + " through " + exit->GetDescription(room) + ". " + exit->connection_desc + "\n";
			ChangeParent(exit->GetDestination(room));
		}
	}

	return true;
}

bool Player::Inventory() const
{
	return PrintItems(LIST_INTROS::INVENTORY_PLAYER, false);
}

bool Player::Infect(const std::string& target)
{
	if (IsParasite())
	{
		std::cout << OUTPUTS::_ERROR << "You cannot infect from inside a living creature.\n";
		return true;
	}
	else if (can_infect)
	{
		Room* player_room = GetRoom();
		Entity* target_creature = player_room->FindEntityByStringType(target, CREATURE);
		if (target_creature != nullptr)
		{
			Creature* creature = (Creature*)target_creature;
			if (creature->alive)
			{
				if (evolution_status == LARVA && creature->IsInjured())
				{
					std::cout << "You stealthy crawl in " << creature->name << " direction. ";
				}
				else
				{
					std::cout << creature->name << " notices you while you are approching it.\n";
					bool attack_succeds = creature->Attack(this);
					if (!alive)
					{
						return true;
					}
				}
				ChangeParent(creature);
				std::cout << "You infected " << creature->name << ". It now serves as your host. You can control him and feed on it. You cannot abandon this corpse until it dies.\n";
			}
			else
				std::cout << "You cannot infect a dead creature.\n";
			return true;
		}
		else
			return false;
	}
	else
	{
		std::cout << OUTPUTS::_ERROR << "You no longer have the ability to infect other people.\n";
		return true;
	}
	return false;
}

bool Player::Feed()
{
	if (IsParasite())
	{
		Creature* host = GetHost();
		std::cout << "You feed on " << host->name << ". ";
		host->Damage(damage);
		Heal(damage);
		evolution_points += host->evolution_points;
		return true;
	}
	else
		return false;
}

bool Player::Evolve()
{
	if (evolution_status == LARVA)
	{
		if (evolution_points >= STATS_VALUE::LARVA_TO_ARACHNID)
		{
			evolution_status = ARACHNID;
			description = PLAYER_CONSTANTS::ARACHNID_DESC;
			evolution_points -= STATS_VALUE::LARVA_TO_ARACHNID;
			if (evolution_points < 0)
				evolution_points = 0;
			if (IsParasite())
				GetHost()->Kill();
			std::cout << "You evolved. ";
			Look(this);
			max_hit_points = STATS_VALUE::ARACHNID_HP;
			Heal(STATS_VALUE::ARACHNID_HP - STATS_VALUE::LARVA_HP);
			damage = STATS_VALUE::ARACHNID_DAMAGE;
			return true;
		}
		else
			return false;
		
	}
	else if (evolution_status == ARACHNID)
	{
		if (evolution_points >= STATS_VALUE::ARACHNID_TO_BIPED)
		{
			evolution_status = BIPED;
			description = PLAYER_CONSTANTS::BIPED_DESC;
			evolution_points -= STATS_VALUE::ARACHNID_TO_BIPED;
			if (evolution_points < 0)
				evolution_points = 0;
			if (IsParasite())
				GetHost()->Kill();
			std::cout << "You evolved. ";
			Look(this);
			max_hit_points = STATS_VALUE::BIPED_HP;
			Heal(STATS_VALUE::BIPED_HP - STATS_VALUE::ARACHNID_HP);
			damage = STATS_VALUE::BIPED_DAMAGE;
			can_take = true;
			can_infect = false;
			smart = true;
			small = false;
			return true;
		}
			return false;
	}
	return false;
}

void Player::Damage(int damage_taken)
{
	hit_points -= damage_taken;
	std::cout << "You take damage.";

	if (hit_points <= 0)
	{
		std::cout << " ";
		Kill();
	}
	else if (IsInjured())
		std::cout << " " << "You are" << OUTPUTS::INJURED << "\n";
	else
		std::cout << "\n";
}

void Player::Kill()
{
	alive = false;
	std::cout << "You drop dead on the ground.\n";
}

bool Player::Attack(Creature* target)
{
	if (evolution_status == LARVA)
		std::cout << "You attack " << target->name << " with your fangs.";
	else if (evolution_status == ARACHNID)
		std::cout << "You attack " << target->name << " with your claws.";
	else if (evolution_status == BIPED)
		std::cout << "You jump at " << target->name << " and viciously tear its flesh apart.";
	std::cout << " ";
	target->Damage(damage);
	return true;
}

Room* Player::GetRoom() const
{
	if (IsParasite())
		return (Room*)parent->parent;
	else
		return (Room*)parent;
}

Creature* Player::GetHost() const
{
	if (IsParasite())
		return (Creature*)parent;
	else
		return nullptr;
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