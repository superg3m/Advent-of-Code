#include <iostream> 
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <stack>
#include <algorithm>

#include "../Header/Directory.h"
#include "../Header/File.h"

#pragma once

std::vector<std::string> copyFileData(std::ifstream &file);
std::tuple<std::string, std::string, std::string, std::string> splitLine(const std::string& line);
void executeLine(Directory* &currentDirectory, std::stack<Directory> &directoryStack, std::stack<File> &fileStack, const std::string& line);