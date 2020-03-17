#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "polygon.hpp"

int main()
{
  Rectangle shape_1({2, 2}, 8, 9);
  Circle shape_2({2, 3}, 2);
  Triangle shape_3({1, 2}, {2, 2}, {2, 1});

  point_t points[] = {{2, 1}, {2, 5}, {4, 7}, {8, 7}, {8, 1}};
  Polygon shape_4(points, 5);

  Shape *rect = &shape_1;
  Shape *cir = &shape_2;
  Shape *tri = &shape_3;
  Shape *pol = &shape_4;

  point_t point = {50, 40};
  double dx = 5, dy = -5;

  rect->move(point);
  rect->move(dx, dy);

  cir->move(point);
  cir->move(dx, dy);

  tri->move(point);
  tri->move(dx, dy);

  pol->move(point);
  pol->move(dx, dy);

  Shape *shapes[] = {rect, cir, tri, pol};

  for (const Shape *shape : shapes)
  {
    rectangle_t frame_rect = shape->getFrameRect();

    std::cout << *shape << std::endl
        << "  area: " << shape->getArea() << std::endl
        << "  framing rectangle:" << std::endl
        << "    x: " << frame_rect.pos.x << std::endl
        << "    y: " << frame_rect.pos.y << std::endl
        << "    width: " << frame_rect.width << std::endl
        << "    height: " << frame_rect.height << std::endl
        << std::endl;
  }

  return 0;
};
