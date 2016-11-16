#include "world.h"
#include "room.h"
#include "constants.h"
#include "item.h"
#include "exit.h"
#include <iostream>

World::World()
{
	Room* lab = new Room("Laboratory", "a small laboratory, filled with strange machines, desks full of scattered documents and some blood samples.");
	Room* medbay = new Room("Medbay", "a small room with a pair of litters and some medical instruments.");
	Room* engine = new Room("Engines", "a room filled with reactors and motors, used by the ship's propulsion system.");
	Room* hangar = new Room("Hangar", "a large room with a small scape pod on top of a large hatch.");
	Room* common = new Room("Kitchen", "a large room that serves as a kitchen and living room for the members of this ship.");
	Room* bridge = new Room("Bridge", "a large room full of computers and other piloting equipment. From a windows you can see how the ship floats above a dark-green planet.");
	Room* armory = new Room("Armory", "a small room filled with some military equipment. Seems like a lot of it is missing.");
	Room* dorms = new Room("Dorms", "a large room full of litters. Some metal closets are present.");
	Room* space = new Room("Space", "outside the ship nobody can hear your prey's screams.");

	end_room = space;

	entities.push_back(lab);
	entities.push_back(medbay);
	entities.push_back(engine);
	entities.push_back(hangar);
	entities.push_back(common);
	entities.push_back(bridge);
	entities.push_back(armory);
	entities.push_back(dorms);
	entities.push_back(space);

	Exit* exit1 = new Exit("North", "West", "a small ventilation duct near a big motor", "a small ventilation duct near the bottom of a file cabinet",
		"You crawl through the vent until you reach the adjacent room.", engine, lab, nullptr, false, true);
	Exit* exit2 = new Exit("East", "West", "a small ventilation duct near a desk full of samples", "a small ventilation duct near a litter",
		"You crawl through the vent until you reach the adjacent room.", lab, medbay, nullptr, false, true);
	Exit* exit3 = new Exit("North", "South", "a small metal door", "a small metal door", 
		"You cross the door's threshold into the other room.", hangar, lab);
	Exit* exit4 = new Exit("North", "South", "a small metal door", "a small metal door",
		"You cross the door's threshold into the other room.", common, medbay);
	Exit* exit5 = new Exit("East", "West", "a huge metal door", "a huge metal door", "You cross the door's threshold into the other room.", engine, hangar);
	Exit* exit6 = new Exit("East", "West", "a large and old curtain", "a large and old curtain", "You set aside the curtain and cross into the other room.", hangar, common);
	Exit* exit7 = new Exit("East", "West", "a big metal security door", "a big metal security door", "You cross the security door's threshold into the other room.", common, bridge);
	Exit* exit8 = new Exit("South", "North", "a big metal door", "a big metal door", "You cross the door's threshold into the other room.", hangar, armory);
	Exit* exit9 = new Exit("South", "North", "a small and blackened crystal door", "a small and blackened crystal door", "You cross the door's threshold into the other room.", common, dorms);
	Exit* exit10 = new Exit("East", "West", "a small ventilation duct near a weapon's cabinet", "a small ventilation duct near a litter",
		"You crawl through the vent until you reach the adjacent room.", armory, dorms, nullptr, false, true);
	Exit* exit11 = new Exit("East", "South", "a small ventilation duct near a metal closet", "a small ventilation duct near table full of computers",
		"You crawl through the vent until you reach the adjacent room.", dorms, bridge, nullptr, false, true);
	Exit* exit_outside = new Exit("Outside", "Inside", "a great hatch in the middle of the room", "a great hatch in the side of the spaceship",
		"You jump into the scape pod. As the spaceship begins the decompression, the pod moves towards the hatch.", hangar, space);

	entities.push_back(exit1);
	entities.push_back(exit2);
	entities.push_back(exit3);
	entities.push_back(exit4);
	entities.push_back(exit5);
	entities.push_back(exit6);
	entities.push_back(exit7);
	entities.push_back(exit8);
	entities.push_back(exit9);
	entities.push_back(exit10);
	entities.push_back(exit11);
	entities.push_back(exit_outside);

	Creature* scientist = new Creature("Scientist", "A human wearing a lab coat.", common, true, 50, 8, 9);
	Creature* medic = new Creature("Medic", "A human simple clothes stained with blood.", medbay, true, 60, 7, 11);
	Creature* soldier = new Creature("Soldier", "A strong human, dressed with military clothes full of mud and blood.", medbay, true, 100, 5, 12);
	soldier->hit_points = 20;
	Creature* boatswain = new Creature("Boatswain", "A tall human, wearing a fancy dress.", bridge, true, 100, 7, 14);
	Creature* captain = new Creature("Captain", "The captain of the ship, a strong and tall human.", bridge, true, 140, 15, 20);
	Creature* engineer = new Creature("Engineer", "A small and bowed human, wearing clothes cover with grease.", engine, true, 75, 5, 10);
	Creature* guard = new Creature("Guard", "A strong human, dressed with military clothes.", hangar, true, 80, 6, 16);
	Creature* rat = new Creature("Rat", "A big and smelly rat", dorms, false, 20, 1, 5, true);

	entities.push_back(scientist);
	entities.push_back(medic);
	entities.push_back(soldier);
	entities.push_back(boatswain);
	entities.push_back(captain);
	entities.push_back(engineer);
	entities.push_back(guard);
	entities.push_back(rat);

	Item* documents = new Item("Documents", "Analisis about Zorks, an alien species that infects other species in order to evolve to further stages.", lab, INFO, true, true);
	Item* report = new Item("Report", "An egg from Zork origin was recovered few days ago from ZORK's natal planet. Further research is needed.", documents, INFO);
	Item* photo = new Item("Photo", "A photo showing a corpse of a spider-like alien.", documents, INFO);
	Item* analisis = new Item("Analisis", "A blood analisis from a sample recovered from a ZORK alien.", medbay, INFO);

	entities.push_back(documents);
	entities.push_back(report);
	entities.push_back(photo);
	entities.push_back(analisis);

	Item* backpack = new Item("Backpack", "A backpack from a military use.", medbay, OBJECT, true, true, nullptr, 0, false);
	Item* briefcase = new Item("Briefcase", "A metallic briefcase. It seems to hold something important.", armory, OBJECT, true, true, nullptr, 0, false);
	Item* dossier = new Item("Dossier", "A dossier explaining structural damage in the escape pod.", briefcase, INFO, true, false);
	Item* bag = new Item("Bag", "A large bag. Its purpose is to store things", dorms, OBJECT, true, true, nullptr, 0, false);

	entities.push_back(backpack);
	entities.push_back(briefcase);
	entities.push_back(dossier);
	entities.push_back(bag);

	Item* lab_key = new Item("Latchkey", "A small metalic key, probably that of a door.", medic, KEY, true, false, exit3);
	Item* code = new Item("Code", "A computer code, probably that needed to open a magnetic sealed hatch.", briefcase, KEY, true, false, exit_outside);
	Item* magnetic_card = new Item("Card", "A magnetic card, probably that of a high security door.", captain, KEY, true, false, exit7);
	Item* armory_key = new Item("Key", "A large metalic key, probably that of a security door.", guard, KEY, true, false, exit8);

	exit3->SetKey(lab_key);
	exit_outside->SetKey(code);
	exit7->SetKey(magnetic_card);
	exit8->SetKey(armory_key);

	entities.push_back(lab_key);
	entities.push_back(code);
	entities.push_back(magnetic_card);
	entities.push_back(armory_key);

	Item* scalpel = new Item("Scalpel", "A small scalpel, stained with fresh blood.", medic, WEAPON, true, false, nullptr, 15, true);
	Item* wrench = new Item("wrench", "A metalic wrench, full of grease and oil.", engineer, WEAPON, true, false, nullptr, 25, false);
	Item* knife = new Item("Knife", "A big military knife.", backpack, WEAPON, true, false, nullptr, 40, true);
	Item* pistol = new Item("Pistol", "A heavy gun.", captain, WEAPON, true, false, nullptr, 60, true);
	Item* carabine = new Item("Carabine", "A human weapon that reaches large distances.", boatswain, WEAPON, true, false, nullptr, 80, false);
	Item* rifle = new Item("Rifle", "A human weapon that fires solid projectiles at large speed.", guard, WEAPON,true,false,nullptr,100,false);

	entities.push_back(scalpel);
	entities.push_back(wrench);
	entities.push_back(knife);
	entities.push_back(pistol);
	entities.push_back(carabine);
	entities.push_back(rifle);

	player = new Player(PLAYER_CONSTANTS::PLAYER, PLAYER_CONSTANTS::LARVA_DESC, lab, false, STATS_VALUE::LARVA_HP, STATS_VALUE::LARVA_DAMAGE);
	entities.push_back(player);

	lab_key->ChangeParent(scientist);

	std::cout << OUTPUTS::FIRST_DESCRIPTION << "\n";
}


