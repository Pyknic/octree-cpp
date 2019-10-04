#pragma once

#include <cstdint>
#include "Octree.h"

template<typename T>
class OctreeLeaf : public Octree<T> {
public:
    explicit OctreeLeaf(const T &value);

    ~OctreeLeaf();

    bool isLeafAndEqualTo(const T &val) const override;

    T get(uint8_t) const override;

    T get(uint8_t x, uint8_t y, uint8_t z) const override;

    Octree<T> *set(uint8_t x, uint8_t y, uint8_t z, const T &value) override;

    uint8_t test(const typename Octree<T>::TPredicate &predicate) const override;

protected:
    Octree<T>* fill(const AABB& bounds, const Shape& shape, const T& value) override;

    void forEach(const AABB& bounds, const typename Octree<T>::BranchAction& action, uint8_t childSize) const override;

private:
    T value;
};

