#ifndef PLAYER_H
#define PLAYER_H

#include "creature.h"
#include "room.h"

enum Player_status
{
	LARVA,
	ARACHNID,
	BIPED
};

class Player : public Creature
{
public:
	Player(const std::string& name, const std::string& description, Entity* parent, bool smart = false, int hp = 100, int damage = 10);
	~Player();

	void Look(Entity* origin) const;
	bool LookAt(Entity* origin,const std::string& thing) const;
	bool Take(Entity* origin, const std::string& thing);
	bool Move(const std::string& direction);
	bool Inventory() const;
	bool Infect(const std::string& target);
	bool Feed();
	bool Evolve();
	void Damage(int damage_taken);
	void Kill();
	bool Attack(Creature* target);
	Room* GetRoom() const;
	Creature* GetHost() const;
	Entity* GetPOV() const;
	bool IsParasite() const;

	Player_status evolution_status;
	bool can_infect;
	bool can_take;
};



#endif // !PLAYER_H
