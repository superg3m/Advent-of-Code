#include "../Header/Main.h"

int main()
{
    std::vector<std::string> textFileData;
    std::ifstream textFile("../day7.txt");

    if (!textFile.is_open()) {
        std::cerr << "Err with the file \n";
    } else {
        textFileData = copyFileData(textFile);
    }

    Directory* root = new Directory("/");
    Directory* currentDirectory = root;

    for (std::string line : textFileData) {
        executeLine(currentDirectory, line);
    }

    currentDirectory = findRootDirectory(currentDirectory);
    currentDirectory->calculateDirectorySize();
    currentDirectory->rootSize = currentDirectory->totalSize;
    currentDirectory->printDirectoryTree();

    std::cout << "Root size: " << currentDirectory->totalSize << std::endl;
    std::cout << "Part One: " << solve_and_return_part_one(currentDirectory) << std::endl;
    std::cout << "Part Two: " << solve_and_return_part_two(currentDirectory) << std::endl;

    delete currentDirectory;

    return 0;
}