#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "polygon.hpp"
#include "composite-shape.hpp"

int main()
{
  stulov::Shape::ptr_type circlePtr = std::make_shared<stulov::Circle>(stulov::point_t{1, 2}, 4);
  stulov::Shape::ptr_type rectanglePtr = std::make_shared<stulov::Rectangle>(stulov::point_t{1.0, 2.0}, 4.0, 5.0);
  stulov::Shape::ptr_type trianglePtr = std::make_shared<stulov::Triangle>(stulov::point_t{4.0, 10.0},
    
    stulov::point_t{15.0, 6.0}, stulov::point_t{1.0, 1.0});
  
  stulov::point_t *points = new stulov::point_t[3]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}};
  stulov::Shape::ptr_type polygonPtr = std::make_shared<stulov::Polygon>(3, points);
  delete[] points;

  stulov::CompositeShape compositeShape;

  compositeShape.add(circlePtr);
  compositeShape.add(rectanglePtr);
  compositeShape.add(trianglePtr);
  compositeShape.add(polygonPtr);
  
  std::cout << "Composite shape:\n";
  compositeShape.printInformation();
  
  compositeShape.move(5.0, 6.5);
  std::cout << "Move with (5, 6.5):\n";
  compositeShape.printInformation();
  
  compositeShape.move({1.0, 2.5});
  std::cout << "Move to (1, 2.5):\n";
  compositeShape.printInformation();
  
  compositeShape.scale(3.5);
  std::cout << "Scale by 3.5:\n";
  compositeShape.printInformation();
  
  std::cout << "Remove circle and rectangle:\n";
  compositeShape.remove(1);
  compositeShape.remove(2);
  compositeShape.printInformation();
  
  size_t count = compositeShape.getCount();
  std::cout << "Count of shapes:" << count << std::endl;
  std::cout << "Get shape and print information:\n";
  compositeShape[1]->printInformation();
  return 0;
}
