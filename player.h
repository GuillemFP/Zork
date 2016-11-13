#ifndef PLAYER_H
#define PLAYER_H

#include "creature.h"

enum Player_status
{
	LARVA,
	ARACHNID,
	BIPED
};

class Player : public Creature
{
public:
	Player(const std::string& name, const std::string& description, Entity* parent, int hp);
	~Player();

	void Look() const;
	void LookAt(const std::string& thing) const;
	void State() const;

	Player_status evolution_status;
};



#endif // !PLAYER_H
