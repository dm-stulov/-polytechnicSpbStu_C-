#include <iostream>
#include <fstream>
#include <stdexcept>
#include <memory>
#include <vector>

const int InitialSize = 1024;

void secondTask(char* filename)
{
  using charArray = std::unique_ptr<char[], decltype(&free)>;
  std::ifstream inputFile(filename);

  if (!inputFile)
  {
    throw std::ios_base::failure("Failed to open file.");
  }

  int size = InitialSize;
  charArray arr(static_cast<char*>(malloc(size)), &free);

  int i = 0;

  while (inputFile)
  {
    inputFile.read(&arr[i], InitialSize);
    i += inputFile.gcount();

    if (inputFile.gcount() == InitialSize)
    {
      size += InitialSize;
      charArray temp(static_cast<char*>(realloc(arr.get(), size)), &free);

      if (temp)
      {
        arr.release();
        std::swap(arr, temp);
      }
      else
      {
        throw std::runtime_error("Failed to reallocate.");
      }
    }
  }

  inputFile.close();

  if (inputFile.is_open())
  {
    throw std::ios_base::failure("Failed to close file.");
  }

  std::vector<char> vector(&arr[0], &arr[i]);

  for (const auto& it: vector)
  {
    std::cout << it;
  }
}
