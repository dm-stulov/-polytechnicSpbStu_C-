#include <cstring>
#include <iostream>
#include <sstream>
#include "priority-queue-implement.hpp"

void task1()
{
  PriorityQueue<std::string> queue;
  std::string string;

  while (std::getline(std::cin, string))
  {
    if (std::cin.fail())
    {
      throw std::runtime_error("Could not read from in");
    }
    std::stringstream stringStream(string);

    std::string command;
    std::string data;
    std::string priority;

    stringStream >> command;

    if (command == "add")
    {
      stringStream >> priority;
      stringStream >> data;

      if (!stringStream.eof())
      {
        std::getline(stringStream, string);
        data += string;
      }


      if ((!stringStream.eof()) || (data.empty()))
      {
        std::cout << "<INVALID COMMAND>\n";
        break;
      }


      if (priority == "low")
      {
        queue.add(PriorityQueue<std::string>::Priority::LOW, data);
      }

      else if (priority == "normal")
      {
        queue.add(PriorityQueue<std::string>::Priority::NORMAL, data);
      }

      else if (priority == "high")
      {
        queue.add(PriorityQueue<std::string>::Priority::HIGH, data);
      }

      else
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else if (command == "get")
    {
      if (queue.isEmpty())
      {
        std::cout << "<EMPTY>\n";
      }
      else
      {
        std::cout << queue.get() << "\n";
      }
    }
    else if (command == "accelerate")
    {
      queue.accelerate();
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
