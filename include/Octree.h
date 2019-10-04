#pragma once

#include <cstdint>

#define OCTREE_MAX_SIZE 256

template<typename T>
class Octree {
public:
    Octree();

    virtual ~Octree() = 0;

    virtual bool isLeafAndEqualTo(const T &value) const = 0;

    virtual T get(uint8_t x, uint8_t y, uint8_t z) const = 0;

    virtual Octree<T> *set(uint8_t x, uint8_t y, uint8_t z, const T &value) = 0;
};