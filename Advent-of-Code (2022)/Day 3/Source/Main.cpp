#include <iostream> 
#include <vector> 
#include <fstream> 
#include <algorithm> 
#include <cstring>
#include <string>
#include <set> 


std::vector<std::string> readFile(std::ifstream& file);
std::pair<std::string, std::string> splitData(std::string& line);
void part1(std::vector<std::pair<std::string, std::string>>& dataPair);
void calculatePriority(std::set<char>& uniqueCharacterSet);
char commonChars(std::vector<std::string>& words);
void part2(std::vector<char> commonVector);

int main() {
    std::ifstream myFile;
    std::vector<std::string> fileData;
    std::vector<std::pair<std::string, std::string>> dataPair;
    
    myFile.open("../Day3.txt");
    if(!myFile.is_open()) std::cerr << "ERORR with file \n"; 
    else {
        fileData = readFile(myFile); 
    }
    
    for(std::string currentLine : fileData) {
        dataPair.push_back(splitData(currentLine));
    } 
    part1(dataPair);
    std::vector<char> commonElements;
    std::vector<std::string> elfGroup;
    
    for(int i = 0; i < fileData.size()+1; i++) {
        if((i+1) % 3 == 0) {
            elfGroup.clear();
            elfGroup.push_back(fileData[i-2]);
            elfGroup.push_back(fileData[i-1]);
            elfGroup.push_back(fileData[i]);
            commonElements.push_back(commonChars(elfGroup));
        }
    }
    part2(commonElements);
}

std::vector<std::string> readFile(std::ifstream& file) {
    std::string  s;
    std::vector<std::string> ret;
    while(std::getline(file, s)) {
        ret.push_back(s);
    }
    return ret;
}

std::pair<std::string, std::string> splitData(std::string& line) {
    int size = 0;
    std::string firstHalf;
    std::string secondHalf;
    size = line.length()/2;
    firstHalf = line.substr(0, size); 
    secondHalf = line.substr(size); 
    return std::make_pair(firstHalf, secondHalf);
}

char commonChars(std::vector<std::string>& words) {
    char c;
    std::string string_intersectionONE;
    std::string string_intersectionTWO;
    std::string string_intersectionTHREE;

    std::string firstElement = words[0];
    std::string secondElement = words[1];
    std::string thirdElement = words[2];

    std::sort(firstElement.begin(), firstElement.end());
    std::sort(secondElement.begin(), secondElement.end());
    std::sort(thirdElement.begin(), thirdElement.end());

    std::set_intersection(firstElement.begin(), firstElement.end(), secondElement.begin(), secondElement.end(), std::back_inserter(string_intersectionONE));

    std::set_intersection(firstElement.begin(), firstElement.end(), thirdElement.begin(), thirdElement.end(), std::back_inserter(string_intersectionTWO));
    
    std::set_intersection(string_intersectionONE.begin(), string_intersectionONE.end(), string_intersectionTWO.begin(), string_intersectionTWO.end(), std::back_inserter(string_intersectionTHREE));
 
    // declaring character array
    char char_array[100];
 
    // copying the contents of the
    // string to char array
    strcpy(char_array, string_intersectionTHREE.c_str());

    c = char_array[0];

    return c;
}

void part1(std::vector<std::pair<std::string, std::string>>& dataPair) {
    std::set<char> uniqueCharacterSet;
    std::string first;
    std::string second;
    int priority = 0;
    for(int i = 0; i < dataPair.size(); i++) {
        first = dataPair[i].first;
        second = dataPair[i].second;
        for(int j = 0; j < first.length(); j++) {
            for(int k = 0; k < second.length(); k++) {
                if(first[j] == second[k]) uniqueCharacterSet.insert(first[j]);
                
            }
        }
        for(char c : uniqueCharacterSet) {
            priority += std::islower(c) ? c - 96 : c - 38;
        }
        uniqueCharacterSet.clear();
    }
    std::cout << "PART1 Priority: " << priority << "\n";
}

void part2(std::vector<char> commonVector) {
    int priority = 0;
    for(char c : commonVector) {
            priority += std::islower(c) ? c - 96 : c - 38;
    }
    std::cout << "PART2 Priority: " << priority << "\n";
}