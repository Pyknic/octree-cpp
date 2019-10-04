#pragma once

#include <cstdint>
#include "Octree.h"

template<typename T, uint8_t SIZE>
class OctreeNode : public Octree<T> {
public:
    explicit OctreeNode(const T &value);

    ~OctreeNode();

    bool isLeafAndEqualTo(const T &value) const override;

    T get(uint8_t x, uint8_t y, uint8_t z) const override;

    Octree<T> *set(uint8_t x, uint8_t y, uint8_t z, const T &value) override;

private:
    const T value;
};

template<typename T> class OctreeNode<T, 0>;
template<typename T> class OctreeNode<T, 1>;
template<typename T> class OctreeNode<T, 2>;
template<typename T> class OctreeNode<T, 4>;
template<typename T> class OctreeNode<T, 8>;
template<typename T> class OctreeNode<T, 16>;
template<typename T> class OctreeNode<T, 32>;
template<typename T> class OctreeNode<T, 64>;
template<typename T> class OctreeNode<T, 128>;