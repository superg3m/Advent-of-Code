#include <algorithm>
#include <unordered_set>
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

std::vector<int> readTextFile(std::ifstream &file);
void findTarget(std::vector<int> &fileData);
void findSum(std::vector<int> &fileData);

int main() {
  std::ifstream myFile;
  std::vector<int> fileData;
  std::string s = "";

  myFile.open("file.txt");

  if (!myFile.is_open()) {
    exit(1);
  } else {
    fileData = readTextFile(myFile);
    myFile.close();
  }
  
  findSum(fileData);
  findTarget(fileData);
}

std::vector<int> readTextFile(std::ifstream &file) {
  std::vector<int> cache;
  std::string s;
  while (std::getline(file, s)) {
    cache.push_back(std::stoi(s));
  }
  return cache;
}
void findSum(std::vector<int> &fileData) {
  int currentFrequency = 0;
  for (int n : fileData) {
    currentFrequency += n;
  }
  std::cout << "Part #1: " << currentFrequency << "\n";
}

void findTarget(std::vector<int> &fileData) {
  int currentFrequency = 0;
  std::unordered_set<int> myList;
  bool found = false;
  auto begin = std::chrono::high_resolution_clock::now();
  myList.insert(currentFrequency);
  while (!found) {
    for (int n : fileData) {
      currentFrequency += n;
      found = myList.find(currentFrequency) != myList.end();
      myList.insert(currentFrequency);
      if (found) {
        std::cout << "The Second Appearing #: " << std::to_string(currentFrequency) + "\n";
        break;
      }
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

  std::cout << "Time: " << elapsed.count() * 1e-9 << "\n";
  std::cout << "Done reading file \n";
}

/*
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <unordered_set>

std::fstream read_input_from_file(const std::string& file)
{
    auto input = std::fstream(file, std::ios_base::in);

    if (!input.is_open())
    {
        std::cerr << "Could not open " << file << '\n';
        throw std::runtime_error("failed to read file: " + file);
    }

    return input;
}

std::vector<int> read_input()
{
    std::fstream input = read_input_from_file("file.txt");

    std::string line;
    std::vector<int> data;

    while (getline(input, line))
    {
        data.push_back(std::stoi(line));
    }
    return data;
}

void _year_2018_day_1_part_1()
{
    const std::vector<int> input = read_input();

    int frequency = 0;

    for (auto val : input)
    {
        frequency += val;
    }

    std::cout << "2018 day 1 part 1 answer: " << frequency << '\n';
}

void _year_2018_day_1_part_2()
{
    auto start = std::chrono::high_resolution_clock::now();

    const std::vector<int> input = read_input();

    int frequency = 0;

    int index = 0;

    std::unordered_set<int> mapping;
    mapping.insert(frequency);
    while (true)
    {
        frequency += input[index];

        index = ++index % input.size();

        if (mapping.count(frequency) > 0)
        {
            std::cout << "2018 day 1 part 2 answer: " << frequency << '\n';
            break;
        }
        mapping.insert(frequency);
    }

    auto stop = std::chrono::high_resolution_clock::now();

    std::chrono::nanoseconds time = stop - start;
    const auto ms{ std::chrono::duration_cast<std::chrono::milliseconds>(time) };

    std::cout << "time: " << ms.count()/1000.00 << "s\n";
}

int main()
{
    _year_2018_day_1_part_1();
    _year_2018_day_1_part_2();
}
*/

/*
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ifstream myFile;
  std::vector<int> my_list;
  std::vector<int> fileData;
  bool found;
  int currentFrequency = 0;
  std::string s = "";

  myFile.open("file.txt");

  if (!myFile.is_open()) {
    exit(1);
  }
  while (getline(myFile, s)) {
    fileData.push_back(std::stoi(s));
  }
  myFile.close();
  my_list.push_back(currentFrequency);
  while(!found) {
    for(auto n : fileData) {
      currentFrequency += n;
      found = std::find(my_list.begin(), my_list.end(), currentFrequency) != my_list.end();
      my_list.push_back(currentFrequency);
      if (found) {
        std::cout << "The Second Appearing #: " << std::to_string(currentFrequency) + "\n";
        break;
      }
    }
    if(found) break;
  }
  std::cout << "Done reading file";
}
*/