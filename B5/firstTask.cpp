#include "firstTask.hpp"

void firstTask()
{
  std::set<std::string> set = readData();

  for (const auto &it : set) {
    std::cout << it << "\n";
  }
};

std::set<std::string> readData()
{
  std::string currentLine;
  std::set<std::string> set;

  while (std::getline(std::cin, currentLine)){
    std::istringstream iss(currentLine);
    std::string word;
    while (iss >> word){
      set.insert(word);
    }
  }
  return set;
}
