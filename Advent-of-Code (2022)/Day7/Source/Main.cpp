#include "../Header/Main.h"

Directory *findRootDirectory(Directory* &currentDirectory)
{
    if(currentDirectory->getParentDirectory() == nullptr) {
        return currentDirectory;
    }
    return findRootDirectory(currentDirectory->getParentDirectory());
}

int main()
{
    std::vector<std::string> textFileData;
    std::ifstream textFile("../day7.txt");

    if(!textFile.is_open()) {
        std::cerr << "Err with the file \n";
    }
    else {
       textFileData = copyFileData(textFile);
    }

    std::stack<File> fileStack; 
    std::stack<Directory> directoryStack;
    Directory root("/");
    directoryStack.push(root);
    Directory *currentDirectory = &directoryStack.top();

    for (std::string line : textFileData)
    {
        executeLine(currentDirectory, directoryStack, fileStack, line);
    }

    currentDirectory = findRootDirectory(currentDirectory);

    currentDirectory->calculateDirectorySize();
    currentDirectory->printDirectoryTree();

    std::sort(Directory::partTwoDirectorySizes.begin(), Directory::partTwoDirectorySizes.end());
    std::cout << "Root size: " << currentDirectory->totalSize << std::endl;
    std::cout << "Part One: " << Directory::partOneTotal << std::endl;
    std::cout << "Part Two: " << Directory::partTwoDirectorySizes[0] << std::endl;
    delete currentDirectory;
    return 0;
}

std::vector<std::string> copyFileData(std::ifstream &file)
{
    std::vector<std::string> ret;
    std::string line;
    while (std::getline(file, line)) {
        ret.push_back(line);
    }

    return ret;
}

std::tuple<std::string, std::string, std::string, std::string> splitLine(const std::string& line) {
    std::stringstream ss(line);
    std::string commandTag, command, name, size;

    if(std::isdigit(line[0])) {
        ss >> size >> name;
    }  else if (line[0] == '$') {
        ss >> commandTag >> command >> name;
    } else {
        ss >> command >> name;
    }
    
    return {commandTag, command, name, size};
}

void executeLine(Directory* &currentDirectory, std::stack<Directory> &directoryStack, std::stack<File> &fileStack, const std::string& line) {
    auto [commandTag, command, name, size] = splitLine(line);

    if (command == "dir" && !name.empty()) {
        Directory tempDirectory(name);
        directoryStack.push(tempDirectory);
        currentDirectory->addSubdirectory(&directoryStack.top());
        
    } else if (std::isdigit(size[0])) {
        File tempFile(name, stoi(size));
        fileStack.push(tempFile);
        currentDirectory->addFile(fileStack.top());
    }

    if (command == "cd" && name == "..") {
        currentDirectory = currentDirectory->getParentDirectory();
    } else if (command == "cd") {
        if (name != "/") {
            currentDirectory = currentDirectory->getSubDirectoy(name);
        }
    } 
}

