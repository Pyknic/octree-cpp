#pragma once

#include "AABB.h"

enum Intersection {
    DISJOINT   = 0,
    INTERSECTS = 1,
    CONTAINS   = 2
};

class Shape {
public:
    virtual ~Shape() = 0;

    virtual Intersection intersects(const AABB& bounds) const = 0;

};
