#include "TestRunner.h"
#include "AABB.h"

TEST_CASE("Max Size", "[AABB]") {
    AABB aabb {0, 0, 0, 0xff};

    REQUIRE(aabb.xMin() == Approx( 0.0f ));
    REQUIRE(aabb.yMin() == Approx( 0.0f ));
    REQUIRE(aabb.zMin() == Approx( 0.0f ));

    REQUIRE(aabb.xMax() == Approx( 1.0f ));
    REQUIRE(aabb.yMax() == Approx( 1.0f ));
    REQUIRE(aabb.zMax() == Approx( 1.0f ));
}

TEST_CASE("Encoded getters", "[AABB]") {
    AABB aabb {3, 3, 3, 3};

    constexpr float TO_UNITY = 1.0f / 256.0f;

    REQUIRE(aabb.xMin() == Approx( 3.0f * TO_UNITY ));
    REQUIRE(aabb.yMin() == Approx( 3.0f * TO_UNITY ));
    REQUIRE(aabb.zMin() == Approx( 3.0f * TO_UNITY ));

    REQUIRE(aabb.xMax() == Approx( 7.0f * TO_UNITY ));
    REQUIRE(aabb.yMax() == Approx( 7.0f * TO_UNITY ));
    REQUIRE(aabb.zMax() == Approx( 7.0f * TO_UNITY ));
}

TEST_CASE("One level subdivisions", "[AABB]") {
    AABB aabb {0, 0, 0, 0xff};

    {
        AABB sub = aabb.subdivide(0);
        REQUIRE(sub.xMin() == Approx( 0.0f ));
        REQUIRE(sub.xMax() == Approx( 0.5f ));
        REQUIRE(sub.yMin() == Approx( 0.0f ));
        REQUIRE(sub.yMax() == Approx( 0.5f ));
        REQUIRE(sub.zMin() == Approx( 0.0f ));
        REQUIRE(sub.zMax() == Approx( 0.5f ));
    }

    {
        AABB sub = aabb.subdivide(1);
        REQUIRE(sub.xMin() == Approx( 0.5f ));
        REQUIRE(sub.xMax() == Approx( 1.0f ));
        REQUIRE(sub.yMin() == Approx( 0.0f ));
        REQUIRE(sub.yMax() == Approx( 0.5f ));
        REQUIRE(sub.zMin() == Approx( 0.0f ));
        REQUIRE(sub.zMax() == Approx( 0.5f ));
    }

    {
        AABB sub = aabb.subdivide(2);
        REQUIRE(sub.xMin() == Approx( 0.0f ));
        REQUIRE(sub.xMax() == Approx( 0.5f ));
        REQUIRE(sub.yMin() == Approx( 0.5f ));
        REQUIRE(sub.yMax() == Approx( 1.0f ));
        REQUIRE(sub.zMin() == Approx( 0.0f ));
        REQUIRE(sub.zMax() == Approx( 0.5f ));
    }

    {
        AABB sub = aabb.subdivide(3);
        REQUIRE(sub.xMin() == Approx( 0.5f ));
        REQUIRE(sub.xMax() == Approx( 1.0f ));
        REQUIRE(sub.yMin() == Approx( 0.5f ));
        REQUIRE(sub.yMax() == Approx( 1.0f ));
        REQUIRE(sub.zMin() == Approx( 0.0f ));
        REQUIRE(sub.zMax() == Approx( 0.5f ));
    }

    {
        AABB sub = aabb.subdivide(4);
        REQUIRE(sub.xMin() == Approx( 0.0f ));
        REQUIRE(sub.xMax() == Approx( 0.5f ));
        REQUIRE(sub.yMin() == Approx( 0.0f ));
        REQUIRE(sub.yMax() == Approx( 0.5f ));
        REQUIRE(sub.zMin() == Approx( 0.5f ));
        REQUIRE(sub.zMax() == Approx( 1.0f ));
    }

    {
        AABB sub = aabb.subdivide(5);
        REQUIRE(sub.xMin() == Approx( 0.5f ));
        REQUIRE(sub.xMax() == Approx( 1.0f ));
        REQUIRE(sub.yMin() == Approx( 0.0f ));
        REQUIRE(sub.yMax() == Approx( 0.5f ));
        REQUIRE(sub.zMin() == Approx( 0.5f ));
        REQUIRE(sub.zMax() == Approx( 1.0f ));
    }

    {
        AABB sub = aabb.subdivide(6);
        REQUIRE(sub.xMin() == Approx( 0.0f ));
        REQUIRE(sub.xMax() == Approx( 0.5f ));
        REQUIRE(sub.yMin() == Approx( 0.5f ));
        REQUIRE(sub.yMax() == Approx( 1.0f ));
        REQUIRE(sub.zMin() == Approx( 0.5f ));
        REQUIRE(sub.zMax() == Approx( 1.0f ));
    }

    {
        AABB sub = aabb.subdivide(7);
        REQUIRE(sub.xMin() == Approx( 0.5f ));
        REQUIRE(sub.xMax() == Approx( 1.0f ));
        REQUIRE(sub.yMin() == Approx( 0.5f ));
        REQUIRE(sub.yMax() == Approx( 1.0f ));
        REQUIRE(sub.zMin() == Approx( 0.5f ));
        REQUIRE(sub.zMax() == Approx( 1.0f ));
    }
}

