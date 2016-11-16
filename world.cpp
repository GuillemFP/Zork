#include "world.h"
#include "room.h"
#include "constants.h"
#include "item.h"
#include "exit.h"
#include <iostream>

World::World()
{
	Room* lab = new Room("Laboratory", "a small laboratory, filled with strange machines and desks full of scattered documents.");
	Room* engine = new Room("Engines", "a room filled with reactors and motors, used by the ship's propulsion system.");
	Room* hangar = new Room("Hangar", "a large room with a small scape pod on top of a large hatch.");

	entities.push_back(lab);
	entities.push_back(engine);
	entities.push_back(hangar);

	Exit* exit1 = new Exit("West", "North", "a small ventilation duct near the bottom of a file cabinet", "a small ventilation duct near a big motor",
		"You crawl through the vent until you reach the adjacent room.", lab, engine);
	Exit* exit3 = new Exit("North", "South", "a small metal door", "a small metal door", 
		"You cross the door's threshold into the other room.", hangar, lab);
	Exit* exit5 = new Exit("East", "West", "a big metal door", "a big metal door", "You cross the door's threshold into the other room.", engine, hangar);

	entities.push_back(exit1);
	entities.push_back(exit3);
	entities.push_back(exit5);

	Item* documents1 = new Item("Documents", "Analisis about Zorks, an alien species that infects other species in order to evolve to further stages.", lab, INFO,true,true);
	Item* report1 = new Item("Report", "An egg from Zork origin was recovered few days ago from Zork's natal planet. Further research is needed.", documents1, INFO);
	Item* photo1 = new Item("Photo", "A photo showing a corpse of a spider-like alien.", documents1, INFO);
	Item* scalpel = new Item("Scalpel", "A small scalpel, stained with fresh blood.", lab, WEAPON);
	Item* lab_key = new Item("Key", "A small metalic key, probably that of a door.", lab, KEY, true, false, exit3);
	Item* rifle = new Item("Rifle", "A human weapon that fires solid projectiles.", lab, WEAPON,false,false,nullptr,0,false);

	exit3->SetKey(lab_key);

	entities.push_back(documents1);
	entities.push_back(report1);
	entities.push_back(photo1);
	entities.push_back(scalpel);
	entities.push_back(lab_key);

	Creature* scientist = new Creature("Scientist", "A human wearing a lab coat.", lab, true, 50, 8, 12);
	entities.push_back(scientist);

	player = new Player(PLAYER_CONSTANTS::PLAYER, PLAYER_CONSTANTS::LARVA_DESC, lab, false, STATS_VALUE::LARVA_HP, STATS_VALUE::LARVA_DAMAGE);
	entities.push_back(player);

	lab_key->ChangeParent(scientist);
	rifle->ChangeParent(scientist);

	LookHandler();
	player->Look(player);
}


World::~World()
{
	for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete *it;

	entities.clear();
}

