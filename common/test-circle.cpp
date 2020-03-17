#include <stdexcept>
#include <boost/test/auto_unit_test.hpp>
#include "circle.hpp"

#define EPSILON 1e-10

BOOST_AUTO_TEST_SUITE(shapeCircle)

BOOST_AUTO_TEST_CASE(CircleAfterMove)
{
  const double radius = 6.5;
  stulov::Circle testCircle({1.0, 2.0}, radius);

  const stulov::rectangle_t rectBeforeMove = testCircle.getFrameRect();
  const double areaBeforeMove = testCircle.getArea();

  testCircle.move(3.0, 6.1);

  const stulov::rectangle_t rectAfterMove = testCircle.getFrameRect();
  const double areaAfterMove = testCircle.getArea();

  BOOST_CHECK_CLOSE(rectAfterMove.width, rectBeforeMove.width, EPSILON);
  BOOST_CHECK_CLOSE(rectAfterMove.height, rectBeforeMove.height, EPSILON);
  BOOST_CHECK_CLOSE(areaAfterMove, areaBeforeMove, EPSILON);

  testCircle.move({1.0, 5.0});

  BOOST_CHECK_CLOSE(rectAfterMove.width, rectBeforeMove.width, EPSILON);
  BOOST_CHECK_CLOSE(rectAfterMove.height, rectBeforeMove.height, EPSILON);
  BOOST_CHECK_CLOSE(areaAfterMove, areaBeforeMove, EPSILON);
}

BOOST_AUTO_TEST_CASE(CircleAfterScale)
{
  const double scale = 2.0;
  stulov::Circle testCircle({8.0, 6.5}, 9.0);
  const double areaBeforeScale = testCircle.getArea();

  testCircle.scale(scale);

  const double areaAfterScale = testCircle.getArea();
  
  BOOST_CHECK_CLOSE((areaBeforeScale * scale * scale), areaAfterScale, EPSILON);
}

BOOST_AUTO_TEST_CASE(CircleIncorrectParameters)
{
  stulov::Circle testCircle({2.0, -6.0}, 4.3);

  BOOST_CHECK_THROW(testCircle.scale(-3.0), std::invalid_argument);
  BOOST_CHECK_THROW(stulov::Circle wrongCircle({2.0, -6.0}, -4.3), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
