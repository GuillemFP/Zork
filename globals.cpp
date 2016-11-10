#include "globals.h"

bool IsEqual(const std::string& first, const std::string& second)
{
	return (_stricmp(first.c_str(), second.c_str()) == 0);
}

bool IsEqual(const std::string& first, const std::vector<std::string>& second)
{
	bool equal = false;
	std::vector<std::string>::const_iterator it = second.begin();

	while (!equal && it != second.end())
	{
		equal = IsEqual(first, *it);
		it++;
	}

	return equal;
}