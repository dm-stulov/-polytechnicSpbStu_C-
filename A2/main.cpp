#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "polygon.hpp"

void shapeModification(stulov::Shape &shape, double dx, double dy, const stulov::point_t &dt, double scale)
{
  shape.printInformation();

  shape.move(dx, dy);
  std::cout << "move(dx, dy):\n";
  shape.printInformation();

  shape.move(dt);
  std::cout << "move(dt):\n";
  shape.printInformation();

  shape.scale(scale);
  std::cout << "Scale:\n";
  shape.printInformation();
}

int main()
{
  stulov::Rectangle objRectangle({5.0, 6.0}, 7.0, 1.0);
  stulov::Shape *shape = &objRectangle;

  std::cout << "\nRectangle:\n";
  shapeModification(*shape, 5.1, 6.2, {0.0, 3.0}, 2.0);

  stulov::Circle objCircle({1.0, 5.0}, 6.0);
  shape = &objCircle;

  std::cout << "\nCircle:\n";
  shapeModification(*shape, 1.0, 2.0, {7.8, -9.0}, 1.5);

  stulov::Triangle objTriangle({4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0});
  shape = &objTriangle;

  std::cout << "\nTriangle:\n";
  shapeModification(*shape, 5.4, 7.6, {1.0, 3.0}, 2.0);

  stulov::point_t *points = new stulov::point_t[3]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}};
  stulov::Polygon objPolygon{3, points};
  delete[] points;
  shape = &objPolygon;

  std::cout << "\nPolygon:\n";
  shapeModification(*shape, 1.02, 2.1, {6.0, 4.001}, 1.5);

  stulov::point_t *points1 = new stulov::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
  stulov::Polygon objPolygon2(4, points1);
  delete[] points1;
  shape = &objPolygon2;

  std::cout << "\npolygon with 4 sides:\n";
  shapeModification(*shape, 1.0, 9.0, {3.2, 4.2}, 6.0);

  return 0;
}

