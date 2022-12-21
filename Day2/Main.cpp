#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

// Win 6, draw 3, lose 0
// Computer: [ A: rock, B: paper, C: scissors ]

std::vector<std::string> readFile(std::ifstream& file);
std::vector<std::pair<char, char>> splitData(std::vector<std::string>& fileData);
std::pair<int, int> calculatePoints(char& computer, char& player);
std::vector<std::pair<int, int>> playGamePART1(std::vector<std::pair<char, char>>& vectorPair);
std::vector<std::pair<int, int>> playGamePART2(std::vector<std::pair<char, char>>& vectorPair);
void calculateAnswer(std::vector<std::pair<int, int>>& totalPoints);
char playerCharChange(char& computer, char& player);

int main() {
    std::ifstream myFile;

    std::vector<std::string> fileData;

    std::vector<std::pair<char, char>> vectorPair;

    std::vector<std::pair<int, int>> totalPoints;

    myFile.open("Day2.txt");
    if(!myFile.is_open()) std::cerr << "There is a problem with the file \n";

    fileData = readFile(myFile);
    vectorPair = splitData(fileData);

    // PART 1
    std::cout << "Part 1:" << "\n";
    totalPoints = playGamePART1(vectorPair);
    calculateAnswer(totalPoints);
    
    

    // PART 2
    std::cout << "*******************\n";
    std::cout << "Part 2:" << "\n";
    totalPoints = playGamePART2(vectorPair);\
    calculateAnswer(totalPoints);
}

std::vector<std::string> readFile(std::ifstream& file) {
    std::string s;
    std::vector<std::string> ret;
    while(std::getline(file, s)) {
        ret.push_back(s);
    }
    return ret;
}

std::vector<std::pair<char, char>> splitData(std::vector<std::string>& fileData) {
    std::vector<std::pair<char, char>> ret;
    for (int i = 0; i < fileData.size(); i++)
    {
        for(int j = 0; j < fileData[i].length(); j++) {
            if(fileData[i].at(j) == ' ') {
                ret.push_back(std::make_pair(fileData[i].at(j - 1), fileData[i].at(j + 1)));
            }
        }
    }
    return ret;
}

std::vector<std::pair<int, int>> playGamePART1(std::vector<std::pair<char, char>>& vectorPair) {
    char computer;
    char player;
    std::pair<int, int> pointPair;
    std::vector<std::pair<int, int>> totalPointPair;
    for(auto pair : vectorPair) {
        computer = pair.first;
        player = pair.second;
        pointPair = calculatePoints(computer, player);
        totalPointPair.push_back(pointPair);
    } 
    return totalPointPair;
}

std::vector<std::pair<int, int>> playGamePART2(std::vector<std::pair<char, char>>& vectorPair) {
    char computer;
    char player;
    std::pair<int, int> pointPair;
    std::vector<std::pair<int, int>> totalPointPair;
    for(auto pair : vectorPair) {
        computer = pair.first;
        player = pair.second;
        player = playerCharChange(computer, player);
        pointPair = calculatePoints(computer, player);
        totalPointPair.push_back(pointPair);
    } 
    return totalPointPair;
}

char playerCharChange(char& computer, char& player) {
    std::vector<char> choiceList = {'X' , 'Y', 'Z'};
    int index = 0;
    switch(player) {
        case 'X':
            // ===================== Computer Win =====================
            while(true) {
                if((computer == 'A' && player == 'Z' || computer == 'B' && player == 'X' || computer == 'C' && player == 'Y')) break;
                index = (++index % choiceList.size());
                player = choiceList[index];
            }
            break;

        case 'Y':
            // ===================== Tie =====================
            while(true) {
                if(computer == 'A' && player == 'X' || computer == 'B' && player == 'Y' || computer == 'C' && player == 'Z') break;
                index = (++index % choiceList.size());
                player = choiceList[index];
            }
            break;

        case 'Z':
            // ===================== Player Win =====================
            while(true) {
                if(computer == 'C' && player == 'X' || computer == 'A' && player == 'Y' || computer == 'B' && player == 'Z') break;
                index = (++index % choiceList.size());
                player = choiceList[index];
            }
            break;
    }
    return player;
}

std::pair<int, int> calculatePoints(char& computer, char& player) {
    int computerPoints = 0;
    int playerPoints = 0;
    switch (computer) {
        case 'A':
            computerPoints+=1;
            break;

        case 'B':
            computerPoints+=2;
            break;

        case 'C':
            computerPoints+=3;
            break;
    }

    switch(player) {
        case 'X':
            playerPoints+=1;
            break;

        case 'Y':
            playerPoints+=2;
            break;

        case 'Z':
            playerPoints+=3;
            break;
    }

    // Computer wins
    if(computer == 'A' && player == 'Z' || computer == 'B' && player == 'X' || computer == 'C' && player == 'Y') computerPoints += 6;

    // Player wins
    else if(computer == 'C' && player == 'X' || computer == 'A' && player == 'Y' || computer == 'B' && player == 'Z') playerPoints += 6;

    // Tie 
    else if(computer == 'A' && player == 'X' || computer == 'B' && player == 'Y' || computer == 'C' && player == 'Z') {
        playerPoints += 3;
        computerPoints += 3;
    }
    return std::make_pair(computerPoints, playerPoints);
}

void calculateAnswer(std::vector<std::pair<int, int>>& totalPoints) {

    int computerSum = 0;
    int playerSum = 0;

    for(auto p : totalPoints) {
        computerSum += p.first;
        playerSum += p.second;
    }
    
    std::cout << "Computer: " << computerSum << "\n";
    std::cout << "Player: " << playerSum << "\n";
}