bool World::CommandHandler(std::vector<std::string>& args, std::string& output)
{
	bool accepted_cmd = true;

	switch (args.size())
	{
		case 1:
		{
			if (IsEqual(args[0], COMMAND::LOOK))
			{
				LookHandler();
			}
			else if (IsEqual(args[0], COMMAND::MOVE))
			{
				output = OUTPUTS::_ERROR + args[0] + OUTPUTS::WHERE;
				accepted_cmd = false;
			}
			else if (IsEqual(args[0], COMMAND::TAKE))
			{
				output = OUTPUTS::_ERROR + args[0] + OUTPUTS::WHAT;
				accepted_cmd = false;
			}
			else if (IsEqual(args[0], COMMAND::DROP))
			{
				output = OUTPUTS::_ERROR + args[0] + OUTPUTS::WHAT;
				accepted_cmd = false;
			}
			else if (IsEqual(args[0], COMMAND::INFECT))
			{
				output = OUTPUTS::_ERROR + args[0] + OUTPUTS::WHAT;
				accepted_cmd = false;
			}
			else if (IsEqual(args[0], COMMAND::FEED))
			{
				if (!player->Feed())
				{
					output = OUTPUTS::_ERROR + OUTPUTS::NOT_FEED;
					accepted_cmd = false;
				}	
			}
			else if (IsEqual(args[0], COMMAND::EVOLVE))
			{
				if (!player->Evolve())
				{
					output = OUTPUTS::_ERROR + OUTPUTS::NOT_EVOLVE;
					accepted_cmd = false;
				}
			}
			else if (IsEqual(args[0], COMMAND::INVENTORY))
			{
				if (!InventoryHandler())
				{
					output = OUTPUTS::INVENTORY_EMPTY;
					accepted_cmd = false;
				}
			}
			else if (IsEqual(args[0],COMMAND::STATE))
			{
				player->Look(player);
			}
			else
			{
				output = OUTPUTS::_ERROR + OUTPUTS::MISTAKE;
				accepted_cmd = false;
			}
			break;
		}
		case 2:
		{
			if (IsEqual(args[0], COMMAND::LOOK))
			{
				if (IsEqual(args[1], CONNECTORS::AT))
				{
					output = OUTPUTS::_ERROR + args[0] + " " + args[1] + OUTPUTS::WHAT;
					accepted_cmd = false;
				}
				else
				{
					if (!LookAtHandler(args[1]))
					{
						output = OUTPUTS::_ERROR + OUTPUTS::CANNOT + args[0] + " at " + args[1] + ".";
						accepted_cmd = false;
					}
				}
			}
			else if (IsEqual(args[0], COMMAND::MOVE))
			{
				if (!MoveHandler(args[1]))
				{
					if (IsEqual(args[1],COMMAND::DIRECTIONS))
					{
						output = OUTPUTS::CANNOT + args[0] + " in that direction.";
						accepted_cmd = false;
					}
					else
					{
						output = OUTPUTS::_ERROR + args[0] + OUTPUTS::WHERE;
						accepted_cmd = false;
					}
				}
			}
			else if (IsEqual(args[0], COMMAND::OPEN))
			{
				if (!OpenHandler(args[1]))
				{
					if (IsEqual(args[1], COMMAND::DIRECTIONS))
					{
						output = OUTPUTS::_ERROR + OUTPUTS::CANNOT + args[0] + " anything in that direction.";
						accepted_cmd = false;
					}
					else
					{
						output = OUTPUTS::_ERROR + args[0] + OUTPUTS::WHAT;
						accepted_cmd = false;
					}
				}
			}
			else if (IsEqual(args[0], COMMAND::TAKE))
			{
				if (!TakeHandler(args[1]))
				{
					output = OUTPUTS::_ERROR + OUTPUTS::CANNOT + args[0] + " " + args[1] + ".";
					accepted_cmd = false;
				}
			}
			else if (IsEqual(args[0], COMMAND::DROP))
			{
				if (!DropHandler(args[1]))
				{
					output = OUTPUTS::_ERROR + OUTPUTS::CANNOT + args[0] + " " + args[1] + ".";
					accepted_cmd = false;
				}
			}
			else if (IsEqual(args[0], COMMAND::INFECT))
			{
				if (!player->Infect(args[1]))
				{
					output = OUTPUTS::_ERROR + OUTPUTS::CANNOT + args[0] + " " + args[1] + ".";
					accepted_cmd = false;
				}
			}
			else
			{
				output = OUTPUTS::_ERROR + OUTPUTS::MISTAKE;
				accepted_cmd = false;
			}
			break;
		}
		case 3:
		{
			if (IsEqual(args[0], COMMAND::LOOK) && IsEqual(args[1], CONNECTORS::AT))
			{
				if (!LookAtHandler(args[2]))
				{
					output = OUTPUTS::_ERROR + args[0] + " " + args[1] + OUTPUTS::WHAT;
					accepted_cmd = false;
				}
			}
			else if (IsEqual(args[0], COMMAND::OPEN))
			{
				if (!OpenHandler(args[1]))
				{
					if (IsEqual(args[1], COMMAND::DIRECTIONS))
					{
						output = OUTPUTS::_ERROR + OUTPUTS::CANNOT + args[0] + " anything in that direction.";
						accepted_cmd = false;
					}
					else
					{
						output = OUTPUTS::_ERROR + args[0] + OUTPUTS::WHAT;
						accepted_cmd = false;
					}
				}
			}
			else
			{
				output = OUTPUTS::_ERROR + OUTPUTS::MISTAKE;
				accepted_cmd = false;
			}
			break;
		}
		case 4:
		{
			if (IsEqual(args[0], COMMAND::LOOK) && IsEqual(args[2],CONNECTORS::INSIDE))
			{
				if (!LookAtInsideHandler(args[1],args[3]))
				{
					output = OUTPUTS::_ERROR + args[0] + OUTPUTS::WHAT + " " + args[2] + OUTPUTS::WHAT;
					accepted_cmd = false;
				}
			}
			else if (IsEqual(args[0], COMMAND::TAKE) && IsEqual(args[2], CONNECTORS::FROM))
			{
				if (!TakeFromHandler(args[1], args[3]))
				{
					output = OUTPUTS::_ERROR + args[0] + OUTPUTS::WHAT + " " + args[2] + OUTPUTS::WHERE;
					accepted_cmd = false;
				}
			}
			else if (IsEqual(args[0], COMMAND::DROP) && IsEqual(args[2], CONNECTORS::INSIDE))
			{
				if (!DropToHandler(args[1],args[3]))
				{
					output = OUTPUTS::_ERROR + args[0] + OUTPUTS::WHAT + " " + args[2] + OUTPUTS::WHERE;
					accepted_cmd = false;
				}
			}
			else
			{
				output = OUTPUTS::_ERROR + OUTPUTS::MISTAKE;
				accepted_cmd = false;
			}
			break;
		}
		case 5:
		{
			if (IsEqual(args[0], COMMAND::LOOK) && IsEqual(args[1],CONNECTORS::AT) && IsEqual(args[3], CONNECTORS::INSIDE))
			{
				if (!LookAtInsideHandler(args[2], args[4]))
				{
					output = OUTPUTS::_ERROR + args[0] + " " + args[1] + OUTPUTS::WHAT + " " + args[3] + OUTPUTS::WHAT;
					accepted_cmd = false;
				}
			}
			else
			{
				output = OUTPUTS::_ERROR + OUTPUTS::MISTAKE;
				accepted_cmd = false;
			}
			break;
		}
		default:
		{
			output = OUTPUTS::_ERROR + OUTPUTS::MISTAKE;
			accepted_cmd = false;
			break;
		}
	}

	return accepted_cmd;
}

