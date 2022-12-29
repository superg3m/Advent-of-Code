#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <variant>
#include <algorithm>
#include <iterator>
#include <unordered_set>



struct fileStruct {
    std::string name;
    std::string Type = "file";
    int fileSize;
};

class directoryStruct {
    
    public: 
        std::string name;
        int uniqueID;
        std::string Type = "dir";
        long totalSize = 0;
        std::vector<std::variant<directoryStruct, fileStruct>> contains;
};

// METHODS
std::vector<std::string> copyTextFileData(std::ifstream& file);
std::pair<std::string, std::string> splitLine(std::string line);

void executeLine(std::string s, std::vector<directoryStruct>& pastDirectories, std::vector<directoryStruct>& directoryObjectVector,  std::string currentDirectory, std::string previousDirectory, int& previousIndex, int& n);
void parseDirectoryData(std::string x, std::vector<directoryStruct>& directoryObjectVector, int& n);
void parseFileData(std::string x, std::string y, std::vector<directoryStruct>& directoryObjectVector, int& n);
void printDirectories(int& i, std::vector<directoryStruct>& directoryObjectVector);
void removeDuplicates(std::vector<directoryStruct>& directoryObjectVector);

int findDirectoryIndex(std::string dirName, std::vector<directoryStruct>& directoryObjectVector);
long calculateDirectorySizeRecursively(directoryStruct& directoryObject, std::vector<directoryStruct>& directoryObjectVector, std::string prev);

int main() {
    std::ifstream textFile;
    std::vector<std::string> fileData;

    std::vector<directoryStruct> directoryObjectVector;

    std::vector<directoryStruct> pastDirectories;

    std::vector<directoryStruct> previouslyVisitedDirectories;
    int n = 0;
    int previousIndex = 0;


    directoryStruct directoryRootObject;
    directoryRootObject.name = "ROOT";
    directoryObjectVector.push_back(directoryRootObject);

    // GO BACK UNTIL char at index i is equal to / and then reverse the directory letters: ROOT/got/hide -> ROOT/got unless the reversed string == ROOT
    std::string currentDirectory = "ROOT";
    std::string previousDirectory;

    textFile.open("Day7.txt");
    if(!textFile.is_open()) {
        std::cerr << "Err with the file \n";
    }
    else {
        fileData = copyTextFileData(textFile);
    }

    for(std::string s : fileData) {
        executeLine(s, pastDirectories, directoryObjectVector, currentDirectory, previousDirectory, previousIndex, n);
    }
    
    calculateDirectorySizeRecursively(directoryObjectVector[0], directoryObjectVector, "ROOT");
    
    
    for(int i = 0; i < directoryObjectVector.size(); i++) {
        std::cout << "In the Directory: " << directoryObjectVector[i].name << "\n";
        printDirectories(i, directoryObjectVector);
    }

    for(int i = 0; i < directoryObjectVector.size(); i++) {
        // THIS IS THE PROBLEM RIGHT NOW THE FILE SIZE IS WRONG FOR DIRECTORIES
        //std::cout << "In the " << directoryObjectVector[i].name << " Directory \n";
    }

    // Helps calculate ROOT directory size
    // Ideally this is replaced with the method calculateDirectorySize()
    for(int i = 1; i < directoryObjectVector.size(); i++) {
        std::cout << directoryObjectVector[i].name << ": " << directoryObjectVector[i].totalSize << "\n";
        //directoryObjectVector[0].totalSize += directoryObjectVector[i].totalSize;
    }
    
    std::vector<int> sumVector;

    for(int i = 1; i < directoryObjectVector.size(); i++) {
        if(directoryObjectVector[i].totalSize <= 100000) {
            sumVector.push_back(directoryObjectVector[i].totalSize);
        }
    }

    int sum = 0;
    for(int i = 0; i < sumVector.size(); i++) {
        sum += sumVector[i];
    }

    std::cout << "PART 1: " << sum << "\n";

    std::cout << "ROOT SIZE: " << directoryObjectVector[0].totalSize;

    /*
    RETHINK THIS WITH STRINGS KEEP TRACK OF ONLY A VECTER OF STRINGS 

    MAP <NAME, CONTAINS> DIRECTORY
    - Map<name, std::vector<std::string>> Directory

    MAP <NAME, SIZE> FILE
    - Map<name, int> File

    a
    - file.txt
    - B DIR

    std::map<std::string, std::vector<std::string>> directoryContents;

    Keep track of the directory with a string

    ROOT/a/s/d/f
    cd ..
    ROOT/a/s/d
    Now all you have to do is keep track of what is in each individual Dir
    */
    return 0;
}

std::vector<std::string> copyTextFileData(std::ifstream& file) {
    std::string line;
    std::vector<std::string> ret;
    while(std::getline(file, line)) {
       ret.push_back(line);
    }
    return ret;
}

std::pair<std::string, std::string> splitLine(std::string line) {
    std::string ret;
    std::string ret2;

    std::size_t pos = line.find("$ cd");

    if(pos != std::string::npos) {
        ret = "$ cd";
        ret2 = line.erase(0, 5);
        //std::cout << ret << " " << ret2 << "\n";
        return std::make_pair(ret, ret2);
    }

    pos = line.find("$ ls");
    if(pos != std::string::npos) {
        ret = "$";
        ret2 = line.erase(0, 2);
        //std::cout << ret << " " << ret2 << "\n";
        return std::make_pair(ret, ret2);
    }

    pos = line.find("dir ");
    if(pos != std::string::npos) {
        ret = "dir";
        ret2 = line.erase(0, 4);
        return std::make_pair(ret, ret2);
    }

    if(std::isdigit(line[0])) {
        for(int i = 0; i < line.length(); i++) {
            if(line[i] == ' ') {
                ret2 = line.erase(0, i+1);
                break;
            }
            ret += line[i];
            
        }
        return std::make_pair(ret, ret2);
    }
    return std::make_pair(ret, ret2);
}

