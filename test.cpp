#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "include/point.h"
#include "include/triangle.h"
#include "include/list.h"

TEST_CASE("Triangle geometry tests") {
    Point p1(0, 0);
    Point p2(0, 3);
    Point p3(4, 0);
    Triangle t(p1, p2, p3);

    SUBCASE("Validation") {
        CHECK(t.is_valid() == true);
    }
    SUBCASE("Area and Perimeter") {
        CHECK(t.perimeter() == doctest::Approx(12.0));
        CHECK(t.area() == doctest::Approx(6.0));
    }
    SUBCASE("Ravnobedr check") {
        CHECK(t.ravnobedr() == false);
    }
}

TEST_CASE("List logic tests") {
    List l;
    Triangle t(Point(0,0), Point(0,3), Point(4,0));

    SUBCASE("Insert and Get") {
        l.GotoBeg();
        CHECK(l.Insert(t) == 0);

        l.StepForward();
        Triangle out;
        CHECK(l.Get(&out) == 0);
        CHECK(out.is_valid() == true);
    }

    SUBCASE("Delete node") {
        l.GotoBeg();
        l.Insert(t);
        CHECK(l.Delete() == 0);
        CHECK(l.StepForward() == -1);
    }
}