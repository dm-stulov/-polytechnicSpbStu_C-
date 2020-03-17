#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace stulov
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t &, double);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double, double) override;
    void move(const point_t &) override;
    void printInformation() const override;
    void scale(double) override;
    void rotate(double) override
    {}

  private:
    point_t position_;
    double radius_;
  };
}

#endif
