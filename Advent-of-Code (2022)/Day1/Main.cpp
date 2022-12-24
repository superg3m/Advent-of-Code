#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

std::vector<std::string> readFile(std::ifstream& file);
std::vector<int> calculateElfData(std::vector<std::string>& data);
void sum(std::vector<int>& data);

int main() {
    std::ifstream myFile;
    std::vector<std::string> fileData;
    std::vector<int> elfData;
    myFile.open("day1.txt");
    if(!myFile.is_open()) {
        std::cerr << "Error with the file \n";
        exit(0);
    }
    else {
        fileData = readFile(myFile);
        myFile.close();
    }
    elfData = calculateElfData(fileData);
    std::sort(elfData.begin(), elfData.end());
    sum(elfData);
}

std::vector<std::string> readFile(std::ifstream& file) {
    std::string s;
    std::vector<std::string> ret;
    while(std::getline(file, s)) {
        ret.push_back(s);
    }
    return ret;
}

std::vector<int> calculateElfData(std::vector<std::string>& data) {
    int sum = 0;
    std::vector<int> ret;
    for(std::string s : data) {
        if(s == "") {
            ret.push_back(sum);
            sum = 0;
        }
        else {
            sum += std::stoi(s);
        }
    }
    return ret;
}

void sum(std::vector<int>& data) {
    int sum = 0;
    for(int i = data.size()-1; i > data.size()-4; i--) {
        sum += data[i];
        
    }
    std::cout << "Part 1: " << data[data.size()-1] << "\n";
    std::cout << "Part 2: " << sum << "\n";
}