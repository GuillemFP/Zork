#include "world.h"

World::World()
{
}


World::~World()
{
}

std::string World::CommandHandler(const std::vector<std::string>& args)
{
	std::string output = "";

	switch (args.size())
	{
		case 1:
		{
			if (IsEqual(args[0], COMMAND::MOVE))
				output = OUTPUTS::_ERROR + args[0] + OUTPUTS::WHERE;
			else
				output = OUTPUTS::_ERROR + OUTPUTS::MISTAKE;
			break;
		}
		default:
		{
			output = OUTPUTS::_ERROR + OUTPUTS::MISTAKE;
			break;
		}
	}

	return output;
}