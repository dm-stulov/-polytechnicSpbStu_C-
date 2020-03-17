#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <iostream>
#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t &pos) = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void printInfo() const = 0;
};

std::ostream& operator<<(std::ostream &out, const Shape &out_shape);

#endif
