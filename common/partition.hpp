#ifndef PARTITION_HPP
#define PARTITION_HPP

#include "matrix.hpp"
#include "composite-shape.hpp"

namespace stulov
{
  bool intersect(const rectangle_t &lhs, const rectangle_t &rhs);
  stulov::Matrix partition(const stulov::CompositeShape &composite);

}

#endif
