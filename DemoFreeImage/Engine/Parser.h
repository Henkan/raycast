#pragma once
#include <vector>
#include <string>

#include "Scene.h"
class Parser
{
public :
	Parser() = default;
	static std::vector<std::string> splitString(const std::string& stringToParse, char delimiter);
	static Scene parseFileIntoScene(const std::string& fileName);
};

