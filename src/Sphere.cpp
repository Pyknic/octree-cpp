#include "Sphere.h"

Sphere::Sphere(float x, float y, float z, float radius) :
    x{x}, y{y}, z{z}, radius{radius} {}

Sphere::~Sphere() = default;

Intersection Sphere::intersects(const AABB &bounds) const {
    float sqDist = 0.0f;
    auto boundary = bounds.xMin();
    if (x < boundary) sqDist += (boundary - x) * (boundary - x);
    boundary = bounds.xMax();
    if (x > boundary) sqDist += (x - boundary) * (x - boundary);
    boundary = bounds.yMin();
    if (y < boundary) sqDist += (boundary - y) * (boundary - y);
    boundary = bounds.yMax();
    if (y > boundary) sqDist += (y - boundary) * (y - boundary);
    boundary = bounds.zMin();
    if (z < boundary) sqDist += (boundary - z) * (boundary - z);
    boundary = bounds.zMax();
    if (z > boundary) sqDist += (z - boundary) * (z - boundary);

    if (sqDist < radius * radius) {
        return INTERSECTS;
    } else {
        return DISJOINT; // TODO: Not strictly correct since an AABB completely covered by the sphere should still be considered a collision
    }
}