World::~World()
{
	for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete *it;

	entities.clear();
}

bool World::CommandHandler(std::vector<std::string>& args, std::string& output, Output_type& output_handler)
{
	bool accepted_cmd = true;
	bool player_hostile = false;
	output_handler = ACCEPTED;

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
			else if (IsEqual(args[0], COMMAND::OPEN))
			{
				output = OUTPUTS::_ERROR + args[0] + OUTPUTS::WHAT;
				accepted_cmd = false;
			}
			else if (IsEqual(args[0], COMMAND::ATTACK))
			{
				output = OUTPUTS::_ERROR + args[0] + OUTPUTS::WHAT;
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
				else
				{
					if (player->evolution_status == BIPED && !player->IsParasite())
						player_hostile = true;
				}
			}
			else if (IsEqual(args[0], COMMAND::EVOLVE))
			{
				if (!player->Evolve())
				{
					if (player->evolution_status == BIPED)
					{
						output = "You cannot evolve any further. You are a perfect being among your species.\n";
						accepted_cmd = false;
					}
					else
					{
						output = OUTPUTS::_ERROR + OUTPUTS::NOT_EVOLVE;
						accepted_cmd = false;
					}
				}
				else
					player_hostile = true;
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
				else
				{
					if (player->evolution_status != LARVA && !player->IsParasite())
						player_hostile = true;
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
				else
				{
					if (player->evolution_status == BIPED && !player->IsParasite())
						player_hostile = true;
				}
			}
			else if (IsEqual(args[0], COMMAND::ATTACK))
			{
				player_hostile = AttackHandler(args[1]);
				if (!player_hostile)
				{
					output = OUTPUTS::_ERROR + args[0] + OUTPUTS::WHAT;
					accepted_cmd = false;
				}
			}
			else if (IsEqual(args[0], COMMAND::TAKE))
			{
				if (!TakeHandler(args[1]))
				{
					output = OUTPUTS::_ERROR + OUTPUTS::CANNOT + args[0] + " " + args[1] + ".";
					accepted_cmd = false;
				}
				else
				{
					if (player->evolution_status == BIPED && !player->IsParasite())
						player_hostile = true;
				}
			}
			else if (IsEqual(args[0], COMMAND::DROP))
			{
				if (!DropHandler(args[1]))
				{
					output = OUTPUTS::_ERROR + OUTPUTS::CANNOT + args[0] + " " + args[1] + ".";
					accepted_cmd = false;
				}
				else
				{
					if (player->evolution_status == BIPED && !player->IsParasite())
						player_hostile = true;
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
				else
				{
					if (player->evolution_status == BIPED && !player->IsParasite())
						player_hostile = true;
				}
			}
			else if (IsEqual(args[0], COMMAND::DROP) && IsEqual(args[2], CONNECTORS::INSIDE))
			{
				if (!DropToHandler(args[1],args[3]))
				{
					output = OUTPUTS::_ERROR + args[0] + OUTPUTS::WHAT + " " + args[2] + OUTPUTS::WHERE;
					accepted_cmd = false;
				}
				else
				{
					if (player->evolution_status == BIPED && !player->IsParasite())
						player_hostile = true;
				}
			}
			else if (IsEqual(args[0], COMMAND::ATTACK) && IsEqual(args[2], CONNECTORS::WITH))
			{
				player_hostile = AttackWithHandler(args[1], args[3]);
				if (!player_hostile)
				{
					output = OUTPUTS::_ERROR + args[0] + OUTPUTS::WHAT + " " + args[2] + OUTPUTS::WHAT;
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

	if (player_hostile)
		CounterattackHandler();
	else if (!accepted_cmd)
		output_handler = ERROR;

	if (!player->alive)
	{
		accepted_cmd = false;
		output_handler = KILLED;
	}
	else if (player->GetRoom() == end_room)
	{
		accepted_cmd = false;
		output_handler = FLED;
	}
	else if (!FindLivingHostiles())
	{
		accepted_cmd = false;
		output_handler = SURVIVOR;
	}

	return accepted_cmd;
}

void World::LookHandler()
{
	player->GetRoom()->Look(player->GetPOV());
}

bool World::LookAtHandler(const std::string& thing)
{
	Entity* pov = player->GetPOV();

	if (IsEqual(thing,NAMES::YOU))
	{
		player->Look(player);
		return true;
	}
	else if (IsEqual(thing,NAMES::HOST) && pov->type == CREATURE)
	{
		pov->Look(pov);
		return true;
	}
	else
	{
		pov->LookAt(pov, thing);
		return true;
	}

	return false;
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

bool World::AttackHandler(const std::string& target)
{
	Creature* attacker = (Creature*)player->GetPOV();
	Creature* target_creature = (Creature*)attacker->parent->FindEntityByStringType(target, CREATURE);

	if (target_creature != nullptr)
	{
		if (target_creature->alive)
		{
			return attacker->Attack(target_creature);
		}
	}
		
	return false;
}

bool World::AttackWithHandler(const std::string& target, const std::string& weapon)
{
	Creature* pov = (Creature*)player->GetPOV();
	Creature* target_creature = (Creature*)pov->GetRoom()->FindEntityByStringType(target, CREATURE);

	if (target_creature != nullptr)
	{
		if (target_creature->alive)
		{
			Item* weapon_used = (Item*)pov->FindEntityByStringType(weapon, ITEM);
			if (weapon_used != nullptr)
			{
				return pov->AttackWith(target_creature, weapon_used);
			}
		}
	}

	return false;
}

bool World::InventoryHandler()
{
	Entity* pov = player->GetPOV();
	Creature* controlled = (Creature*)pov;

	return controlled->Inventory();
}

void World::CounterattackHandler()
{
	std::list<Entity*> list_enemies;
	Creature* pov = (Creature*)player->GetPOV();
	pov->GetRoom()->FindAllByType(list_enemies, CREATURE);

	for (std::list<Entity*>::const_iterator it = list_enemies.begin(); it!=list_enemies.end(); ++it)
	{
		Creature* attacker = (Creature*)(*it);
		if (attacker->alive)
		{
			attacker->Attack(pov);
		}
	}
}

bool World::FindLivingHostiles() const
{
	for (std::list<Entity*>::const_iterator it = entities.begin(); it!=entities.end();++it)
	{
		if ((*it)->type == CREATURE)
		{
			Creature* npc = (Creature*)(*it);
			if (npc->alive && !npc->small)
				return true;
		}
	}
	return false;
}