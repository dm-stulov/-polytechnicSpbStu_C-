#include <stdexcept>

#include <boost/test/auto_unit_test.hpp>

#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "polygon.hpp"

#define EPSILON 1e-10


BOOST_AUTO_TEST_SUITE(testSuiteForCompositeShape)
  
  BOOST_AUTO_TEST_CASE(testCopyConstructorForCompositeShape)
  {
    stulov::Shape::ptr_type testRectangle = std::make_shared<stulov::Rectangle>(stulov::point_t{1.0, 2.0}, 4.0, 5.0);
    stulov::CompositeShape testComposite(testRectangle);
    
    stulov::CompositeShape copiedComposite(testComposite);
    BOOST_CHECK_CLOSE(testComposite.getArea(), copiedComposite.getArea(), EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(testMoveConstructorForCompositeShape)
  {
    stulov::Shape::ptr_type testCircle = std::make_shared<stulov::Circle>(stulov::point_t{1, 2}, 4);

    stulov::CompositeShape testComposite(testCircle);
  
    const double initialArea = testComposite.getArea();
    
    stulov::CompositeShape movedComposite(std::move(testComposite));
    BOOST_CHECK_CLOSE(initialArea, movedComposite.getArea(), EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(copyAssigmentOperatorForCompositeShape)
  {
    stulov::Shape::ptr_type testRectangle = std::make_shared<stulov::Rectangle>(stulov::point_t{1.0, 2.0}, 4.0, 5.0);
    stulov::Shape::ptr_type testCircle = std::make_shared<stulov::Circle>(stulov::point_t{1, 2}, 4);
    stulov::CompositeShape testComposite(testRectangle);
    
    stulov::CompositeShape copiedEmptyComposite;
    copiedEmptyComposite = testComposite;
    BOOST_CHECK_CLOSE(testComposite.getArea(), copiedEmptyComposite.getArea(), EPSILON);
    
    stulov::CompositeShape copiedComposite(testCircle);
    copiedComposite = copiedEmptyComposite;
    BOOST_CHECK_CLOSE(copiedComposite.getArea(), copiedEmptyComposite.getArea(), EPSILON);
    
  }
  
  BOOST_AUTO_TEST_CASE(moveAssigmentOperatorForCompositeShape)
  {
    stulov::Shape::ptr_type testRectangle = std::make_shared<stulov::Rectangle>(stulov::point_t{1.0, 2.0}, 4.0, 5.0);
    stulov::Shape::ptr_type testCircle = std::make_shared<stulov::Circle>(stulov::point_t{1, 2}, 4);
    
    stulov::CompositeShape testComposite(testRectangle);
    const double initialArea = testComposite.getArea();
    
    stulov::CompositeShape movedEmptyComposite;
    movedEmptyComposite = std::move(testComposite);
    
    BOOST_CHECK_CLOSE(initialArea, movedEmptyComposite.getArea(), EPSILON);
    
    stulov::CompositeShape movedComposite(testCircle);
    
    movedComposite = std::move(movedEmptyComposite);
    BOOST_CHECK_CLOSE(initialArea, movedComposite.getArea(), EPSILON);
    
  }
  BOOST_AUTO_TEST_CASE(testConstructorForCompositeShape)
  {
    stulov::Shape::ptr_type testRectangle = std::make_shared<stulov::Rectangle>(stulov::point_t{1.0, 2.0}, 4.0, 5.0);
    stulov::CompositeShape testComposite(testRectangle);
    
    BOOST_CHECK_CLOSE(testComposite.getFrameRect().pos.x, testRectangle->getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(testComposite.getFrameRect().pos.y, testRectangle->getFrameRect().pos.y, EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(checkRangeOperatorforCompositeShape)
  {
    stulov::Shape::ptr_type testCircle = std::make_shared<stulov::Circle>(stulov::point_t{1, 2}, 4);
    stulov::Shape::ptr_type testRectangle = std::make_shared<stulov::Rectangle>(stulov::point_t{1.0, 2.0}, 4.0, 5.0);
    stulov::Shape::ptr_type testTriangle = std::make_shared<stulov::Triangle>(stulov::point_t{4.0, 10.0},
        stulov::point_t{15.0, 6.0}, stulov::point_t{1.0, 1.0});
    stulov::point_t *points = new stulov::point_t[3]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}};
    stulov::Shape::ptr_type testPolygon = std::make_shared<stulov::Polygon>(3, points);
    delete[] points;
  
    stulov::CompositeShape testComposite;
  
    testComposite.add(testCircle);
    testComposite.add(testRectangle);
    testComposite.add(testTriangle);
    testComposite.add(testPolygon);
    
    BOOST_CHECK_CLOSE(testRectangle->getArea(), testComposite[1]->getArea(), EPSILON);
    BOOST_CHECK_CLOSE(testRectangle->getFrameRect().pos.x, testComposite[1]->getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(testRectangle->getFrameRect().pos.y, testComposite[1]->getFrameRect().pos.y, EPSILON);
    
    BOOST_CHECK_THROW(testComposite[testComposite.getCount()+1], std::out_of_range);
  }
  
  BOOST_AUTO_TEST_CASE(compositeShapeAfterShiftMove)
  {
    stulov::Shape::ptr_type testCircle = std::make_shared<stulov::Circle>(stulov::point_t{1, 2}, 4);
    stulov::Shape::ptr_type testRectangle = std::make_shared<stulov::Rectangle>(stulov::point_t{1.0, 2.0}, 4.0, 5.0);
    stulov::Shape::ptr_type testTriangle = std::make_shared<stulov::Triangle>(stulov::point_t{4.0, 10.0},
        stulov::point_t{15.0, 6.0}, stulov::point_t{1.0, 1.0});
    stulov::point_t *points = new stulov::point_t[3]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}};
    stulov::Shape::ptr_type testPolygon = std::make_shared<stulov::Polygon>(3, points);
    delete[] points;
  
    stulov::CompositeShape testComposite;
  
    testComposite.add(testCircle);
    testComposite.add(testRectangle);
    testComposite.add(testTriangle);
    testComposite.add(testPolygon);
    
    const double beforeArea = testComposite.getArea();
    const stulov::rectangle_t beforeFrameRect = testComposite.getFrameRect();
    testComposite.move(1.0, 2.0);
    BOOST_CHECK_CLOSE(beforeArea, testComposite.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(testComposite.getFrameRect().width, beforeFrameRect.width, EPSILON);
    BOOST_CHECK_CLOSE(testComposite.getFrameRect().height, beforeFrameRect.height, EPSILON);
    
  }
  
  BOOST_AUTO_TEST_CASE(compositeShapeAfterPointMove)
  {
    stulov::Shape::ptr_type testCircle = std::make_shared<stulov::Circle>(stulov::point_t{1, 2}, 4);
    stulov::Shape::ptr_type testRectangle = std::make_shared<stulov::Rectangle>(stulov::point_t{1.0, 2.0}, 4.0, 5.0);
    stulov::Shape::ptr_type testTriangle = std::make_shared<stulov::Triangle>(stulov::point_t{4.0, 10.0},
        stulov::point_t{15.0, 6.0}, stulov::point_t{1.0, 1.0});
    stulov::point_t *points = new stulov::point_t[3]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}};
    stulov::Shape::ptr_type testPolygon = std::make_shared<stulov::Polygon>(3, points);
    delete[] points;
  
    stulov::CompositeShape testComposite;
  
    testComposite.add(testCircle);
    testComposite.add(testRectangle);
    testComposite.add(testTriangle);
    testComposite.add(testPolygon);
  
    const double beforeArea = testComposite.getArea();
    const stulov::rectangle_t beforeFrameRect = testComposite.getFrameRect();
    testComposite.move({1.0, 2.0});
    BOOST_CHECK_CLOSE(beforeArea, testComposite.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(testComposite.getFrameRect().width, beforeFrameRect.width, EPSILON);
    BOOST_CHECK_CLOSE(testComposite.getFrameRect().height, beforeFrameRect.height, EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(CompositeShapeScale)
  {
    stulov::Shape::ptr_type testCircle = std::make_shared<stulov::Circle>(stulov::point_t{1, 2}, 4);
    stulov::Shape::ptr_type testRectangle = std::make_shared<stulov::Rectangle>(stulov::point_t{1.0, 2.0}, 4.0, 5.0);
    stulov::Shape::ptr_type testTriangle = std::make_shared<stulov::Triangle>(stulov::point_t{4.0, 10.0},
        stulov::point_t{15.0, 6.0}, stulov::point_t{1.0, 1.0});
    stulov::point_t *points = new stulov::point_t[3]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}};
    stulov::Shape::ptr_type testPolygon = std::make_shared<stulov::Polygon>(3, points);
    delete[] points;
  
    stulov::CompositeShape testComposite;
  
    testComposite.add(testCircle);
    testComposite.add(testRectangle);
    testComposite.add(testTriangle);
    testComposite.add(testPolygon);
  
    double beforeArea = testComposite.getArea();
    double scale = 3;
    testComposite.scale(scale);
    BOOST_CHECK_CLOSE(beforeArea * scale * scale, testComposite.getArea(), EPSILON);
    
    beforeArea = testComposite.getArea();
    scale = 0.5;
    testComposite.scale(scale);
    BOOST_CHECK_CLOSE(beforeArea * scale * scale, testComposite.getArea(), EPSILON);
    
    BOOST_CHECK_THROW(testComposite.scale(-10), std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(compositeShapeAdd)
  {
    stulov::Shape::ptr_type testCircle = std::make_shared<stulov::Circle>(stulov::point_t{1, 2}, 4);
    stulov::Shape::ptr_type testRectangle = std::make_shared<stulov::Rectangle>(stulov::point_t{1.0, 2.0}, 4.0, 5.0);
    stulov::Shape::ptr_type testTriangle = std::make_shared<stulov::Triangle>(stulov::point_t{4.0, 10.0},
                                                                                stulov::point_t{15.0, 6.0}, stulov::point_t{1.0, 1.0});
    stulov::point_t *points = new stulov::point_t[3]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}};
    stulov::Shape::ptr_type testPolygon = std::make_shared<stulov::Polygon>(3, points);
    delete[] points;
  
    stulov::CompositeShape testComposite;
  
    testComposite.add(testCircle);
  
    BOOST_CHECK_CLOSE(testComposite.getArea(), testCircle->getArea(), EPSILON);
    BOOST_CHECK_CLOSE(testComposite.getFrameRect().pos.x, testCircle->getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(testComposite.getFrameRect().pos.y, testCircle->getFrameRect().pos.y, EPSILON);
  
    testComposite.add(testRectangle);
    testComposite.add(testTriangle);
    testComposite.add(testPolygon);
    BOOST_CHECK_EQUAL(testComposite.getCount(), 4);
  }
  
  
  BOOST_AUTO_TEST_CASE(compositeShapeRemove)
  {
    stulov::Shape::ptr_type testCircle = std::make_shared<stulov::Circle>(stulov::point_t{1, 2}, 4);
    stulov::Shape::ptr_type testRectangle = std::make_shared<stulov::Rectangle>(stulov::point_t{1.0, 2.0}, 4.0, 5.0);
    stulov::Shape::ptr_type testTriangle = std::make_shared<stulov::Triangle>(stulov::point_t{4.0, 10.0},
        stulov::point_t{15.0, 6.0}, stulov::point_t{1.0, 1.0});
    stulov::point_t *points = new stulov::point_t[3]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}};
    stulov::Shape::ptr_type testPolygon = std::make_shared<stulov::Polygon>(3, points);
    delete[] points;
  
    stulov::CompositeShape testComposite;
  
    testComposite.add(testCircle);        //0
    testComposite.add(testRectangle);     //1
    testComposite.add(testTriangle);      //2
    testComposite.add(testPolygon);       //3
    
    const int count = testComposite.getCount();
    //by index
    testComposite.remove(3);//remove polygon
    const int countAfterRemove = testComposite.getCount();
    
    BOOST_CHECK_EQUAL(count - 1, countAfterRemove);
  }

BOOST_AUTO_TEST_SUITE_END()
