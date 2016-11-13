#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include <list>
#include "constants.h"
#include "globals.h"

#include "entity.h"
#include "player.h"

class World
{
public:
	World();
	~World();
	bool World::CommandHandler(std::vector<std::string>& args, std::string& output);

	Player* player;
	std::list<Entity*> entities;
};

#endif // !WORLD_H



