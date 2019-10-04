#pragma once
#include <cstdint>

class AABB {
public:
    AABB(uint8_t x, uint8_t y, uint8_t z, uint8_t sizeMinusOne);

    float xMin() const;

    float yMin() const;

    float zMin() const;

    float xMax() const;

    float yMax() const;

    float zMax() const;

    AABB subdivide(uint8_t index) const;

private:
    const uint8_t x, y, z, sizeMinusOne;
};
