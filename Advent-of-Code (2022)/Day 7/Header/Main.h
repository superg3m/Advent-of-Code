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

std::vector<std::string> copyFileData(std::ifstream &file)
{
    std::vector<std::string> ret;
    std::string line;
    while (std::getline(file, line))
    {
        ret.push_back(line);
    }

    return ret;
}

std::tuple<std::string, std::string, std::string, std::string> splitLine(const std::string &line)
{
    std::stringstream ss(line);
    std::string commandTag, command, name, size;

    if (std::isdigit(line[0])) { 
        ss >> size >> name;
    }
    else if (line[0] == '$') {
        ss >> commandTag >> command >> name;
    }
    else {
        ss >> command >> name;
    }

    return {commandTag, command, name, size};
}

void executeLine(Directory* &currentDirectory, const std::string &line)
{
    auto [commandTag, command, name, size] = splitLine(line);
    
    if (command == "dir" && !name.empty()) {
        Directory* tempDirectory = new Directory(name);
        currentDirectory->addSubdirectory(tempDirectory);
    } else if (std::isdigit(size[0])) {
        File* tempFile = new File(name, stoi(size));
        currentDirectory->addFile(tempFile);
    }

    if (command == "cd" && name == "..") { 
        currentDirectory = currentDirectory->getParentDirectory(); 
    } else if (command == "cd") { 
        if (name != "/") 
        { 
            currentDirectory = currentDirectory->getSubDirectoy(name); 
        } 
    } 
}

Directory* findRootDirectory(Directory *currentDirectory)
{
    if (currentDirectory->getParentDirectory() == nullptr) {
        return currentDirectory;
    }
    return findRootDirectory(currentDirectory->getParentDirectory());
}

int solve_and_return_part_one(Directory *current_directory) {
  static int partOneTotal{0};
  
  for(Directory* dir : current_directory->subDirectories) {
    if (dir->totalSize <= 100000) {
        partOneTotal += dir->totalSize;
    }
    solve_and_return_part_one(dir); // Discard result
  }
  return partOneTotal;
}

int solve_and_return_part_two(Directory* current_directory) {
  static std::vector<int> eligibleDirectories{};
  const int max_system_capacity = 70000000;
  const int root_directory_size = Directory::rootSize;
  const int memory_required = 30000000;

  for(Directory* dir : current_directory->subDirectories) {
    if (dir->totalSize >= memory_required - (max_system_capacity - root_directory_size)) {
        eligibleDirectories.push_back(dir->totalSize);
    }
    solve_and_return_part_two(dir); // Discard result
  }

  std::sort(eligibleDirectories.begin(), eligibleDirectories.end()); //Find smallest one that can be deleted by sorting

  return eligibleDirectories[0];
}