#include <stdexcept>
#include <boost/test/auto_unit_test.hpp>
#include "polygon.hpp"

#define EPSILON 1e-10

BOOST_AUTO_TEST_SUITE(shapePolygon)

  BOOST_AUTO_TEST_CASE(copyConstructor)
  {
    stulov::point_t *points = new stulov::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
    stulov::Polygon testPolygon(4, points);
    delete[] points;
    stulov::Polygon copiedPolygon(testPolygon);

    BOOST_CHECK_CLOSE(copiedPolygon.getArea(), testPolygon.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(copiedPolygon.getFrameRect().height, testPolygon.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(copiedPolygon.getFrameRect().width, testPolygon.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(copiedPolygon.getFrameRect().pos.x, testPolygon.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(copiedPolygon.getFrameRect().pos.y, testPolygon.getFrameRect().pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(moveConstructor)
  {
    stulov::point_t *points = new stulov::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
    stulov::Polygon testPolygon(4, points);
    delete[] points;
    double areaBefore = testPolygon.getArea();
    stulov::rectangle_t frameRectBefore = testPolygon.getFrameRect();
    stulov::Polygon movedPolygon(std::move(testPolygon));

    BOOST_CHECK_CLOSE(areaBefore, movedPolygon.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(frameRectBefore.height, movedPolygon.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(frameRectBefore.width, movedPolygon.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(frameRectBefore.pos.x, movedPolygon.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(frameRectBefore.pos.y, movedPolygon.getFrameRect().pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(copyAssignmentOperator)
  {
    stulov::point_t *points = new stulov::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
    stulov::Polygon testPolygon(4, points);
    delete[] points;
    stulov::point_t *points1 = new stulov::point_t[3]{{4.0, 12.0}, {15.0, 6.0}, {1.0, 1.0}};
    stulov::Polygon copiedPolygon(3, points1);
    delete[] points1;
    copiedPolygon = testPolygon;

    BOOST_CHECK_CLOSE(testPolygon.getArea(), copiedPolygon.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(testPolygon.getFrameRect().height, copiedPolygon.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(testPolygon.getFrameRect().width, copiedPolygon.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(testPolygon.getFrameRect().pos.x, copiedPolygon.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(testPolygon.getFrameRect().pos.y, copiedPolygon.getFrameRect().pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(moveAssignmentOperator)
  {
    stulov::point_t *points = new stulov::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
    stulov::Polygon testPolygon(4, points);
    delete[] points;

    double areaBefore = testPolygon.getArea();
    stulov::rectangle_t frameRectBefore = testPolygon.getFrameRect();
    stulov::point_t *points1 = new stulov::point_t[3]{{4.0, 12.0}, {15.0, 6.0}, {1.0, 1.0}};
    stulov::Polygon movedPolygon(3, points1);
    delete[] points1;
    movedPolygon = std::move(testPolygon);
    BOOST_CHECK_CLOSE(areaBefore, movedPolygon.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(frameRectBefore.height, movedPolygon.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(frameRectBefore.width, movedPolygon.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(frameRectBefore.pos.x, movedPolygon.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(frameRectBefore.pos.y, movedPolygon.getFrameRect().pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(PolygonAfterShiftMove)
  {
    stulov::point_t *points = new stulov::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
    stulov::Polygon testPolygon(4, points);
    delete[] points;    
    const stulov::rectangle_t rectBeforeMove = testPolygon.getFrameRect();
    const double areaBeforeMove = testPolygon.getArea();

    testPolygon.move(0.5, 6.0);

    const stulov::rectangle_t rectAfterMove = testPolygon.getFrameRect();
    const double areaAfterMove = testPolygon.getArea();

    BOOST_CHECK_CLOSE(rectBeforeMove.width, rectAfterMove.width, EPSILON);
    BOOST_CHECK_CLOSE(rectBeforeMove.height, rectAfterMove.height, EPSILON);
    BOOST_CHECK_CLOSE(areaBeforeMove, areaAfterMove, EPSILON);
  }

    BOOST_AUTO_TEST_CASE(PolygonAfterPointMove)
  {
    stulov::point_t *points = new stulov::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
    stulov::Polygon testPolygon(4, points);
    delete[] points;
    const stulov::rectangle_t rectBeforeMove = testPolygon.getFrameRect();
    const double areaBeforeMove = testPolygon.getArea();

    testPolygon.move({0.4, 5.0});

    const stulov::rectangle_t rectAfterMove = testPolygon.getFrameRect();
    const double areaAfterMove = testPolygon.getArea();

    BOOST_CHECK_CLOSE(rectBeforeMove.width, rectAfterMove.width, EPSILON);
    BOOST_CHECK_CLOSE(rectBeforeMove.height, rectAfterMove.height, EPSILON);
    BOOST_CHECK_CLOSE(areaBeforeMove, areaAfterMove, EPSILON);  
  }
  
  BOOST_AUTO_TEST_CASE(PolygonAfterScale)
  {
    const double scale = 5.0;
    const double declineScale = 0.6;
    stulov::point_t *points = new stulov::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
    stulov::Polygon testPolygon(4, points);
    delete[] points;

    double areaBeforeScale = testPolygon.getArea();
    testPolygon.scale(scale);
    double areaAfterScale = testPolygon.getArea();
    BOOST_CHECK_CLOSE((areaBeforeScale * scale * scale), areaAfterScale, EPSILON);

    areaBeforeScale = testPolygon.getArea();
    testPolygon.scale(declineScale);
    areaAfterScale = testPolygon.getArea();
    BOOST_CHECK_CLOSE((areaBeforeScale * declineScale * declineScale), areaAfterScale, EPSILON);

  }

  BOOST_AUTO_TEST_CASE(PolygonWrongParameters)
  {
    stulov::point_t *points = new stulov::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
    stulov::Polygon testPolygon(4, points);
    delete[] points;    
    BOOST_CHECK_THROW(testPolygon.scale(-2.0), std::invalid_argument);
    //ÐºÐ¾Ð»Ð¸ÑÐµÑÑÐ²Ð¾ ÑÑÐ¾ÑÐ¾Ð½
    stulov::point_t *points1 = new stulov::point_t[2]{{4.0, 10.0}, {15.0, 6.0}};
    BOOST_CHECK_THROW(stulov::Polygon incorrectPolygon1(2, points1), std::invalid_argument);
    delete[] points1;

    //Ð¿ÑÐ¾Ð²ÐµÑÐºÐ° Ð½Ð° Ð²ÑÑÐ¾Ð¶Ð´ÐµÐ½Ð½Ð¾ÑÑÑ
    stulov::point_t *points2 = new stulov::point_t[4]{{4.0, 10.0}, {4.0, 6.0}, {4.0, 1.0}, {4.0, 6.0}};
    BOOST_CHECK_THROW(stulov::Polygon incorrectPolygon2(4, points2), std::invalid_argument);
    delete[] points2;

    //Ð²ÑÐ¿ÑÐºÐ»Ð¾ÑÑÑ
    stulov::point_t *points3 = new stulov::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {5.0, 5.0}};
    BOOST_CHECK_THROW(stulov::Polygon incorrectPolygon3(4, points3), std::invalid_argument);
    delete[] points3;
  }

BOOST_AUTO_TEST_SUITE_END()
