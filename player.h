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
	Player(const std::string& name, const std::string& description, Entity* parent, int hp = 100, bool smart = false);
	~Player();

	void Look(Entity* origin) const;
	bool LookAt(Entity* origin,const std::string& thing) const;
	bool LookAtInside(Entity* origin,const std::string& item_name, const std::string& container_name) const;
	bool Inventory() const;
	Room* GetRoom() const;
	Entity* GetPOV() const;
	bool IsParasite() const;

	Player_status evolution_status;
};



#endif // !PLAYER_H
