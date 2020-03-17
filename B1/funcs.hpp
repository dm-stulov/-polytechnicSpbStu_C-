#ifndef FUNCS_HPP_INCLUDED
#define FUNCS_HPP_INCLUDED

#include <iostream>
#include <memory>
#include <ctime>

bool isReverse(char* direction);

template <typename ContainerType, typename AccessType>
void sort(ContainerType &container, int size, bool reverse)
{
  if (size == 0)
  {
    return;
  }

  auto access = std::shared_ptr<AccessType>();
  
  for (int i = 0; i < size - 1; i++)
  {
    for (int j = 0; j < size - i - 1; j++)
    {
      auto element_1 = *access->getElement(container, j);
      auto element_2 = *access->getElement(container, j + 1);

      if (reverse ? element_1 < element_2 : element_1 > element_2)
      {
        std::swap(*access->getElement(container, j),
          *access->getElement(container, j + 1));
      }
    }
  }
}

template <typename ContainerType>
void print(const ContainerType &container, bool space_insert = true)
{
  if (container.empty())
  {
    return;
  }

  for (auto it = container.begin(); it != container.end();++it)
  {
    std::cout << *it;

    if (space_insert)
    {
      std::cout << " ";
    }
  }
}

#endif
