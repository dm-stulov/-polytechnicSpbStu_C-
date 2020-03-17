#include "polygon.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

Polygon::Polygon(const Polygon &polygon) :
  points_(new point_t[polygon.size_]),
  size_(polygon.size_)
{
  for (int i = 0; i < size_; i++)
  {
    points_[i] = polygon.points_[i];
  }
}

Polygon::Polygon(Polygon &&polygon) :
  points_(polygon.points_),
  size_(polygon.size_)
{
  polygon.points_ = nullptr;
  polygon.size_ = 0;
}

Polygon::Polygon(const point_t *points, int size) :
  points_(new point_t[size]),
  size_(size)
{
  if (size < 3)
  {
    delete [] points_;
    throw std::invalid_argument("Count of points must be >= 3");
  }

  if (points == nullptr)
  {
    delete [] points_;
    throw std::invalid_argument("Pointer to points mustn't be nullptr");
  }

  for (int i = 0; i < size_; i++)
  {
    points_[i] = points[i];
  }

  if (!isConvex())
  {
    delete [] points_;
    throw std::invalid_argument("Polygon must be convex");
  }

  if (getArea() == 0)
  {
    delete [] points_;
    throw std::invalid_argument("Area mustn't be = 0");
  }
}

Polygon::~Polygon()
{
  delete [] points_;
}

Polygon &Polygon::operator=(const Polygon &polygon)
{
  if (this == &polygon)
  {
    return *this;
  }

  delete [] points_;
  points_ = new point_t[polygon.size_];

  for (int i = 0; i < size_; i++)
  {
    points_[i] = polygon.points_[i];
  }

  size_ = polygon.size_;

  for (int i = 0; i < size_; i++)
  {
    points_[i] = polygon.points_[i];
  }

  return *this;
}

Polygon &Polygon::operator=(Polygon &&polygon)
{
  if (this == &polygon)
  {
    return *this;
  }

  delete [] points_;

  points_ = polygon.points_;
  polygon.points_ = nullptr;

  size_ = polygon.size_;
  polygon.size_ = 0;

  return *this;
}

double Polygon::getArea() const
{
  double area = (points_[size_ - 1].x + points_[0].x) * (points_[size_ - 1].y - points_[0].y);

  for (int i = 0; i < size_ - 1; i++)
  {
    area += (points_[i].x + points_[i + 1].x) * (points_[i].y - points_[i + 1].y);
  }

  return fabs(area) / 2;
}

rectangle_t Polygon::getFrameRect() const
{
  point_t top_left = getCenter();
  point_t bottom_right = top_left;

  for (int i = 0; i < size_; i++)
  {
    top_left.x = std::min(points_[i].x, top_left.x);
    top_left.y = std::max(points_[i].y, top_left.y);
    bottom_right.x = std::max(points_[i].x, bottom_right.x);
    bottom_right.y = std::min(points_[i].y, bottom_right.y);
  }

  return {{(top_left.x + bottom_right.x) / 2, (top_left.y + bottom_right.y) / 2},
      bottom_right.x - top_left.x, top_left.y - bottom_right.y};
}

void Polygon::move(const point_t &pos)
{
  const point_t center = getCenter();
  move(pos.x - center.x, pos.y - center.y);
}

void Polygon::move(double dx, double dy)
{
  for (int i = 0; i < size_; i++)
  {
    points_[i].x += dx;
    points_[i].y += dy;
  }
}

void Polygon::printInfo() const
{
  const point_t center = getCenter();

  std::cout << "polygon" << std::endl
      << "  pos: {" << center.x << "; " << center.y << "}" << std::endl;

  for (int i = 0; i < size_; i++)
  {
    std::cout << "  points[" << i << "]: {" << points_[i].x << "; " << points_[i].y << "}" << std::endl;
  }
}

point_t Polygon::getCenter() const
{
  point_t center = {0, 0};

  for (int i = 0; i < size_; i++)
  {
    center.x += points_[i].x / size_;
    center.y += points_[i].y / size_;
  }

  return center;
}

bool Polygon::isConvex() const
{
  bool got_negative = false;
  bool got_positive = false;

  for (int i = 0; i < size_; i++)
  {
    const int j = (i + 1) % size_;
    const int k = (j + 1) % size_;

    double cross_product = (points_[j].x - points_[i].x) * (points_[k].y - points_[j].y)
        - (points_[j].y - points_[i].y) * (points_[k].x - points_[j].x);

    if (cross_product < 0)
    {
      got_negative = true;
    }
    else if (cross_product > 0)
    {
      got_positive = true;
    }

    if (got_negative && got_positive)
    {
      return false;
    }
  }

  return true;
}
