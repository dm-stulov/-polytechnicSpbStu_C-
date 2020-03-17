#include <iostream>
#include <list>

const int MAX = 20;

void task2()
{
  std::list<int> list;
  int data;

  while (std::cin >> data, !std::cin.eof())
  {
    if ((data < 1) || (data > MAX))
    {
      throw std::invalid_argument("Data must be between 1 and 20");
    }

    if(list.size() >= MAX)
    {
      throw std::out_of_range("Max size of list is 20");
    }

    list.push_back(data);
  }

  if((!std::cin.eof()) && (std::cin.fail()))
  {
    throw std::runtime_error("Could not read from in");
  }

  std::list<int>::iterator begin = list.begin();
  std::list<int>::iterator end = list.end();

  while (begin != end)
  {
    std::cout << *begin << " ";

    if (std::next(begin) == end)
    {
      break;
    }

    begin++;
    end--;
    std::cout << *end << " ";
  }
  std::cout << "\n";
}
