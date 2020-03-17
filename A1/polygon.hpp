#ifndef POLYGON_HPP
#define POLYGON_HPP
#include "shape.hpp"

class Polygon : public Shape
{
public:
  Polygon(const Polygon &);
  Polygon(Polygon &&);
  Polygon(const point_t *points, int size);
  ~Polygon();
  Polygon & operator=(const Polygon &);
  Polygon & operator=(Polygon &&);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &pos) override;
  void move(double dx, double dy) override;
  void printInfo() const override;

private:
  point_t *points_;
  int size_;
  point_t getCenter() const;
  bool isConvex() const;
};

#endif