void executeLine(std::string s, std::vector<directoryStruct>& pastDirectories, std::vector<directoryStruct>& directoryObjectVector,  std::string currentDirectory, std::string previousDirectory, int& previousIndex, int& n) {
    if(splitLine(s).second == "..") {
        pastDirectories.erase(pastDirectories.end());
        previousIndex--;
        previousDirectory = pastDirectories[previousIndex].name;

        n = findDirectoryIndex(previousDirectory, directoryObjectVector);
        currentDirectory = directoryObjectVector[n].name;
    }
    else if(splitLine(s).first == "$ cd") {
        n = findDirectoryIndex(splitLine(s).second, directoryObjectVector);
        previousDirectory = currentDirectory;
        currentDirectory = directoryObjectVector[n].name;
        pastDirectories.push_back(directoryObjectVector[n]);

        previousIndex = pastDirectories.size()-1;
    }
    else if(splitLine(s).first == "dir") parseDirectoryData(splitLine(s).second, directoryObjectVector, n);
    else if(splitLine(s).second == "ls") {
        // TODO
    }
    else {
        parseFileData(splitLine(s).first, splitLine(s).second, directoryObjectVector, n);
    }
}

void parseDirectoryData(std::string x, std::vector<directoryStruct>& directoryObjectVector, int& n) {
    directoryStruct directoryObject;
    directoryObject.name = x;

    directoryObjectVector[n].contains.push_back(directoryObject);
    directoryObjectVector.push_back(directoryObject);
}

void parseFileData(std::string x, std::string y, std::vector<directoryStruct>& directoryObjectVector, int& n) {
    fileStruct fileObject;
    fileObject.fileSize = std::stoi(x);
    fileObject.name = y;

    directoryObjectVector[n].contains.push_back(fileObject);
}
 
int findDirectoryIndex(std::string dirName, std::vector<directoryStruct>& directoryObjectVector) {
    if(dirName == "/") return 0;
    for(int i = 0; i < directoryObjectVector.size(); i++) {
        if(directoryObjectVector[i].name == dirName) return i;
    }

    return -1;
}

void printDirectories(int& i, std::vector<directoryStruct>& directoryObjectVector) {
    /* Make this a recrusive Method where it returns a int and the base case is when the directory no longer holds a directory object that we you can work you way up to the directory size*/
    for(int j = 0; j < directoryObjectVector[i].contains.size(); j++) {
        if(std::holds_alternative<directoryStruct>(directoryObjectVector[i].contains[j])) {
            std::cout << std::get<directoryStruct>(directoryObjectVector[i].contains[j]).name << " (dir)" << "\n";
        }
        else if(std::holds_alternative<fileStruct>(directoryObjectVector[i].contains[j])) {
            std::cout << std::get<fileStruct>(directoryObjectVector[i].contains[j]).name << " | Size: " << std::get<fileStruct>(directoryObjectVector[i].contains[j]).fileSize << "\n";
        }
        // TODO
    }
    if(i != 0) {
        std::cout << "--------------------- TOTAL SIZE: " << directoryObjectVector[i].totalSize << " ----------------------- \n";
    }
    else {
        std::cout << "--------------------------------------------------------- \n";
    }
}

long calculateDirectorySizeRecursively(directoryStruct& directoryObject, std::vector<directoryStruct>& directoryObjectVector, std::string prev) {
    int n = 0;
    int x = -1;

    // YOU NEED A UNIQUE ID FOR EACH DIRECTORY
    for (int i = 0; i < directoryObject.contains.size(); i++)  {
        if(std::holds_alternative<fileStruct>(directoryObject.contains[i])) {
            n = findDirectoryIndex(directoryObject.name, directoryObjectVector);
            directoryObjectVector[n].totalSize += std::get<fileStruct>(directoryObject.contains[i]).fileSize;
            
            //std::cout << "Currently in directory: " << directoryObjectVector[n].name << " | SIZE: " << directoryObjectVector[n].totalSize << "\n";
        }
        else if(std::holds_alternative<directoryStruct>(directoryObject.contains[i])) {
            n = findDirectoryIndex(std::get<directoryStruct>(directoryObject.contains[i]).name, directoryObjectVector);
            prev = directoryObjectVector[n].name;
            x = findDirectoryIndex(prev, directoryObjectVector);
            //std::cout << "N: " << n << "\n";
            directoryObjectVector[n].totalSize += calculateDirectorySizeRecursively(directoryObjectVector[n], directoryObjectVector, prev);
            //std::cout << "Now in directory: " << directoryObjectVector[n].name << " | SIZE: " << directoryObjectVector[n].totalSize << "\n";
	    }
        //std::cout << "--------------------------------------------------------- \n
    }
    if(directoryObject.name == "ROOT") {
        std::cout << "In ROOT FOLDER \n";
        for (int i = 0; i < directoryObject.contains.size(); i++) {
            if(std::holds_alternative<directoryStruct>(directoryObject.contains[i])) {
                int l = findDirectoryIndex(std::get<directoryStruct>(directoryObject.contains[i]).name, directoryObjectVector);
                directoryObjectVector[0].totalSize += directoryObjectVector[l].totalSize;
                std::cout << directoryObjectVector[i].totalSize << "\n"; 
            }
        }
    }
    //std::cout << "X: " << x << "\n";
    if(x != -1) return directoryObjectVector[x].totalSize;
    else {
        return 0;
    }
}