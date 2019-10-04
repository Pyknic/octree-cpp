#include "Octree.h"
#include "OctreeNode.h"

template <typename T>
Octree<T>::Octree() = default;

template <typename T>
Octree<T>::~Octree() = default;

template<typename T>
Octree<T>* Octree<T>::create(const T &value) {
    return new OctreeNode<T, OCTREE_MAX_SIZE>{value};
}

template<typename T>
Octree<T>* Octree<T>::fill(const Shape &shape, const T &value) {
    const AABB bounds {0, 0, 0, (uint8_t) 0xff};
    return fill(bounds, shape, value);
}

template<typename T>
void Octree<T>::forEach(const Octree::BranchAction &action, uint8_t childSize) const {
    const AABB bounds {0, 0, 0, (uint8_t) 0xff};
    return forEach(bounds, action, childSize);
}
