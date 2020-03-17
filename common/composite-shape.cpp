#include "composite-shape.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

stulov::CompositeShape::CompositeShape() :
  count_(0),
  shapesArray_(nullptr)
{}

stulov::CompositeShape::CompositeShape(const stulov::CompositeShape &shape) :
  count_(shape.count_),
  shapesArray_(std::make_unique<stulov::Shape::ptr_type[]>(shape.count_))
{
  for (size_t i = 0; i < count_; ++i)
  {
    shapesArray_[i] = shape.shapesArray_[i];
  }
}

stulov::CompositeShape::CompositeShape(stulov::CompositeShape &&shape) noexcept:
  count_(shape.count_),
  shapesArray_(std::move(shape.shapesArray_))
{}

stulov::CompositeShape::CompositeShape(stulov::Shape::ptr_type &shape) :
  count_(1),
  shapesArray_(std::make_unique<stulov::Shape::ptr_type[]>(1))
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("There is no shape to add");
  }
  shapesArray_[0] = shape;
}

stulov::CompositeShape& stulov::CompositeShape::operator =(const CompositeShape &rhs)
{
  if (this != &rhs)
  {
    count_ = rhs.count_;
    array_type tempArray(std::make_unique<stulov::Shape::ptr_type[]>(rhs.count_));
    for (size_t i = 0; i < count_; i++)
    {
      tempArray[i] = rhs.shapesArray_[i];
    }
    shapesArray_.swap(tempArray);
  }
  
  return *this;
}

stulov::CompositeShape& stulov::CompositeShape::operator =(CompositeShape &&rhs) noexcept
{
  if (this != &rhs)
  {
    count_ = rhs.count_;
    shapesArray_.swap(rhs.shapesArray_);
    rhs.shapesArray_.reset();
    rhs.count_ = 0;
  }
  
  return *this;
}

stulov::Shape::ptr_type stulov::CompositeShape::operator [](size_t index) const
{
  if (index >= count_)
  {
    throw std::out_of_range("Index is out of range");
  }
  return shapesArray_[index];
}

double stulov::CompositeShape::getArea() const
{
  double area = 0.0;
  for (size_t i = 0; i < count_; ++i)
  {
    area += shapesArray_[i]->getArea();
  }
  
  return area;
}

stulov::rectangle_t stulov::CompositeShape::getFrameRect() const
{
  if (count_ == 0)
  {
    return {0.0, 0.0, {0.0, 0.0}};
  }
  point_t maxPoint{shapesArray_[0]->getFrameRect().pos.x, shapesArray_[0]->getFrameRect().pos.y};
  point_t minPoint{shapesArray_[0]->getFrameRect().pos.x, shapesArray_[0]->getFrameRect().pos.y};
  
  for (size_t i = 1; i < count_; ++i)
  {
    rectangle_t frameRect = shapesArray_[i]->getFrameRect();
    
    double left = frameRect.pos.x - frameRect.width / 2;
    minPoint.x = std::min(minPoint.x, left);
    
    double right = frameRect.pos.x + frameRect.width / 2;
    maxPoint.x = std::max(maxPoint.x, right);
    
    double bottom = frameRect.pos.y - frameRect.height / 2;
    minPoint.y = std::min(minPoint.y, bottom);
    
    double top = frameRect.pos.y + frameRect.height / 2;
    maxPoint.y = std::max(maxPoint.y, top);
  }
  
  return rectangle_t{(maxPoint.x - minPoint.x), (maxPoint.y - minPoint.y),
      {(maxPoint.x + minPoint.x) / 2, (maxPoint.y + minPoint.y) / 2}};
}

void stulov::CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i < count_; ++i)
  {
    shapesArray_[i]->move(dx, dy);
  }
}

void stulov::CompositeShape::move(const stulov::point_t &center)
{
  const double dx = center.x - getFrameRect().pos.x;
  const double dy = center.y - getFrameRect().pos.y;
  for (size_t i = 0; i < count_; ++i)
  {
    shapesArray_[i]->move(dx, dy);
  }
}

void stulov::CompositeShape::printInformation() const
{
  stulov::rectangle_t temp_rect = getFrameRect();
  std::cout << "Area = " << getArea() << std::endl
            << "Frame rectangle width = " << temp_rect.width
            << ", height = " << temp_rect.height
            << ", and frameRectangle center (" << temp_rect.pos.x << ", "
            << temp_rect.pos.y << ") " << std::endl << std::endl;
}

void stulov::CompositeShape::scale(double scale)
{
  if (scale <= 0)
  {
    throw std::invalid_argument("Scale factor must be greater than zero");
  }
  
  const point_t pos = getFrameRect().pos;
  for (size_t i = 0; i < count_; ++i)
  {
    double dx = shapesArray_[i]->getFrameRect().pos.x - pos.x;
    double dy = shapesArray_[i]->getFrameRect().pos.y - pos.y;
    shapesArray_[i]->move((scale - 1) * dx, (scale - 1) * dy);
    shapesArray_[i]->scale(scale);
  }
}
void stulov::CompositeShape::rotate(double angle)
{
    rectangle_t frameRect = getFrameRect();
    
    double radAngle = M_PI * angle / 180;
    for (size_t i = 0; i < count_; i++)
    {
      point_t delta = shapesArray_[i]->getFrameRect().pos;
      delta.x -= frameRect.pos.x;
      delta.y -= frameRect.pos.y;
      shapesArray_[i]->rotate(angle);
      double dx = delta.x * (cos(radAngle) - 1) - delta.y * sin(radAngle);
      double dy = delta.y * (cos(radAngle) - 1) + delta.x * sin(radAngle);
      shapesArray_[i]->move(dx, dy);
    }
  }

void stulov::CompositeShape::add(const Shape::ptr_type &shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Pointer on shape is null");
  }
  
  array_type tempArray(std::make_unique<stulov::Shape::ptr_type[]>(count_ + 1));
  for (size_t i = 0; i < count_; ++i)
  {
    tempArray[i] = shapesArray_[i];
  }
  tempArray[count_] = shape;
  count_++;
  shapesArray_.swap(tempArray);
}

void stulov::CompositeShape::remove(size_t index)
{
  array_type tempArray(std::make_unique<stulov::Shape::ptr_type[]>(count_ - 1));
  
  for (size_t i = 0; i < index; ++i)
  {
    tempArray[i] = shapesArray_[i];
  }
  
  count_--;
  
  for (size_t i = index; i < count_; ++i)
  {
    tempArray[i] = shapesArray_[i + 1];
  }
  
  shapesArray_.swap(tempArray);
}

size_t stulov::CompositeShape::getCount() const
{
  return count_;
}
