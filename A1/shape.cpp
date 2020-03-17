#include "shape.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream &out, const Shape &out_shape)
{
  out_shape.printInfo();
  return out;
}