TEST_CASE("Two level subdivisions", "[AABB]") {
    AABB aabb {0, 0, 0, 0xff};
    AABB aabb2 = aabb.subdivide(1);

    {
        AABB sub = aabb2.subdivide(0);
        REQUIRE(sub.xMin() == Approx( 0.5f ));
        REQUIRE(sub.xMax() == Approx( 0.75f ));
        REQUIRE(sub.yMin() == Approx( 0.0f ));
        REQUIRE(sub.yMax() == Approx( 0.25f ));
        REQUIRE(sub.zMin() == Approx( 0.0f ));
        REQUIRE(sub.zMax() == Approx( 0.25f ));
    }

    {
        AABB sub = aabb2.subdivide(1);
        REQUIRE(sub.xMin() == Approx( 0.75f ));
        REQUIRE(sub.xMax() == Approx( 1.0f ));
        REQUIRE(sub.yMin() == Approx( 0.0f ));
        REQUIRE(sub.yMax() == Approx( 0.25f ));
        REQUIRE(sub.zMin() == Approx( 0.0f ));
        REQUIRE(sub.zMax() == Approx( 0.25f ));
    }

    {
        AABB sub = aabb2.subdivide(2);
        REQUIRE(sub.xMin() == Approx( 0.5f ));
        REQUIRE(sub.xMax() == Approx( 0.75f ));
        REQUIRE(sub.yMin() == Approx( 0.25f ));
        REQUIRE(sub.yMax() == Approx( 0.5f ));
        REQUIRE(sub.zMin() == Approx( 0.0f ));
        REQUIRE(sub.zMax() == Approx( 0.25f ));
    }

    {
        AABB sub = aabb2.subdivide(3);
        REQUIRE(sub.xMin() == Approx( 0.75f ));
        REQUIRE(sub.xMax() == Approx( 1.0f ));
        REQUIRE(sub.yMin() == Approx( 0.25f ));
        REQUIRE(sub.yMax() == Approx( 0.5f ));
        REQUIRE(sub.zMin() == Approx( 0.0f ));
        REQUIRE(sub.zMax() == Approx( 0.25f ));
    }

    {
        AABB sub = aabb2.subdivide(4);
        REQUIRE(sub.xMin() == Approx( 0.5f ));
        REQUIRE(sub.xMax() == Approx( 0.75f ));
        REQUIRE(sub.yMin() == Approx( 0.0f ));
        REQUIRE(sub.yMax() == Approx( 0.25f ));
        REQUIRE(sub.zMin() == Approx( 0.25f ));
        REQUIRE(sub.zMax() == Approx( 0.5f ));
    }

    {
        AABB sub = aabb2.subdivide(5);
        REQUIRE(sub.xMin() == Approx( 0.75f ));
        REQUIRE(sub.xMax() == Approx( 1.0f ));
        REQUIRE(sub.yMin() == Approx( 0.0f ));
        REQUIRE(sub.yMax() == Approx( 0.25f ));
        REQUIRE(sub.zMin() == Approx( 0.25f ));
        REQUIRE(sub.zMax() == Approx( 0.5f ));
    }

    {
        AABB sub = aabb2.subdivide(6);
        REQUIRE(sub.xMin() == Approx( 0.5f ));
        REQUIRE(sub.xMax() == Approx( 0.75f ));
        REQUIRE(sub.yMin() == Approx( 0.25f ));
        REQUIRE(sub.yMax() == Approx( 0.5f ));
        REQUIRE(sub.zMin() == Approx( 0.25f ));
        REQUIRE(sub.zMax() == Approx( 0.5f ));
    }

    {
        AABB sub = aabb2.subdivide(7);
        REQUIRE(sub.xMin() == Approx( 0.75f ));
        REQUIRE(sub.xMax() == Approx( 1.0f ));
        REQUIRE(sub.yMin() == Approx( 0.25f ));
        REQUIRE(sub.yMax() == Approx( 0.5f ));
        REQUIRE(sub.zMin() == Approx( 0.25f ));
        REQUIRE(sub.zMax() == Approx( 0.5f ));
    }
}