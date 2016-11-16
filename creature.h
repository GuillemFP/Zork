#ifndef CREATURE_H
#define CREATURE_H

#include "entity.h"
#include "room.h"

class Creature : public Entity
{
public:
	Creature(const std::string& name, const std::string& description, Entity* parent, bool smart = true, int hp = 100, int evo_points = 5, int damage = 10);
	~Creature();
	virtual void Look(Entity* origin) const;
	virtual bool LookAt(Entity* origin,const std::string& thing) const;
	virtual bool Take(Entity* origin, const std::string& thing);
	bool Move(const std::string& direction);
	bool Open(const std::string& direction);
	virtual bool Inventory() const;
	virtual void Damage(int damage_taken);
	virtual void Heal(int damage_healed);
	virtual void Kill();
	bool PrintItems(const std::string& intro, bool only_seen) const;
	bool IsHost() const;
	bool IsInjured() const;
	Entity* FindParasite() const;
	virtual Room* GetRoom() const;

	int max_hit_points;
	int hit_points;
	int evolution_points;
	int damage;
	bool alive;
	bool smart;
};



#endif // !CREATURE_H
