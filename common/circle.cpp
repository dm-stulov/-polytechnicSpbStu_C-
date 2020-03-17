#define _USE_MATH_DEFINES
#include "circle.hpp"
#include <iostream>
#include <cmath>

stulov::Circle::Circle(const point_t &position, double radius) :
  position_(position),
  radius_(radius)
{
  if (radius_ <= 0.0)
  {
    throw std::invalid_argument("Radius must be greater than zero!");
  }
}

double stulov::Circle::getArea() const
{
  return (M_PI * pow(radius_, 2));
}

stulov::rectangle_t stulov::Circle::getFrameRect() const
{
  return rectangle_t{radius_ * 2, radius_ * 2, position_};
}

void stulov::Circle::move(double dx, double dy)
{
  position_.x += dx;
  position_.y += dy;
}

void stulov::Circle::move(const point_t &position)
{
  position_ = position;
}

void stulov::Circle::printInformation() const
{
  rectangle_t info = getFrameRect();
  std::cout << "Area = " << getArea() << "\n";
  std::cout << "Central coordinates of frame: (" << info.pos.x << ", " << info.pos.y << ")\n";
  std::cout << "Frame width = " << info.width <<", frame height = " << info.height << "\n\n";
}

void stulov::Circle::scale(double scale)
{
  if (scale <= 0)
  {
    throw std::invalid_argument("Scale factor must be greater than zero!");
  }
  radius_ *= scale;
}
