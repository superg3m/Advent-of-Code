#include "../Header/Directory.h"

long Directory::partOneTotal = 0;

long Directory::rootSize = 0;

std::vector<long> Directory::partTwoDirectorySizes{};
Directory::Directory(const std::string &name)
{
    this->name = name;
    this->totalSize = 0;
    this->partOneTotal = 0;
    this->parentDirectory = nullptr;

    return;
}

Directory::~Directory()
{
    for(File* file : this->files) {
        delete file;
    }
    this->files.clear();
    for (Directory* subDir : subDirectories)
    {
        delete subDir;
    }
    return;
}

void Directory::addSubdirectory(Directory *dir)
{
    this->subDirectories.push_back(dir);
    dir->parentDirectory = this;
    return;
}

void Directory::addFile(File* file)
{
    this->totalSize += file->size;
    this->files.push_back(file);
    return;
}

void Directory::calculateDirectorySize(Directory *dir)
{
    if (dir == nullptr)
    {
        dir = this;
    }
    this->totalSize = dir->totalSize;
    // std::cout << this->name << " (size: " << this->totalSize << ")\n";
    for (Directory* subDir : dir->subDirectories)
    {
        subDir->calculateDirectorySize(subDir);
        this->totalSize += subDir->totalSize;
        // std::cout << this->name << " (size: " << this->totalSize << ")\n";
    }

    return;
}

Directory* Directory::getSubDirectoy(const std::string &name)
{
    for (Directory *subDir : this->subDirectories)
    {
        if (name == subDir->name)
        {
            return subDir;
        }
    }
    std::cout << "failed to find a subDirectory with the name of " << name << std::endl;
    return nullptr;
}

Directory* Directory::getParentDirectory()
{
    return this->parentDirectory;
}

void Directory::printDirectoryTree(int depth)
{
    std::string directoryIndent(depth, ' ');
    std::string fileIndent(depth + 2, ' ');

    std::cout << directoryIndent << "- Dir: " << this->name << " (size: " << this->totalSize << ")\n";

    if (this->totalSize <= 100000)
    {
        Directory::partOneTotal += this->totalSize;
    }
    if (this->totalSize >= 30000000 -  (70000000 - Directory::rootSize))
    {
        
        Directory::partTwoDirectorySizes.push_back(this->totalSize);
    }
    for (File *file : this->files)
    {
        std::cout << fileIndent << "- File: " << file->name << "\n";
    }
    for (Directory *subDir : this->subDirectories)
    {
        subDir->printDirectoryTree(depth + 2);
    }

    return;
}
