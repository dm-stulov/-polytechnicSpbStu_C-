#include <boost/test/auto_unit_test.hpp>
#include <memory>
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "polygon.hpp"
#include "partition.hpp"

#define EPSILON = 1e-10;

BOOST_AUTO_TEST_SUITE(matrixTestSuite)

  BOOST_AUTO_TEST_CASE(matrixCopyConstructor)
  {
    stulov::Shape::ptr_type circlePtr = std::make_shared<stulov::Circle>(stulov::point_t{1, 2}, 4);
    stulov::Shape::ptr_type rectanglePtr = std::make_shared<stulov::Rectangle>(stulov::point_t{1.0, 2.0}, 4.0, 5.0);
    stulov::Shape::ptr_type trianglePtr = std::make_shared<stulov::Triangle>(stulov::point_t{4.0, 10.0},
        stulov::point_t{15.0, 6.0}, stulov::point_t{1.0, 1.0});
    stulov::point_t *points = new stulov::point_t[3]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}};
    stulov::Shape::ptr_type polygonPtr = std::make_shared<stulov::Polygon>(3, points);
    delete[] points;
  
    stulov::CompositeShape testComposite;
  
    testComposite.add(circlePtr);
    testComposite.add(rectanglePtr);
    testComposite.add(trianglePtr);
    testComposite.add(polygonPtr);
  
    stulov::Matrix testMatrix = stulov::partition(testComposite);
    stulov::Matrix testMatrixCopy(testMatrix);

    BOOST_CHECK(testMatrix == testMatrixCopy);
    BOOST_CHECK_EQUAL(testMatrixCopy.getRows(), testMatrix.getRows());
    BOOST_CHECK_EQUAL(testMatrixCopy.getColumns(), testMatrix.getColumns());
}

  BOOST_AUTO_TEST_CASE(matrixMoveConstructor)
  {
    stulov::Shape::ptr_type circlePtr = std::make_shared<stulov::Circle>(stulov::point_t{1, 2}, 4);
    stulov::Shape::ptr_type rectanglePtr = std::make_shared<stulov::Rectangle>(stulov::point_t{1.0, 2.0}, 4.0, 5.0);
    stulov::Shape::ptr_type trianglePtr = std::make_shared<stulov::Triangle>(stulov::point_t{4.0, 10.0},
        stulov::point_t{15.0, 6.0}, stulov::point_t{1.0, 1.0});
    stulov::point_t *points = new stulov::point_t[3]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}};
    stulov::Shape::ptr_type polygonPtr = std::make_shared<stulov::Polygon>(3, points);
    delete[] points;
  
    stulov::CompositeShape testComposite;
  
    testComposite.add(circlePtr);
    testComposite.add(rectanglePtr);
    testComposite.add(trianglePtr);
    testComposite.add(polygonPtr);

    stulov::Matrix testMatrix = stulov::partition(testComposite);
    stulov::Matrix testMatrixCopy(testMatrix);
    stulov::Matrix testMatrixMove = std::move(testMatrix);

    BOOST_CHECK(testMatrixMove == testMatrixCopy);
    BOOST_CHECK_EQUAL(testMatrixMove.getRows(), testMatrixCopy.getRows());
    BOOST_CHECK_EQUAL(testMatrixMove.getColumns(), testMatrixCopy.getColumns());;
  }

  BOOST_AUTO_TEST_CASE(matrixCopyAssigmentOperator)
  {
    stulov::Shape::ptr_type circlePtr = std::make_shared<stulov::Circle>(stulov::point_t{1, 2}, 4);
    stulov::Shape::ptr_type rectanglePtr = std::make_shared<stulov::Rectangle>(stulov::point_t{1.0, 2.0}, 4.0, 5.0);
    stulov::Shape::ptr_type trianglePtr = std::make_shared<stulov::Triangle>(stulov::point_t{4.0, 10.0},
        stulov::point_t{15.0, 6.0}, stulov::point_t{1.0, 1.0});
    stulov::point_t *points = new stulov::point_t[3]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}};
    stulov::Shape::ptr_type polygonPtr = std::make_shared<stulov::Polygon>(3, points);
    delete[] points;
  
    stulov::CompositeShape testComposite;
  
    testComposite.add(circlePtr);
    testComposite.add(rectanglePtr);
    testComposite.add(trianglePtr);
    testComposite.add(polygonPtr);
  
    stulov::Matrix testMatrix = stulov::partition(testComposite);
    stulov::Matrix testMatrixCopy;
    testMatrixCopy = testMatrix;

    BOOST_CHECK(testMatrixCopy == testMatrix);
    BOOST_CHECK_EQUAL(testMatrixCopy.getRows(), testMatrix.getRows());
    BOOST_CHECK_EQUAL(testMatrixCopy.getColumns(), testMatrix.getColumns());;
}

  BOOST_AUTO_TEST_CASE(matrixMoveAssigmentOperator)
  {
    stulov::Shape::ptr_type circlePtr = std::make_shared<stulov::Circle>(stulov::point_t{1, 2}, 4);
    stulov::Shape::ptr_type rectanglePtr = std::make_shared<stulov::Rectangle>(stulov::point_t{1.0, 2.0}, 4.0, 5.0);
    stulov::Shape::ptr_type trianglePtr = std::make_shared<stulov::Triangle>(stulov::point_t{4.0, 10.0},
        stulov::point_t{15.0, 6.0}, stulov::point_t{1.0, 1.0});
    stulov::point_t *points = new stulov::point_t[3]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}};
    stulov::Shape::ptr_type polygonPtr = std::make_shared<stulov::Polygon>(3, points);
    delete[] points;
  
    stulov::CompositeShape testComposite;
  
    testComposite.add(circlePtr);
    testComposite.add(rectanglePtr);
    testComposite.add(trianglePtr);
    testComposite.add(polygonPtr);

    stulov::Matrix testMatrix = stulov::partition(testComposite);
    stulov::Matrix testMatrixCopy(testMatrix);
    stulov::Matrix testMatrixMove;
    testMatrixMove = std::move(testMatrix);

    BOOST_CHECK(testMatrixMove == testMatrixCopy);
    BOOST_CHECK_EQUAL(testMatrixMove.getRows(), testMatrixCopy.getRows());
    BOOST_CHECK_EQUAL(testMatrixMove.getColumns(), testMatrixCopy.getColumns());;
  }

  BOOST_AUTO_TEST_CASE(matrixThrowExceptions)
  {
    stulov::Shape::ptr_type circlePtr = std::make_shared<stulov::Circle>(stulov::point_t{1, 2}, 4);
    stulov::Shape::ptr_type rectanglePtr = std::make_shared<stulov::Rectangle>(stulov::point_t{1.0, 2.0}, 4.0, 5.0);
    stulov::Shape::ptr_type trianglePtr = std::make_shared<stulov::Triangle>(stulov::point_t{4.0, 10.0},
        stulov::point_t{15.0, 6.0}, stulov::point_t{1.0, 1.0});
    stulov::point_t *points = new stulov::point_t[3]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}};
    stulov::Shape::ptr_type polygonPtr = std::make_shared<stulov::Polygon>(3, points);
    delete[] points;
  
    stulov::CompositeShape testComposite;
  
    testComposite.add(circlePtr);
    testComposite.add(rectanglePtr);
    testComposite.add(trianglePtr);
    testComposite.add(polygonPtr);


    stulov::Matrix testMatrix = stulov::partition(testComposite);
  
    BOOST_CHECK_THROW(testMatrix[50], std::out_of_range);
    BOOST_CHECK_THROW(testMatrix[-5], std::out_of_range);
  }

BOOST_AUTO_TEST_SUITE_END()
