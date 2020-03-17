#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>

Rectangle::Rectangle(const point_t &pos, double height, double width) :
  pos_(pos),
  height_(height),
  width_(width)
{
  if (width <= 0)
  {
    throw std::invalid_argument("Width must be > 0");
  }

  if (height <= 0)
  {
    throw std::invalid_argument("Height must be > 0");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {pos_, width_, height_};
}

void Rectangle::move(const point_t &pos)
{
  pos_ = pos;
}

void Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Rectangle::printInfo() const
{
  std::cout << "rectangle" << std::endl
      << "  pos: {" << pos_.x << "; " << pos_.y << "}" << std::endl
      << "  height: " << height_ << std::endl
      << "  width: " << width_;
}
