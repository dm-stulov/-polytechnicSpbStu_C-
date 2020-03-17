#include "polygon.hpp"
#include <iostream>
#include <cmath>

stulov::Polygon::Polygon(const Polygon &shape) :
  number_(shape.number_),
  pointsArray_(new point_t[number_])
{
  for (size_t i = 0; i < number_; i++)
  {
    pointsArray_[i] = shape.pointsArray_[i];
  }
}

stulov::Polygon::Polygon(Polygon &&shape) noexcept :
  number_(shape.number_),
  pointsArray_(shape.pointsArray_)
{
  shape.number_ = 0;
  shape.pointsArray_ = nullptr;
}

stulov::Polygon::Polygon(size_t number, point_t *vertex) :
  number_(number),
  pointsArray_(new point_t[number_])
{
  if (number_ < 3)
  {
    delete[] pointsArray_;
    throw std::invalid_argument("Polygon must have 3 or more vertices");
  }
  if (vertex == nullptr)
  {
    delete[] pointsArray_;
    throw std::invalid_argument("Nothing to add");
  }
  
  for (size_t i = 0; i < number_; i++)
  {
    pointsArray_[i] = vertex[i];
  }
  
  if (getArea() <= 0.0)
  {
    delete[] pointsArray_;
    throw std::invalid_argument("This is a degenerate polygon");
  }
  if (!isConvex())
  {
    delete[] pointsArray_;
    throw std::invalid_argument("This polygon is nonconvex");
  }
}

stulov::Polygon::~Polygon()
{
  delete[] pointsArray_;
}

stulov::Polygon & stulov::Polygon::operator =(const Polygon &rhs)
{
  if (this != &rhs)
  {
    number_ = rhs.number_;
    delete[] pointsArray_;

    pointsArray_ = new point_t[number_];
    for (size_t i = 0; i < number_; i++)
    {
      pointsArray_[i] = rhs.pointsArray_[i];
    }
  }
  return *this;
}

stulov::Polygon & stulov::Polygon::operator =(Polygon &&rhs) noexcept
{
  if (this != &rhs)
  {
    number_ = rhs.number_;
    rhs.number_ = 0;
    delete[] pointsArray_;
  
    pointsArray_ = rhs.pointsArray_;
    rhs.pointsArray_ = nullptr;
  }
  return *this;
}

double stulov::Polygon::getArea()const
{
  double area = 0.0;
  
  for (size_t i = 0; i < (number_ - 1); i++)
  {
    area += ((pointsArray_[i].x + pointsArray_[i + 1].x) * (pointsArray_[i].y - pointsArray_[i + 1].y));
  }
  area += ((pointsArray_[number_ - 1].x + pointsArray_[0].x) * (pointsArray_[number_ - 1].y - pointsArray_[0].y));
  
  return fabs(area / 2);
}

stulov::rectangle_t stulov::Polygon::getFrameRect() const
{
  point_t minPoint{pointsArray_[0].x, pointsArray_[0].y};
  point_t maxPoint{pointsArray_[0].x, pointsArray_[0].y};
  
  for (size_t i = 1; i < number_; i++)
  {
    minPoint.x = std::min(minPoint.x, pointsArray_[i].x);
    minPoint.y = std::min(minPoint.y, pointsArray_[i].y);
  
    maxPoint.x = std::max(maxPoint.x, pointsArray_[i].x);
    maxPoint.y = std::max(maxPoint.y, pointsArray_[i].y);
  }
  
  return rectangle_t{(maxPoint.x - minPoint.x), (maxPoint.y - minPoint.y),
      {(minPoint.x + maxPoint.x) / 2, (minPoint.y + maxPoint.y) / 2}};
}

void stulov::Polygon::move(double dx, double dy)
{
  for (size_t i = 0; i < number_; i++)
  {
    pointsArray_[i].x += dx;
    pointsArray_[i].y += dy;
  }
}

void stulov::Polygon::move(const point_t &pos)
{
  const point_t center = getCenter();
  move(pos.x - center.x, pos.y - center.y);
}

void stulov::Polygon::printInformation() const
{
  const rectangle_t frameInfo = getFrameRect();
  const point_t center = getCenter();
  std::cout << "Center: (" << center.x << ", " << center.y << ")\n";
  std::cout << "Area = " << getArea() << "\n";
  std::cout << "Central coordinates of frame: (" << frameInfo.pos.x << ", " << frameInfo.pos.y << ")\n";
  std::cout << "Frame width = " << frameInfo.width <<", frame height = " << frameInfo.height << "\n\n";
}

void stulov::Polygon::scale(double scale)
{
  if (scale <= 0.0)
  {
    throw std::invalid_argument("Scale factor must be greater than zero!");
  }
  const point_t center = getCenter();
  for (size_t i = 0; i < number_; i++)
  {
    pointsArray_[i] = {pointsArray_[i].x - (center.x - pointsArray_[i].x) * (scale - 1),
        pointsArray_[i].y - (center.y - pointsArray_[i].y) * (scale - 1)};
  }
}

void stulov::Polygon::rotate(double angle)
{
  const point_t center = getCenter();
  angle = angle * M_PI / 180;
  for (size_t i = 0; i < number_; i++)
  {
    const point_t tempPoint = pointsArray_[i];
    pointsArray_[i].x = center.x + (tempPoint.x - center.x) * cos(angle) -
        (tempPoint.y - center.y) * sin(angle);
    pointsArray_[i].y = center.y + (tempPoint.x - center.x) * sin(angle) +
        (tempPoint.y - center.y) * cos(angle);
  }
}

stulov::point_t stulov::Polygon::getCenter() const
{
  point_t center{0.0, 0.0};
  
  for (size_t i = 0; i < number_; i++)
  {
    center.x += pointsArray_[i].x;
    center.y += pointsArray_[i].y;
  }
  
  return point_t{center.x / number_, center.y / number_};
}

double stulov::Polygon::getLineForConvexCheck(size_t num1, size_t num2, size_t num3) const
{
  double line = (pointsArray_[num3].y - pointsArray_[num2].y) * (pointsArray_[num1].x - pointsArray_[num2].x)
      - (pointsArray_[num3].x - pointsArray_[num2].x) * (pointsArray_[num1].y - pointsArray_[num2].y);
  
  return line;
}

bool stulov::Polygon::isConvex() const
{
  for (size_t i = 0; i < (number_ - 1); i++)
  {
    double line1 = getLineForConvexCheck(0, i, (i + 1));
    double line2 = 0.0;
    for (size_t j = 1; j < number_; j++)
    {
      line2 = getLineForConvexCheck(j, i, (i + 1));
      if (line2 * line1 >= 0)
      {
        line1 = line2;
      }
      else
      {
        return false;
      }
    }
  }
  return true;
}
