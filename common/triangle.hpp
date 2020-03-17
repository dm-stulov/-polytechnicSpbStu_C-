#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

namespace stulov
{
  class Triangle : public Shape
  {
  public:
    Triangle(const point_t &, const point_t &, const point_t &);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move (const point_t &) override;
    void move (double,  double) override;
    void printInformation() const override;
    void scale(double) override;
    void rotate(double) override;
  
    point_t getCenter() const;
    point_t getNewVertex(const point_t &, double) const;
    point_t rotate(const point_t &, double) const;
  private:
    point_t pointA_;
    point_t pointB_;
    point_t pointC_;
    point_t center_;
  };
}

#endif
