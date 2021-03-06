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
	bool CommandHandler(std::vector<std::string>& args, std::string& output, Output_type& output_handler);
	void LookHandler();
	bool LookAtHandler(const std::string& thing);
	bool LookAtInsideHandler(const std::string& item_name, const std::string& container_name);
	bool TakeHandler(const std::string& thing);
	bool TakeFromHandler(const std::string& item_name, const std::string& container_name);
	bool DropHandler(const std::string& thing);
	bool DropToHandler(const std::string& item_name, const std::string& container_name);
	bool MoveHandler(const std::string& direction);
	bool OpenHandler(const std::string& direction);
	bool AttackHandler(const std::string& target);
	bool AttackWithHandler(const std::string& target, const std::string& weapon);
	bool InventoryHandler();
	void CounterattackHandler();
	bool FindLivingHostiles() const;

	Player* player;
	std::list<Entity*> entities;
	Room* end_room;
};

#endif // !WORLD_H



