#include "AABB.h"

constexpr float TO_UNITY = 1.0f / 256.0f;

AABB::AABB(uint8_t x, uint8_t y, uint8_t z, uint8_t sizeMinusOne) :
    x{x}, y{y}, z{z}, sizeMinusOne{sizeMinusOne} {}

float AABB::xMin() const {
    return (float) x * TO_UNITY;
}

float AABB::yMin() const {
    return (float) y * TO_UNITY;
}

float AABB::zMin() const {
    return (float) z * TO_UNITY;
}

float AABB::xMax() const {
    return (float) ((uint32_t) x + sizeMinusOne + 1) * TO_UNITY;
}

float AABB::yMax() const {
    return (float) ((uint32_t) y + sizeMinusOne + 1) * TO_UNITY;
}

float AABB::zMax() const {
    return (float) ((uint32_t) z + sizeMinusOne + 1) * TO_UNITY;
}

AABB AABB::subdivide(uint8_t index) const {
    constexpr auto B_001 = (uint8_t) 0x1;
    constexpr auto B_010 = (uint8_t) 0x2;
    constexpr auto B_100 = (uint8_t) 0x4;
    const auto HALF_SIZE = (uint8_t) (sizeMinusOne >> (uint8_t) 1);

    uint8_t nx {x}, ny {y}, nz {z};
    if (index & B_001) nx += HALF_SIZE + 1;
    if (index & B_010) ny += HALF_SIZE + 1;
    if (index & B_100) nz += HALF_SIZE + 1;

    return AABB{nx, ny, nz, HALF_SIZE};
}
