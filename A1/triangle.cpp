#include "triangle.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

Triangle::Triangle(const point_t &pos_a, const point_t &pos_b, const point_t &pos_c) :
  points_({pos_a, pos_b, pos_c})
{
  if (getArea() == 0)
  {
    throw std::invalid_argument("Area mustn't be = 0");
  }
}

double Triangle::getArea() const
{
  return fabs(((points_[0].x - points_[2].x) * (points_[1].y - points_[2].y)
      - (points_[1].x - points_[2].x) * (points_[0].y - points_[2].y))) / 2;
}

rectangle_t Triangle::getFrameRect() const
{
  point_t top_left = getCenter();
  point_t bottom_right = top_left;

  for (const point_t point : points_)
  {
    top_left.x = std::min(point.x, top_left.x);
    top_left.y = std::max(point.y, top_left.y);
    bottom_right.x = std::max(point.x, bottom_right.x);
    bottom_right.y = std::min(point.y, bottom_right.y);
  }

  return {{(top_left.x + bottom_right.x) / 2, (top_left.y + bottom_right.y) / 2},
      bottom_right.x - top_left.x, top_left.y - bottom_right.y};
}

void Triangle::move(const point_t &pos)
{
  const point_t center = getCenter();
  move(pos.x - center.x, pos.y - center.y);
}

void Triangle::move(double dx, double dy)
{
  for (point_t &point : points_)
  {
    point.x += dx;
    point.y += dy;
  }
}

void Triangle::printInfo() const
{
  const point_t center = getCenter();

  std::cout << "triangle" << std::endl
      << "  pos: {" << center.x << "; " << center.y << "}" << std::endl
      << "  A: {" << points_[0].x << "; " << points_[0].y << "}" << std::endl
      << "  B: {" << points_[1].x << "; " << points_[1].y << "}" << std::endl
      << "  C: {" << points_[2].x << "; " << points_[2].y << "}";
}

point_t Triangle::getCenter() const
{
  return {(points_[0].x + points_[1].x + points_[2].x) / 3,
      (points_[0].y + points_[1].y + points_[2].y) / 3};
}
