#pragma once
#include "Shape.h"

class Sphere : public Shape {
public:
    Sphere(float x, float y, float z, float radius);

    ~Sphere() override;

    Intersection intersects(const AABB &bounds) const override;

private:
    const float x, y, z;
    const float radius;
};
