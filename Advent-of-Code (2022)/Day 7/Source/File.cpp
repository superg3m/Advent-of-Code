#include "../Header/File.h"

File::File(const std::string &name, const int size)
{

        this->name = name;
        this->size = size;
}

File::~File()
{
        return;
}