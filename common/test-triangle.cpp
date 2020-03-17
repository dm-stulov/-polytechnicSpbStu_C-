#include <iostream>
#include <boost/test/auto_unit_test.hpp>
#include "triangle.hpp"

#define EPSILON 1e-10

BOOST_AUTO_TEST_SUITE(shapeTriangle)
  
  BOOST_AUTO_TEST_CASE(TriangleAfterMove)
  {
    
    stulov::Triangle testTriangle({6.9, 7.0}, {1.2, 0.3}, {3.1, 1.6});
    const stulov::rectangle_t rectBeforeMove = testTriangle.getFrameRect();
    const double areaBeforeMove = testTriangle.getArea();
    
    testTriangle.move(4.5, 6.0);
    
    const stulov::rectangle_t rectAfterMove = testTriangle.getFrameRect();
    const double areaAfterMove = testTriangle.getArea();
    
    BOOST_CHECK_CLOSE(rectBeforeMove.width, rectAfterMove.width, EPSILON);
    BOOST_CHECK_CLOSE(rectBeforeMove.height, rectAfterMove.height, EPSILON);
    BOOST_CHECK_CLOSE(areaBeforeMove, areaAfterMove, EPSILON);
    
    testTriangle.move({1.3, 5.6});
    
    BOOST_CHECK_CLOSE(rectBeforeMove.width, rectAfterMove.width, EPSILON);
    BOOST_CHECK_CLOSE(rectBeforeMove.height, rectAfterMove.height, EPSILON);
    BOOST_CHECK_CLOSE(areaBeforeMove, areaAfterMove, EPSILON);
    
  }
  
  BOOST_AUTO_TEST_CASE(TriangleAfterScale)
  {
    const double scale = 2.6;
    stulov::Triangle testTriangle({4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0});
    
    const double areaBeforeScale = testTriangle.getArea();
    
    testTriangle.scale(scale);
    
    const double areaAfterScale = testTriangle.getArea();
    
    BOOST_CHECK_CLOSE((areaBeforeScale * scale * scale), areaAfterScale, EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(TriangleWrongParameters)
  {
    stulov::Triangle testTriangle({6.9, 7.0}, {1.2, 0.3}, {3.1, 1.6});
    BOOST_CHECK_THROW(testTriangle.scale(-2.0), std::invalid_argument);
    
    BOOST_CHECK_THROW(stulov::Triangle incorrectTriangle_1({1.0, 7.0}, {1.0, 6.5}, {1.0, 8.0}), std::invalid_argument);
    BOOST_CHECK_THROW(stulov::Triangle incorrectTriangle_2({1.0, 1.0}, {1.0, 1.0}, {1.0, 1.0}), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
