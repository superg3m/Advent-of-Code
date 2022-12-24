#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

std::string parseTextFileData(std::ifstream& file);
void part1(std::string s);
void part2(std::string s);
int checkForOccurences(std::vector<char>& vec);

int main() {
    std::ifstream textFile;
    textFile.open("Day6.txt");

    std::string fileData;
    if(!textFile.is_open()) {
        std::cerr << "The file is not open \n";
        return -1;
    }
    else {
        fileData = parseTextFileData(textFile);
    }
    part1(fileData);
    part2(fileData);

    return 0;
}

std::string parseTextFileData(std::ifstream& file) {
    std::string ret;
    std::string line;

    while(std::getline(file, line)) {
        ret += line;
    }
    return ret;
}

void part1(std::string s) {
    std::vector<char> cache;
    bool done = false;

    for(int i = 0; i < s.length(); i++) {
        cache.clear();
        for(int j = i; j <= i+3; j++) {
            cache.push_back(s[j]);
        }
        // Greater than zero means it has been found
        if(checkForOccurences(cache) == 0) {
            std::cout << "Part1: " << i+4 << "\n";
            done = true;
        }
        if(done) break;
    }
}

void part2(std::string s) {
    std::vector<char> cache;
    bool done = false;

    for(int i = 0; i < s.length(); i++) {
        cache.clear();
        for(int j = i; j <= i+13; j++) {
            cache.push_back(s[j]);
        }
        // Greater than zero means it has been found
        if(checkForOccurences(cache) == 0) {
            std::cout << "Part2: " << i+14 << "\n";
            done = true;
        }
        if(done) break;
    }
}

int checkForOccurences(std::vector<char>& vec) {
    int occurences = 0;
    for(char c : vec) {
        for(int i = 0; i < vec.size(); i++) {
            if(c == vec[i]) occurences++;
        }
        if(occurences > 1) break;
        occurences = 0;
    }
    return occurences;
}

