#include <iostream>
#include <iomanip>
#include <iterator>
#include <algorithm>

#include "func.hpp"


int main() {
  try {
    std::istream_iterator<long long int> end;
    std::istream_iterator<long long int> start(std::cin);

    func my_funct = for_each(start, end, func());

    if (!std::cin.eof() && (std::cin.fail() || std::cin.bad())) {
      std::cout << "incorrect input";
      return 1;
    }

    if (my_funct.returnCount() == 0) {
      std::cout << "No Data\n";
    } else {
      std::cout << "Max: " << my_funct.returnMin() << '\n';
      std::cout << "Min: " << my_funct.returnMax() << '\n';
      std::cout.flags(std::ios::fixed);
      std::cout << "Mean: " << std::setprecision(1) << my_funct.returnMean() << '\n';
      std::cout << "Positive: " << my_funct.returnPositive() << '\n';
      std::cout << "Negative: " << my_funct.returnNegative() << '\n';
      std::cout << "Odd Sum: " << my_funct.returnOddSum() << '\n';
      std::cout << "Even Sum: " << my_funct.returnEvenSum() << '\n';
      std::cout << "First/Last Equal: " << (my_funct.comparatorFirstLast() ? "yes" : "no") << '\n';
    }
  }
  catch (...) {
    std::cerr << "error\n";
    return 1;
  }
  return 0;
}
