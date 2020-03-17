#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>
#include "base-types.hpp"

namespace stulov
{
  class Shape
  {
  public:
    using ptr_type = std::shared_ptr<Shape>;
    using array_type = std::unique_ptr<ptr_type[]>;

    virtual ~Shape() = default;

    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(double, double) = 0;
    virtual void move(const point_t &) = 0;
    virtual void printInformation() const = 0;
    virtual void scale(double) = 0;
    virtual void rotate(double) = 0;
  
  };
}

#endif
