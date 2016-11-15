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
	bool CommandHandler(std::vector<std::string>& args, std::string& output);
	void LookHandler();
	bool LookAtHandler(const std::string& thing);
	bool LookAtInsideHandler(const std::string& item_name, const std::string& container_name);
	bool MoveHandler(const std::string& direction);
	bool OpenHandler(const std::string& direction);
	bool TakeHandler(const std::string& thing);
	bool TakeFromHandler(const std::string& item_name, const std::string& container_name);
	bool InventoryHandler();

	Player* player;
	std::list<Entity*> entities;
};

#endif // !WORLD_H



