#include <iostream>
#include <cstring>

void task1();
void task2();

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "ARGC: Wrong number of arguments";
      return 1;
    }

    char *ptr = nullptr;
    int task = std::strtol(argv[1], &ptr, 10);

    if (*ptr)
    {
      std::cerr << "ARGV: Wrong task number";
      return 1;
    }

    switch (task)
    {
      case 1:
      {
        task1();
        break;
      }

      case 2:
      {
        task2();
        break;
      }

      default:
      {
        std::cerr << "ARGV: Wrong task number";
        return 1;
      }
    }
  }
  catch(std::exception &e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }

  return 0;
}
