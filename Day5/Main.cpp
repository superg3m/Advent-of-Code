#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctype.h>
#include <vector>
#include <map>
#include <sstream>


std::pair<std::vector<std::string>, std::vector<std::string>> readTextFile(std::ifstream& textFile);
std::map<int, std::string> parseFirstHalf(std::vector<std::string>& firstVector);

void solution(std::map<int, std::string>& m, std::vector<std::string>& v);


int main() {
    std::ifstream textFile;
    std::pair<std::vector<std::string>, std::vector<std::string>> vectorPair;
    textFile.open("Day5.txt");

    vectorPair = readTextFile(textFile);

    std::map<int, std::string> hMap;
    hMap = parseFirstHalf(vectorPair.first);

    solution(hMap, vectorPair.second);
}

std::pair<std::vector<std::string>, std::vector<std::string>> readTextFile(std::ifstream& textFile) {
    bool blankSpace = false;

    std::vector<std::string> firstHalf;
    std::vector<std::string> secondHalf;

    std::string line;
    while(std::getline(textFile, line)) {
        if(line.empty()) {
            blankSpace = true;
            continue;
        }

        if(!blankSpace) {
            firstHalf.push_back(line);
        }
        else if(blankSpace) {
            secondHalf.push_back(line);
        }
        
    }
    return std::make_pair(firstHalf, secondHalf);
}


std::map<int, std::string> parseFirstHalf(std::vector<std::string>& firstVector) {

    std::vector<std::vector<char>> temp;
    bool digit = false;

    std::map<int, std::string> hashMap;
    
    //doubleVector[row][column]
    
    std::pair<int, std::string> valuePair;

    for(int i = 0; i < firstVector.size(); i++) {
        for(int j = 0; j < firstVector[i].length(); j++) {
            temp.push_back(std::vector<char>());
            temp[i].push_back(firstVector[i][j]);
        }
    }

    for(int i = 0; i < firstVector[0].length(); i++) {
        for(int j = 0; j < firstVector.size(); j++) {
            if(std::isdigit(temp[j][i]) && !digit) {
                j = 0;
                digit = true;
            }

            if(digit && std::isdigit(temp[j][i])) {
                valuePair.first = temp[j][i] - 48;
            }
            else if(digit && temp[j][i] != ' ') {
                valuePair.second += temp[j][i];
            }
        }
        hashMap.insert(valuePair);
        valuePair.second.clear();
        digit = false;
    }
    hashMap.erase(0);
    return hashMap;
}

void solution(std::map<int, std::string>& m, std::vector<std::string>& v) {

    std::map<int, std::string> tempMap = m;
    std::map<int, std::string> tempMap2 = m;


    std::vector<int> cache;
    int foundNumber;
    int amount;
    int from;
    int to;

    std::stringstream ss;
    std::string temp;


    for(std::string str : v) {
        ss = std::stringstream(str);
        while(!ss.eof()) {
            ss >> temp;
            if(std::stringstream(temp) >> foundNumber) {
                cache.push_back(foundNumber);
            }
            temp = "";
        }
        cache.clear();
        amount = cache[0];
        from = cache[1];
        to = cache[2];

        std::string intersection = tempMap[from].substr(0, amount);
        std::string intersection2 = tempMap2[from].substr(0, amount);

        std::string moreCache = "";

        //std::cout << "Before | " << intersection << "\n";
        for(int i = intersection.length()-1; i >= 0; i--) {
            moreCache += intersection[i];
        }
        //std::cout << "After | " << moreCache << "\n";

        tempMap[from].erase(0, amount);
        tempMap[to].insert(0, moreCache);

        tempMap2[from].erase(0, amount);
        tempMap2[to].insert(0, intersection2);
    }

    std::string result;
    for(int i = 0; i < tempMap.size(); i++) {
        result += tempMap[i][0];
    }

    std::cout << "Part1: " << result << "\n";

    result.clear();

    for(int i = 0; i < tempMap2.size(); i++) {
        result += tempMap2[i][0];
    }

    std::cout << "Part2: " << result << "\n";
}