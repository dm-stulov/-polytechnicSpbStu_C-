#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "shape.hpp"

namespace stulov {

  class Matrix {
  public:
    Matrix();
    Matrix(const Matrix &);
    Matrix(Matrix &&);
    ~Matrix() = default;

    Matrix & operator =(const Matrix &);
    Matrix & operator =(Matrix &&);

    Shape::array_type operator [](size_t) const;
    bool operator ==(const Matrix &) const;
    bool operator !=(const Matrix &) const;

    size_t getRows() const;
    size_t getColumns() const;
    size_t getLayerSize(size_t) const;

    void add(const Shape::ptr_type &, size_t);

  private:
    Shape::array_type shapesArray_;
    size_t rows_;
    size_t columns_;
  };

}

#endif
