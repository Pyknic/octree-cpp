#pragma once

#include <cstdint>
#include "Octree.h"

template<typename T>
class OctreeLeaf : public Octree<T> {
public:
    explicit OctreeLeaf(const T &value);

    ~OctreeLeaf();

    bool isLeafAndEqualTo(const T &value) const override;

    T get(uint8_t x, uint8_t y, uint8_t z) const override;

    Octree<T> *set(uint8_t x, uint8_t y, uint8_t z, const T &value) override;

private:
    T value;
};

