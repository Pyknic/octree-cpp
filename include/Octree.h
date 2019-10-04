#pragma once

#include <cstdint>
#include <functional>
#include "Shape.h"

#define OCTREE_MAX_SIZE 128

template<typename T>
class Octree {
public:
    typedef std::function<bool(const T& value)> TPredicate;
    typedef std::function<void(Octree<T>* tree, const AABB& bounds)> BranchAction;

    static Octree<T>* create(const T& value);

    virtual ~Octree() = 0;

    virtual bool isLeafAndEqualTo(const T &value) const = 0;

    virtual T get(uint8_t index) const = 0;

    virtual T get(uint8_t x, uint8_t y, uint8_t z) const = 0;

    virtual Octree<T> *set(uint8_t x, uint8_t y, uint8_t z, const T &value) = 0;

    /**
     * Fills all the nodes in the octree located inside the specified shape. The
     * shape is expected to be given in a coordinate system normalized after the
     * octree so that the left-most position in the tree has value {@code 0.0}
     * and the right-most position in the tree has value {@code 1.0}.
     *
     * @param shape  the shape to test intersection against
     * @param value  the value to fill with
     * @return  A replacement for this node if the implementation had to be
     *          changed. If the implementation of this node could remain the
     *          same, then {@code nullptr} is returned instead.
     */
    Octree<T>* fill(const Shape& shape, const T& value);

    /**
     * Tests each of the children in this level of the octree with the specified
     * predicate, setting a bit in a bitmap to 1 for each success. The bitmap is
     * then returned.
     * <p>
     * If this is a leaf node, then the predicate is only invoked once and the
     * returned bitmap will be either {@code 0x00} or {@code 0xff}.
     * <p>
     * If this is a branch, the predicate will be invoked on the corners of the
     * cube.
     *
     * @param predicate  the predicate to test children against
     * @return  bitmap showing which children match the predicate
     */
    virtual uint8_t test(const TPredicate& predicate) const = 0;

    /**
     * Applies the specified action on every branch in this tree on the
     * specified level. The action will be given a pointer to the branch as well
     * as the bounds for that branch. If all values are identical over a large
     * area, the size of the bounds might be larger than the specified size.
     *
     * @param action  the action to invoke
     * @param childSize  the size of the children in the nodes we want
     */
    void forEach(const BranchAction& action, uint8_t childSize=0) const;

protected:
    Octree();

    virtual Octree<T>* fill(const AABB& bounds, const Shape& shape, const T& value) = 0;

    virtual void forEach(const AABB& bounds, const BranchAction& action, uint8_t childSize) const = 0;
};

