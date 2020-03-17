#include "matrix.hpp"

stulov::Matrix::Matrix():
  rows_(0),
  columns_(0)
{}

stulov::Matrix::Matrix(const Matrix &other):
  shapesArray_(std::make_unique<Shape::ptr_type[]>(other.rows_ * other.columns_)),
  rows_(other.rows_),
  columns_(other.columns_)
{
  for (size_t i = 0; i < (rows_ * columns_); i++)
  {
    shapesArray_[i] = other.shapesArray_[i];
  }
}

stulov::Matrix::Matrix(Matrix &&other):
  shapesArray_(std::move(other.shapesArray_)),
  rows_(other.rows_),
  columns_(other.columns_)
{
  other.rows_ = 0;
  other.columns_ = 0;
}

stulov::Matrix& stulov::Matrix::operator =(const Matrix &rhs)
{
  if (&rhs != this)
  {
    Shape::array_type tempArray = std::make_unique<Shape::ptr_type[]>(rhs.rows_ * rhs.columns_);
    for (size_t i = 0; i < (rhs.rows_ * rhs.columns_); i++)
    {
      tempArray[i] = rhs.shapesArray_[i];
    }

    shapesArray_.swap(tempArray);
    rows_ = rhs.rows_;
    columns_ = rhs.columns_;
  }
  return *this;
}

stulov::Matrix& stulov::Matrix::operator =(Matrix &&rhs)
{
  if (&rhs != this)
  {
    rows_ = rhs.rows_;
    columns_ = rhs.columns_;
    shapesArray_ = std::move(rhs.shapesArray_);
  
    rhs.rows_ = 0;
    rhs.columns_ = 0;
  }
  return *this;
}

stulov::Shape::array_type stulov::Matrix::operator [](size_t layer) const
{
  if (rows_ <= layer)
  {
    throw std::out_of_range("Index is out of range");
  }

  Shape::array_type shapeArray = std::make_unique<Shape::ptr_type[]>(getLayerSize(layer));

  for (size_t i = 0; i < getLayerSize(layer); i++)
  {
    shapeArray[i] = shapesArray_[layer * columns_ + i];
  }

  return shapeArray;
}

bool stulov::Matrix::operator ==(const Matrix & rhs) const
{
  if ((rows_ != rhs.rows_) || (columns_ != rhs.columns_))
  {
    return false;
  }

  for (size_t i = 0; i < (rows_ * columns_); i++)
  {
    if (shapesArray_[i] != rhs.shapesArray_[i])
    {
        return false;
    }
  }

  return true;
}

bool stulov::Matrix::operator !=(const Matrix &rhs) const
{
  return !(*this == rhs);
}

size_t stulov::Matrix::getRows() const
{
  return rows_;
}

size_t stulov::Matrix::getColumns() const
{
  return columns_;
}

size_t stulov::Matrix::getLayerSize(size_t layer) const
{
  if (layer >= rows_)
  {
    return 0;
  }

  for (size_t i = 0; i < columns_; i++)
  {
    if (shapesArray_[layer * columns_ + i] == nullptr)
    {
      return i;
    }
  }

  return columns_;
}

void stulov::Matrix::add(const Shape::ptr_type &newShape, size_t layer)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Nothing to add");
  }

  const size_t tempRows = (layer >= rows_) ? (rows_ + 1) : rows_;
  const size_t tempColumns = (getLayerSize(layer) == columns_) ? (columns_ + 1) : columns_;
  const size_t column = (layer < rows_) ? getLayerSize(layer) : 0;

  Shape::array_type tempArray = std::make_unique<Shape::ptr_type[]>(tempRows * tempColumns);

  for (size_t i = 0; i < tempRows; i++)
  {
    for (size_t j = 0; j < tempColumns; j++)
    {
      if ((i == rows_) || (j == columns_))
      {
        tempArray[i * tempColumns + j] = nullptr;
      } else {
        tempArray[i * tempColumns + j] = shapesArray_[i * columns_ + j];
      }
    }
  }

  if (layer < rows_)
  {
    tempArray[layer * tempColumns + column] = newShape;
  } else {
    tempArray[rows_ * tempColumns + column] = newShape;
  }

  shapesArray_.swap(tempArray);
  rows_ = tempRows;
  columns_ = tempColumns;
}
