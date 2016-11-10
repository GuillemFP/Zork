#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <ios>
#include "globals.h"
#include "constants.h"


int main()
{
	std::vector<std::string> args;
	std::string player_input,sub;
	std::stringstream ss;

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

		args.clear();
		ss.clear();
	}

	std::cout << "Thanks for playing!";

	getchar();

}