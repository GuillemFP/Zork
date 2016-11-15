#ifndef CREATURE_H
#define CREATURE_H

#include "entity.h"
#include "room.h"

class Creature : public Entity
{
public:
	Creature(const std::string& name, const std::string& description, Entity* parent, int hp = 100, bool smart = true);
	~Creature();
	virtual void Look(Entity* origin) const;
	virtual bool LookAt(Entity* origin,const std::string& thing) const;
	virtual bool Take(Entity* origin, const std::string& thing);
	bool Move(const std::string& direction);
	bool Open(const std::string& direction);
	virtual bool Inventory() const;
	bool PrintItems(const std::string& intro, bool only_seen) const;
	virtual Room* GetRoom() const;

	int hit_points;
	bool alive;
	bool smart;
};



#endif // !CREATURE_H
