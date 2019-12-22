#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE point
#include <boost/test/unit_test.hpp>
#include "../include/point.hpp"

BOOST_AUTO_TEST_SUITE(point)

BOOST_AUTO_TEST_CASE(addition)
{
    Point<int> p1{1, 1};
    Point<int> p2{-99, -10};
    BOOST_REQUIRE_EQUAL((p1 + p2), (Point<int>{-98, -9}));
}

    
BOOST_AUTO_TEST_CASE(substraction)
{
    Point<int> p1{1, 1};
    Point<int> p2{-99, -10};
    BOOST_REQUIRE_EQUAL(p1 - p2, (Point<int>{100, 11}));
}

BOOST_AUTO_TEST_CASE(multiplication)
{
    Point<int> p1{1, 1};
    BOOST_REQUIRE_EQUAL(p1 * 33, (Point<int>{33, 33}));
}

BOOST_AUTO_TEST_CASE(division)
{
    Point<int> p1{1024, 256};
    BOOST_REQUIRE_EQUAL(p1 / 16, (Point<int>{64, 16}));
}

BOOST_AUTO_TEST_SUITE_END()
