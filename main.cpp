#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <ios>
#include "globals.h"
#include "constants.h"
#include "world.h"


int main()
{
	std::vector<std::string> args;
	std::string player_input,sub,output;
	std::stringstream ss;

	World spaceship;

	while (true)
	{
		std::getline(std::cin, player_input);
		ss.str(player_input);

		while (ss >> sub)
			args.push_back(sub);

		if (args.size() > 0 && IsEqual(args[0], MENU::QUIT))
		{
			break;
		}

		output = spaceship.CommandHandler(args);
		if (output != "")
			std::cout << output << "\n";

		args.clear();
		ss.clear();
	}

	std::cout << "Thanks for playing!";

	getchar();

}