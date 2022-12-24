#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

struct directoryStruct {
    std::string name;
    int totalSize;
    int number_of_children;
    std::vector<std::string> contains;
};

struct fileStruct {
    std::string name;
    int size;
};

// METHODS
std::vector<std::string> copyTextFileData(std::ifstream& file);
std::pair<std::string, std::string> splitLine(std::string& line);

void executeCommand();
void parseDirectoryData();
void parseFileData() ;

int main() {
    std::ifstream textFile;
    std::vector<std::string> fileData;

    // GO BACK UNTIL char at index i is equal to / and then reverse the directory letters: ROOT/got/hide -> ROOT/got unless the reversed string == ROOT
    std::string currentDirectory = "ROOT/";

    textFile.open("Day7.txt");
    if(!textFile.is_open()) {
        std::cerr << "Err with the file \n";
    }
    else {
        fileData = copyTextFileData(textFile);
    }

    for(std::string s : fileData) {
        //std::cout << splitLine(s).first << "\n"; 
        //std::cout << splitLine(s).second << "\n"; 
        if(splitLine(s).first == "$") executeCommand();
        else if(splitLine(s).first == "dir") parseDirectoryData();
        else {
            parseFileData();
        }
    }
    bool firstPrint = true;

    std::vector<std::string> temp = {"bsl", "fg", "gol", "rel"};
    std::vector<directoryStruct> directoryVector;
    directoryStruct dirObject;
    dirObject.name = "a";
    dirObject.contains = temp;
    directoryVector.push_back(dirObject);
    
    for(int i = 0; i < directoryVector.size(); i++) {
        std::cout << "Name: " << directoryVector[i].name << "\n";
        std::cout << "contains: {";
        for(std::string s : directoryVector[i].contains) {
            if(firstPrint) {
                firstPrint = false;
                std::cout << s;
            }
            else {
                std::cout << ", ";
                std::cout << s;
            }
            
        }
        std::cout << "}";
    }
    //std::map<std::string, std::vector<std::string>> directoryContents;
    /*
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

std::pair<std::string, std::string> splitLine(std::string& line) {
    std::string ret;
    std::string ret2;
    bool secondHalf = false;
    bool first = false;
    for(int i = 0; i < line.length(); i++) {
        // This checks if the character is empty
        if(line[i] == ' ') {
            secondHalf = true;
            if(!first) {
                first = true;
                continue;
            }
            //
        }
        if(!secondHalf) {
            ret += line[i];
        }
        else {
            ret2 += line[i];
        }
        
    }
    return std::make_pair(ret, ret2);
}

void executeCommand() {

}

void parseDirectoryData() {
    
}

void parseFileData() {

}

