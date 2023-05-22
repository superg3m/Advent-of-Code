#include <iostream> 
#include <vector>
#include <string>

#pragma once

class File
{
public:
    std::string name;
    int size;
    File(const std::string &name, const int size);
    ~File();
};