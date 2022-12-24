#include <iostream> 
#include <vector> 
#include <fstream> 
#include <algorithm> 
#include <cstring>
#include <sstream>
#include <string>
#include <set> 


std::vector<std::string> readFile(std::ifstream& file);

std::pair<std::string, std::string> splitDataOnce(std::string& line);

std::pair<std::string, std::string> splitDataTwice(std::pair<std::string, std::string>& set, int x);

void solution(std::vector<std::pair<std::string, std::string>>& dataPair);

std::vector<int> split(std::string target);


int main() {
    std::ifstream myFile;
    std::vector<std::string> fileData;
    std::vector<std::pair<std::string, std::string>> dataPair;
    std::vector<std::pair<std::string, std::string>> assignmentPairOne;
    int lineNumber = 0;
    
    myFile.open("Day4.txt");
    if(!myFile.is_open()) std::cerr << "ERORR with file \n"; 
    else {
        fileData = readFile(myFile); 
    }
    for(std::string currentLine : fileData) {
        dataPair.push_back(splitDataOnce(currentLine));
    }   
    for(std::pair<std::string, std::string> currentAssignementPair : dataPair) {
        lineNumber++;
        assignmentPairOne.push_back(splitDataTwice(currentAssignementPair, lineNumber));
    }   
    lineNumber = 0;

    solution(assignmentPairOne);
}

std::vector<std::string> readFile(std::ifstream& file) {
    std::string  s;
    std::vector<std::string> ret;
    while(std::getline(file, s)) {
        ret.push_back(s);
    }
    return ret;
}

std::pair<std::string, std::string> splitDataOnce(std::string& line) {
    std::string firstSet;
    std::string secondSet;

    for(int i = 0; i < line.length()-1; i++) {
        if(line.at(i) == ',') {
            firstSet = line.substr(0, i);
            secondSet = line.substr(i+1, line.length());
        }
    }
    return std::make_pair(firstSet, secondSet);
}

std::pair<std::string, std::string> splitDataTwice(std::pair<std::string, std::string>& set, int x) {
    std::string firstNumber;
    std::string secondNumber;

    int lineNumber = x;

    std::string retOne;
    std::string retTwo;
    std::string cache;

    for(int i = 0; i < set.first.length()-1; i++) {
        if(set.first.at(i) == '-') {
            firstNumber = set.first.substr(0, i);
            secondNumber = set.first.substr(i+1, set.first.length());
            break;
        }
    }

    for (int i = std::stoi(firstNumber); i <= std::stoi(secondNumber); i++)
    {
        cache += std::to_string(i) + " ";
    }

    retOne = cache;
    cache.clear();

    for(int i = 0; i < set.second.length()-1; i++) {
        if(set.second.at(i) == '-') {
            firstNumber = set.second.substr(0, i);
            secondNumber = set.second.substr(i+1, set.second.length());
            break;
        }
    }
    for (int i = std::stoi(firstNumber); i <= std::stoi(secondNumber); i++)
    {
        cache += std::to_string(i) + " ";
    }
    retTwo = cache;
    cache.clear();
    return std::make_pair(retOne, retTwo);
}

void solution(std::vector<std::pair<std::string, std::string>>& dataPair) {

    int occurrences = 0;
    int overlapAtALL = 0;
    std::string firstElement;
    std::string secondElement;

    std::vector<int> firstElementVector;
    std::vector<int> secondElementVector;

    std::vector<int> intersectingVector;

    for(auto pair : dataPair) {
        intersectingVector.clear();
        firstElement = pair.first;
        secondElement = pair.second;

        
        firstElementVector = split(firstElement);
        secondElementVector = split(secondElement);

        std::set_intersection(firstElementVector.begin(), firstElementVector.end(), secondElementVector.begin(), secondElementVector.end(), std::back_inserter(intersectingVector));
        std::cout << "Intersecting: {";
        for(int x : intersectingVector) {
            std::cout << x << " ";
        }
        std::cout << "} \n";
        
        if(!intersectingVector.empty()) overlapAtALL++;

        firstElementVector.erase(std::set_difference(firstElementVector.begin(), firstElementVector.end(), intersectingVector.begin(), intersectingVector.end(), firstElementVector.begin()), firstElementVector.end());
        secondElementVector.erase(std::set_difference(secondElementVector.begin(), secondElementVector.end(), intersectingVector.begin(), intersectingVector.end(), secondElementVector.begin()), secondElementVector.end());
        // If any of the element vectors are empty then there is a complete overlap somewhere because I check for all intersecting points and then erase them from the original
        if(firstElementVector.empty() && secondElementVector.empty()) {
            occurrences++;
        }
        else if(secondElementVector.empty()) {
            occurrences++;
        }
        else if(firstElementVector.empty()) {
            occurrences++;
        }
    }
    std::cout << "PART1: " << occurrences << "\n";
    std::cout << "PART2: " << overlapAtALL << "\n";
}

std::vector<int> split(std::string target) {
    std::vector<int> v;
    std::string cache;
    if (target.empty()) return v;
    for(int i = 0; i < target.length(); i++) {
        if(target.at(i) == ' ') {
            v.push_back(std::stoi(cache));
            cache.clear();
        }
        else { 
            cache += target.at(i);
        }
    }
    return v;
}