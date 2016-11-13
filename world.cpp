#include "world.h"

World::World()
{
}


World::~World()
{
}

bool World::CommandHandler(std::vector<std::string>& args, std::string& output)
{
	bool accepted_cmd = true;

	switch (args.size())
	{
		case 1:
		{
			if (IsEqual(args[0], COMMAND::LOOK))
				player->Look();
			else if (IsEqual(args[0], COMMAND::MOVE))
			{
				output = OUTPUTS::_ERROR + args[0] + OUTPUTS::WHERE;
				accepted_cmd = false;
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
					player->LookAt(args[1]);
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
				player->LookAt(args[2]);
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