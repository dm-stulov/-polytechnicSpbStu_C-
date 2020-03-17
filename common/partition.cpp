#include "partition.hpp"

bool stulov::intersect(const rectangle_t &lhs, const rectangle_t &rhs)
{
  const point_t leftBottom = {lhs.pos.x - lhs.width / 2, lhs.pos.y - lhs.height / 2};
  const point_t leftTop = {lhs.pos.x + lhs.width / 2, lhs.pos.y + lhs.height / 2};
  const point_t rightBottom = {rhs.pos.x - rhs.width / 2, rhs.pos.y - rhs.height / 2};
  const point_t rightTop = {rhs.pos.x + rhs.width / 2, rhs.pos.y + rhs.height / 2};

  return ((leftBottom.x < rightTop.x && leftBottom.y < rightTop.y) &&
      (rightBottom.x < leftTop.x && rightBottom.y < leftTop.y));
}

stulov::Matrix stulov::partition(const stulov::CompositeShape &composite)
{
  Matrix tmpMatrix;
  const size_t size = composite.getCount();

  for (size_t i = 0; i < size; i++)
  {
    size_t layer = 0;
    for (size_t j = 0; j < tmpMatrix.getRows(); j++)
    {
      bool intersected = false;
      for (size_t k = 0; k < tmpMatrix.getLayerSize(j); k++)
      {
        if (intersect(composite[i]->getFrameRect(), tmpMatrix[j][k]->getFrameRect()))
        {
          layer++;
          intersected = true;
          break;
        }
      }
      if (!intersected)
        {
        break;
      }
    }
    tmpMatrix.add(composite[i], layer);
  }

  return tmpMatrix;
}
