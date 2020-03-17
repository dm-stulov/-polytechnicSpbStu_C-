#include <boost/test/auto_unit_test.hpp>

#include <memory>
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "polygon.hpp"
#include "triangle.hpp"
#include "partition.hpp"

const double DELTA = 1e-10;

BOOST_AUTO_TEST_SUITE(testPartition)
  
  BOOST_AUTO_TEST_CASE(intersectCorrectness)
  {
    stulov::Circle testCircle({5.0, 6.0}, 3.0);
    stulov::Rectangle testRectangle({5.0, 6.0}, 10.0, 4.5);
    stulov::Circle testCircle2 ({20.0, 10.0}, 1.0);
  
    BOOST_CHECK(stulov::intersect(testCircle.getFrameRect(),testRectangle.getFrameRect()));
    BOOST_CHECK(!(stulov::intersect(testCircle2.getFrameRect(),testRectangle.getFrameRect())));
    BOOST_CHECK(!(stulov::intersect(testCircle.getFrameRect(),testCircle2.getFrameRect())));
  }
  
  BOOST_AUTO_TEST_CASE(partitionCorrectness)
  {
    stulov::Shape::ptr_type circlePtr = std::make_shared<stulov::Circle>(stulov::point_t{20.0, 10.0}, 1.0);
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
    
    stulov::Matrix testMatrix = stulov::partition(compositeShape);
    
    const std::size_t correctRows = 3;
    const std::size_t correctColumns = 2;
    
    BOOST_CHECK_EQUAL(testMatrix.getRows(), correctRows);
    BOOST_CHECK_EQUAL(testMatrix.getColumns(), correctColumns);
    BOOST_CHECK(testMatrix[0][0] == circlePtr);
    BOOST_CHECK(testMatrix[0][1] == rectanglePtr);
    BOOST_CHECK(testMatrix[1][0] == trianglePtr);
    BOOST_CHECK(testMatrix[2][0] == polygonPtr);
  }

BOOST_AUTO_TEST_SUITE_END()
