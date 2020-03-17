#include "line.hpp"

std::istream& operator>>(std::istream &in, Line &line) {
  while(std::getline(in, line)) {
    if(line.empty()) {
      continue;
    }
    if(std::find_if(line.begin(), line.end(),[]
        (char c) {
      return !std::isspace(c, std::locale());
    }) != line.end()){
      break;
    }
  }
  return in;
}
