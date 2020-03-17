#include <iostream>
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "polygon.hpp"
#include "matrix.hpp"
#include "partition.hpp"

int main()
{
  stulov::Shape::ptr_type circlePtr = std::make_shared<stulov::Circle>(stulov::point_t{10.0, 12.0}, 5.0);

  stulov::Shape::ptr_type rectanglePtr = std::make_shared<stulov::Rectangle>(stulov::point_t{4.0, 1.0}, 3.0, 5.0);
  
  stulov::Shape::ptr_type trianglePtr = std::make_shared<stulov::Triangle>(stulov::point_t{3.0, 8.0},
  
    stulov::point_t{5.0, 2.0}, stulov::point_t{3.0, 3.0});
    
  stulov::point_t *points = new stulov::point_t[3]{{6.0, 12.0}, {16.0, 5.0}, {2.0, 2.0}};
  stulov::Shape::ptr_type polygonPtr = std::make_shared<stulov::Polygon>(3, points);
  delete[] points;
  
  stulov::CompositeShape compositeShape;
  
  compositeShape.add(circlePtr);
  compositeShape.add(rectanglePtr);
  compositeShape.add(trianglePtr);
  compositeShape.add(polygonPtr);
  
  std::cout << "Composite shape:\n";
  compositeShape.printInformation();
  
  compositeShape.move(4.0, 5.5);
  std::cout << "Move with (4, 5.5):\n";
  compositeShape.printInformation();
  
  compositeShape.move({2.0, 3.5});
  std::cout << "Move to (2, 3.5):\n";
  compositeShape.printInformation();
  
  compositeShape.scale(3.5);
  std::cout << "Scale by 3.5:\n";
  compositeShape.printInformation();
  
  size_t count = compositeShape.getCount();
  std::cout << "Count shapes:" << count << std::endl;
  std::cout << "Get shape and print information:\n";
  compositeShape[1]->printInformation();
  
  std::cout << "Rotate 45 degrees:\n";
  compositeShape.rotate(45);
  compositeShape.printInformation();
  
  std::cout << "\n\nMatrix\n";
  stulov::Matrix matrix = stulov::partition(compositeShape);
  
  std::cout << "layers: " << matrix.getRows() << " columns:" << matrix.getColumns() << "\n";
  
  for (size_t i = 0; i < matrix.getRows(); i++)
  {
    for (size_t j = 0; j < matrix.getLayerSize(i); j++)
    {
      std::cout << "This is layer N" << i << ": " << "figure N" << j << " ,area:" << matrix[i][j]->getArea() << "\n";
    }
  }
  
  std::cout << "\n\nDelete circle and rectangle:\n";
  compositeShape.remove(1);
  compositeShape.remove(2);
  compositeShape.printInformation();
  
  return 0;
}
