#include <iostream> 
#include <vector>
#include <string>
#include <set>
#include "../Header/File.h"


#pragma once 

class Directory 
{
public:
    std::string name;
    long totalSize;
    static long partOneTotal;
    
    std::vector<File> files;
    std::vector<Directory*> subDirectories;
    static std::vector<long> partTwoDirectorySizes;

    Directory(const std::string &name);
    ~Directory();

    void addSubdirectory(Directory *dir);

    void addFile(File file);

    void calculateDirectorySize(Directory *dir = nullptr);
    
    Directory *getSubDirectoy(const std::string &name);

    Directory* &getParentDirectory();

    void printDirectoryTree(int depth = 0);
private:
    Directory *parentDirectory;

};