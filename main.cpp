#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <ios>
#include <iostream>
#include "globals.h"
#include "constants.h"
#include "world.h"


int main()
{
	ReportMemoryLeaks();
	std::vector<std::string> args;
	std::string player_input,sub,output;
	std::stringstream ss;
	Output_type output_handler;

	std::cout << "         WELCOME TO...\n";
	std::cout << "__________            __    \n";
	std::cout << "\\____    /___________|  | __\n";
	std::cout << "  /     //  _ \\_  __ \\  |/ /\n";
	std::cout << " /     /(  <_> )  | \\/    < \n";
	std::cout << "/_______ \\____/|__|  |__|_ \\\n";
	std::cout << "        \\/                \\/\n";
	std::cout << "        FROM OUTER SPACE\n";
	std::cout << "\n";

	World spaceship;

	while (true)
	{
		std::cout << OUTPUTS::_WAITING;
		
		std::getline(std::cin, player_input);
		ss.str(player_input);

		while (ss >> sub)
			args.push_back(sub);

		if (args.size() > 0 && IsEqual(args[0], MENU::QUIT))
		{
			break;
		}

		if (!spaceship.CommandHandler(args, output, output_handler))
		{
			if (output_handler == ERROR)
			{
				std::cout << output << "\n";
			}
			else if (output_handler == KILLED)
			{
				std::cout << "\n";
				std::cout << "  ________                        ________                     \n";
				std::cout << " /  _____/_____    _____   ____   \\_____  \\___  __ ___________ \n";
				std::cout << "/   \\  ___\\__  \\  /     \\_/ __ \\   /   |   \\  \\/ // __ \\_  __ \\\n";
				std::cout << "\\    \\_\\  \\/ __ \\|  Y Y  \\  ___/  /    |    \\   /\\  ___/|  | \\/\n";
				std::cout << " \\______  (____  /__|_|  /\\___  > \\_______  /\\_/  \\___  >__|   \n";
				std::cout << "        \\/     \\/      \\/     \\/          \\/          \\/       \n";
				std::cout << "\nBe careful next time!";
				break;
			}
			else if (output_handler == FLED)
			{
				std::cout << "YOU FLED FROM THE SPACESHIP!\n";
				std::cout << "Now you can return to your planet.\n";
				break;
			}
			else if (output_handler == SURVIVOR)
			{
				std::cout << "YOU SURVIVED!\n";
				std::cout << "You are the last living creature remaining in this ship.\n";
				std::cout << "You will try to find a method to flee from it\n";
				std::cout << "or lay in wait for more preys...\n";
				break;
			}				
		}
		else
			std::cout << "\n";

		args.clear();
		ss.clear();
	}
	
	std::cout << "\n";
	std::cout << "THANKS FOR PLAYING!\n";
	std::cout << "(press any key to exit)\n";

	getchar();

}