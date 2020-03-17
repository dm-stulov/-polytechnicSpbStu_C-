#include <iostream>
#include <string>

#include "firstTask.hpp"
#include "secondTask.hpp"

int main(int argc, char *argv[]) {
  if (argc != 2){
    std::cerr << "Wrong number of parameters;";
    return 1;
  }

  std::string taskNumber(argv[1]);
  try {
    if (taskNumber == "1"){
      firstTask();
    } else if (taskNumber == "2"){
      secondTask();
    } else {
      std::cerr << "Wrong task;";
      return 1;
    }
  } catch (const std::exception & e){
    std::cerr << e.what();
    return 1;
  }

  return 0;
}
