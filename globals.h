#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <vector>
#include "memleaks.h"

bool IsEqual(const std::string& first, const std::string& second);
bool IsEqual(const std::string& first, const std::vector<std::string>& second);

#endif // !GLOBALS_H

