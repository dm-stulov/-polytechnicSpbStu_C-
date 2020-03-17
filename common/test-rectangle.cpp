#include <stdexcept>
#include <boost/test/auto_unit_test.hpp>
#include "rectangle.hpp"

#define EPSILON 1e-10

BOOST_AUTO_TEST_SUITE(shapeRectangle)
  
  BOOST_AUTO_TEST_CASE(RectangleAfterMove)
  {

    stulov::Rectangle testRectangle({5.0, 2.0}, 6.9, 7.0);
    const stulov::rectangle_t rectBeforeMove = testRectangle.getFrameRect();
    const double areaBeforeMoving = testRectangle.getArea();

    testRectangle.move(4.5, 6.0);
    
    const stulov::rectangle_t rectAfterMove = testRectangle.getFrameRect();
    const double areaAfterMove = testRectangle.getArea();
    
    BOOST_CHECK_CLOSE(rectAfterMove.width, rectBeforeMove.width, EPSILON);
    BOOST_CHECK_CLOSE(rectAfterMove.height, rectBeforeMove.height, EPSILON);
    BOOST_CHECK_CLOSE(areaAfterMove, areaBeforeMoving, EPSILON);

    testRectangle.move({1.3, 5.6});

    BOOST_CHECK_CLOSE(testRectangle.getFrameRect().width, rectBeforeMove.width, EPSILON);
    BOOST_CHECK_CLOSE(testRectangle.getFrameRect().height, rectBeforeMove.height, EPSILON);
    BOOST_CHECK_CLOSE(areaAfterMove, areaBeforeMoving, EPSILON);

  }

  BOOST_AUTO_TEST_CASE(RectangleAfterScale)
  {
    const double scale = 0.5;
    stulov::Rectangle testRectangle{{0.6, 4.5}, 5.0, 6.0};
    const double areaBeforeScale = testRectangle.getArea();

    testRectangle.scale(scale);
  
    const double areaAfterScale = testRectangle.getArea();
  
    BOOST_CHECK_CLOSE((areaBeforeScale * scale * scale), areaAfterScale, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(RectangleIncorrectParameters)
  {
    stulov::Rectangle testRectangle({1.0, 6.0}, 5.0, 4.0);

    BOOST_CHECK_THROW(stulov::Rectangle incorrectRectangle_1({1.0, 6.0}, 5.0, -4.0), std::invalid_argument);
    BOOST_CHECK_THROW(stulov::Rectangle incorrectRectangle_2({1.0, 6.0}, -5.0, 4.0), std::invalid_argument);
    BOOST_CHECK_THROW(testRectangle.scale(-2.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
