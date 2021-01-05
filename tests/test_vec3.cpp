#include <catch.hpp>
#include <common/Vec3.hpp>

TEST_CASE("Vec3 testing", "[Vec3]" ) {

    Point3 a(10.0, 20.0, 30.0);
    Point3 b(1.0, 2.0, 3.0);

    Point3 c = a + b;

    REQUIRE(c.x() == 11.0);
    REQUIRE(c.y() == 22.0);
    REQUIRE(c.z() == 33.0);
}