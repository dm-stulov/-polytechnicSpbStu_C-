#include "triangle.hpp"
#include <iostream>
#include <cmath>

stulov::Triangle::Triangle(const point_t &pointA, const point_t &pointB, const point_t &pointC) :
  pointA_(pointA),
  pointB_(pointB),
  pointC_(pointC),
  center_{(pointA_.x + pointB_.x + pointC_.x) / 3, (pointA_.y + pointB_.y + pointC_.y) / 3}
{
  if (getArea() <= 0.0)
  {
    throw std::invalid_argument("This is a degenerate triangle");
  }
}

double stulov::Triangle::getArea() const
{
  double square = fabs(((pointA_.x - pointC_.x) * (pointB_.y - pointC_.y)
      - (pointA_.y - pointC_.y) * (pointB_.x - pointC_.x)) / 2);

  return square;
}

stulov::rectangle_t stulov::Triangle::getFrameRect() const
{
  point_t minPoint{std::min(pointA_.x, std::min(pointB_.x, pointC_.x)),
      std::min(pointA_.y, std::min(pointB_.y, pointC_.y))};

  point_t maxPoint{std::max(pointA_.x, std::max(pointB_.x, pointC_.x)),
      std::max(pointA_.y, std::max(pointB_.y, pointC_.y))};

  double width = maxPoint.x - minPoint.x;
  double height = maxPoint.y - minPoint.y;

  point_t frameCenter{minPoint.x + width / 2, minPoint.y + height / 2};

  return rectangle_t{width, height, frameCenter};
}

void stulov::Triangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;

  pointA_.x += dx;
  pointB_.x += dx;
  pointC_.x += dx;

  pointA_.y += dy;
  pointB_.y += dy;
  pointC_.y += dy;
}

void stulov::Triangle::move(const point_t &param)
{
  double dx = param.x - center_.x;
  double dy = param.y - center_.y;
  
  move(dx, dy);
}

void stulov::Triangle::printInformation() const
{
  rectangle_t info = getFrameRect();
  
  std::cout << "Center: (" << center_.x << ", " << center_.y << ")\n";
  std::cout << "Area = " << getArea() << "\n";
  std::cout << "Central coordinates of frame: (" << info.pos.x << ", " << info.pos.y << ")\n";
  std::cout << "Frame width = " << info.width <<", frame height = " << info.height << "\n\n";
}

void stulov::Triangle::scale(double scale)
{
  if (scale <= 0)
  {
    throw std::invalid_argument("Scale factor must be greater than zero!");
  }
  pointA_ = getNewVertex(pointA_, scale);
  pointB_ = getNewVertex(pointB_, scale);
  pointC_ = getNewVertex(pointC_, scale);
}

void stulov::Triangle::rotate(double angle)
{
  pointA_ = rotate(pointA_, angle);
  pointB_ = rotate(pointB_, angle);
  pointC_ = rotate(pointC_, angle);
}

stulov::point_t stulov::Triangle::getCenter() const
{
  return center_;
}

stulov::point_t stulov::Triangle::getNewVertex(const point_t &point, double scale) const
{
  const double lengthX = center_.x - point.x;
  const double lengthY = center_.y - point.y;
  point_t newPoint{point.x - lengthX * (scale - 1), point.y - lengthY * (scale - 1)};
  return newPoint;
}

stulov::point_t stulov::Triangle::rotate(const point_t &point, double angle) const
{
  angle *=  M_PI / 180;
  return point_t{center_.x + (point.x - center_.x) * cos(angle) - (point.y - center_.y) * sin(angle),
      center_.y + (point.y - center_.y) * cos(angle) + (point.x - center_.x) * sin(angle)};
}
