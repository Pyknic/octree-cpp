#pragma once

#include <cstdint>
#include "Octree.h"

template<typename T, uint8_t SIZE>
class OctreeBranch : public Octree<T> {
public:
    explicit OctreeBranch(const T &defaultValue);

    ~OctreeBranch();

    bool isLeafAndEqualTo(const T &value) const override;

    T get(uint8_t x, uint8_t y, uint8_t z) const override;

    Octree<T> *set(uint8_t x, uint8_t y, uint8_t z, const T &value) override;

private:
    Octree<T> *children[8];
};

template<typename T> class OctreeBranch<T, 0>;
template<typename T> class OctreeBranch<T, 1>;
template<typename T> class OctreeBranch<T, 2>;
template<typename T> class OctreeBranch<T, 4>;
template<typename T> class OctreeBranch<T, 8>;
template<typename T> class OctreeBranch<T, 16>;
template<typename T> class OctreeBranch<T, 32>;
template<typename T> class OctreeBranch<T, 64>;
template<typename T> class OctreeBranch<T, 128>;