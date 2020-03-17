#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <cstdlib>
#include <memory>
#include "shape.hpp"

namespace stulov
{
  class Polygon : public Shape
  {
  public:
    Polygon(const Polygon &);
    Polygon(Polygon &&) noexcept;
    Polygon(size_t, point_t *);
    ~Polygon() override;

    Polygon &operator =(const Polygon &);
    Polygon &operator =(Polygon &&) noexcept;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &) override;
    void move(double, double) override;
    void printInformation() const override;
    void scale(double) override;
    void rotate(double) override;
  
    point_t getCenter() const;
    
  private:
    size_t number_;
    point_t *pointsArray_;
    
    double getLineForConvexCheck(size_t, size_t, size_t) const;
    bool isConvex() const;
  };
}
#endif
