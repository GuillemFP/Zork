#ifndef CREATURE_H
#define CREATURE_H

#include "entity.h"

class Creature : public Entity
{
public:
	Creature(const std::string& name, const std::string& description, Entity* parent, int hp);
	~Creature();
	virtual void Look() const;
	virtual void LookAt(const std::string& thing) const;

	int hit_points;
};



#endif // !CREATURE_H
