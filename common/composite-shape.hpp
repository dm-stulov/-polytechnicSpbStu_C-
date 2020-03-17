#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace stulov
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape &);
    CompositeShape(CompositeShape &&) noexcept;
    CompositeShape(Shape::ptr_type &);
    ~CompositeShape() override = default;

    CompositeShape& operator =(const CompositeShape &);
    CompositeShape& operator =(CompositeShape &&) noexcept;
    Shape::ptr_type operator [](size_t) const;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double, double) override;
    void move(const point_t &) override;
    void scale(double) override;
    void printInformation() const override;
    void rotate(double) override;
    
    void add(const Shape::ptr_type &);
    void remove(size_t);

    size_t getCount() const;

  private:
    size_t count_;
    Shape::array_type shapesArray_;
  };
}

#endif
