#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include "constants.h"
#include "globals.h"

class World
{
public:
	World();
	~World();

	std::string World::CommandHandler(const std::vector<std::string>& args);
};

#endif // !WORLD_H