void World::LookHandler()
{
	player->GetRoom()->Look(player->GetPOV());
}

bool World::LookAtHandler(const std::string& thing)
{
	bool thing_found = false;

	if (IsEqual(thing,NAMES::YOU))
	{
		player->Look(player);
		thing_found = true;
	}
	else if (IsEqual(thing,NAMES::HOST) && player->parent->type == CREATURE)
	{
		player->parent->Look(player->parent);
		thing_found = true;
	}
	else
	{
		thing_found = player->LookAt(player->GetPOV(),thing);
	}

	return thing_found;
}

bool World::LookAtInsideHandler(const std::string& item_name, const std::string& container_name)
{
	Entity* pov = player->GetPOV();

	return pov->LookAtInside(pov, item_name, container_name);
}

bool World::TakeHandler(const std::string& thing)
{
	Entity* pov = player->GetPOV();

	if (!player->IsParasite() && !player->can_take)
	{
		std::cout << OUTPUTS::_ERROR << "You do not posses prehensile extremities in order to pick up things.\n";
		return true;
	}
	else
	{
		Room* present_room = player->GetRoom();
		return present_room->Take(pov, thing);
	}
	return false;
}

bool World::TakeFromHandler(const std::string& item_name, const std::string& container_name)
{
	Entity* pov = player->GetPOV();

	if (!player->IsParasite() && !player->can_take)
	{
		std::cout << OUTPUTS::_ERROR << "You do not posses prehensile extremities in order to pick up things.\n";
		return true;
	}
	else
	{
		return pov->TakeFrom(pov, item_name, container_name);
	}
	return false;
}

bool World::DropHandler(const std::string& thing)
{
	Room* target_room = player->GetRoom();

	return DropToHandler(thing, target_room->name);
}

bool World::DropToHandler(const std::string& item_name, const std::string& container_name)
{
	Entity* pov = player->GetPOV();
	Entity* item_drop = pov->FindEntityByStringType(item_name, ITEM);

	if (item_drop != nullptr)
	{
		Item* item = (Item*)item_drop;
		return pov->Drop(item_drop, container_name);
	}

	return false;
}

bool World::MoveHandler(const std::string& direction)
{
	Entity* pov = player->GetPOV();
	Creature* walker = (Creature*)pov;

	return walker->Move(direction);
}

bool World::OpenHandler(const std::string& direction)
{
	Entity* pov = player->GetPOV();
	Creature* opener = (Creature*)pov;

	return opener->Open(direction);
}

bool World::InventoryHandler()
{
	Entity* pov = player->GetPOV();
	Creature* controlled = (Creature*)pov;

	return controlled->Inventory();
}